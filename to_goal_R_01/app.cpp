/******************************************************************************
 *  ファイル名：app.cpp
 *　　　　内容：タスクであるmain_taskの実施
 *  　　作成日：2024/8/20
 *  　　作成者：近藤　悠太
 *****************************************************************************/
#include <stdio.h>

#include "app.h"

#include "HackSPiUnit2.h"
#include "ScenarioTracerWithStarter.h"
#include "ScenarioTracer.h"
#include "DeviceManage.h"
#include "Scenario.h"
#include "Scene.h"

#include "Run.h"
#include "RotateRun.h"
#include "StraRun.h"
#include "LineSearchRun.h"
#include "LineTraceRun.h"

#include "Control.h"
#include "GyroStopP.h"
#include "GyroStraPD.h"
#include "LineTracePID.h"

#include "Judge.h"
#include "RotateAngleJudge.h"
#include "RunDistJudge.h"
#include "ColorJudge.h"

#include "RunDistDetect.h"
#include "ColorDetect.h"

#include "AngleMonitor.h"
#include "CountMonitor.h"
#include "HSVMonitor.h"

#include "Motor.h"
#include "GyroSensor.h"
#include "ColorSensor.h"
#include "SonarSensor.h"

using namespace ev3api;

Motor       gLeftMotor(PORT_C);
Motor       gRightMotor(PORT_B);
Motor       gLeftMotorEncoder(PORT_C);
Motor       gRightMotorEncoder(PORT_B);
GyroSensor  gGyroSensor(PORT_4);
ColorSensor gColorSensor(PORT_2);
SonarSensor gSonarSensor(PORT_3);

/*----------------------------------------------------
*                      内部結合
*-----------------------------------------------------*/
namespace {

/* オブジェクトの定義 */
AngleMonitor*   gAngleMonitor = nullptr;
CountMonitor*   gCountMonitor = nullptr;
HSVMonitor*     gHSVMonitor = nullptr;

ColorDetect*    gColorDetect = nullptr;
RunDistDetect*  gRunDistDetect = nullptr;

/////////////////////////////////SIZE変更//////////////////////////////
Control*        gControl[Control::ALL_SIZE] = {nullptr};

Run*            gRun[Scenario::ALL_SIZE] = {nullptr};
Judge*          gJudge[Scenario::ALL_SIZE] = {nullptr};

Scene*          gScene[Scenario::ALL_SIZE] = {nullptr};
//////////////////////////////////////////////////////////////////////

DeviceManage*   gDeviceManage = nullptr;

/*----------------toLAPゲート走行のシナリオ関連のポインタ定義----------------------*/

Scenario*       gLAPScenario = nullptr;
ScenarioTracer* gLAPScenarioTracer = nullptr;
ScenarioTracerWithStarter* gLAPScenarioTracerWithStarter = nullptr;

/*-----------------------------------------------------------------------------*/

Scenario*       gDoubleScenario = nullptr;  // ダブルループNEO
Scenario*       gToGoalScenario = nullptr;  // ゴールまで

 /* 0：ダブルループNEO、
    1：ゴールまで       */
ScenarioTracer* gScenarioTracer[HackSPiUnit2::SIZE] = {nullptr};

HackSPiUnit2*   gHackSPiUnit2 = nullptr;    // HackSPi2号機の生成

/* システムの生成 */
void system_create()
{
    unsigned char i;
    /* 監視(Monitor)オブジェクトを動的に確保 */
    gAngleMonitor = new AngleMonitor(gGyroSensor);
    gCountMonitor = new CountMonitor(gLeftMotorEncoder, gRightMotorEncoder);
    gHSVMonitor   = new HSVMonitor(gColorSensor);

    /* 検出(Detect)オブジェクトを動的に確保 */
    gColorDetect   = new ColorDetect(gHSVMonitor);
    gRunDistDetect = new RunDistDetect(gCountMonitor);

    /* デバイス管理オブジェクトを動的に確保 */
    gDeviceManage = new DeviceManage(gLeftMotor, gRightMotor, gLeftMotorEncoder, gRightMotorEncoder, gGyroSensor);

    /*---------------------------------toLAPゲート---------------------------------------------*/

    /* -------------------------------------------------------------
     * 概要　　：シーン１
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[0] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.005, 2);
    gRun[0]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[0], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[0]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン２
     * 走行方法：ライントレース走行（PWM = 70）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[1] = new LineTracePID(gHSVMonitor, 40, 0.1, 0.005, 3);
    gRun[1]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[1], gLeftMotor, gRightMotor, Run::HIGH);
    gJudge[1]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン３
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[2] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.005, 2);
    gRun[2]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[2], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[2]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン４
     * 走行方法：ライントレース走行（PWM = 70）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[3] = new LineTracePID(gHSVMonitor, 40, 0.1, 0.005, 3);
    gRun[3]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[3], gLeftMotor, gRightMotor, Run::HIGH);
    gJudge[3]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン５
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[4] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.005, 2);
    gRun[4]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[4], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[4]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン６
     * 走行方法：ライントレース走行（PWM = 45）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[5] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.025, 2);
    gRun[5]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[5], gLeftMotor, gRightMotor, Run::MID);
    gJudge[5]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン７
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[6] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.025, 2);
    gRun[6]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[6], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[6]   = new ColorJudge(gColorDetect);

    /* シーンオブジェクトを動的に確保 */
    for (i = 0; i < Scenario::TO_LAP_SIZE; i++)
    {
        gScene[i] = new Scene(gRun[i], gJudge[i]);
    }

    /* toLAPゲート走行シナリオオブジェクトを動的に確保 */
    gLAPScenario = new Scenario(gScene, 0, 6);

    /* toLAPゲート走行シナリオトレーサオブジェクトを動的に確保 */
    gLAPScenarioTracer = new ScenarioTracer(gDeviceManage, gLAPScenario, gCountMonitor, gAngleMonitor, gHSVMonitor);

    /* toLAPゲート走行スターター付きシナリオトレーサオブジェクトを動的に確保 */
    gLAPScenarioTracerWithStarter = new ScenarioTracerWithStarter(gLAPScenarioTracer, gSonarSensor);
    
    /*----------------------------------------------------------------------------------------*/

    /*-----------------------------------ダブルループNEO---------------------------------------*/

    /* -------------------------------------------------------------
     * 概要　　：シーン１
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 0] = new GyroStopP(gAngleMonitor);
    gRun[Scenario::TO_LAP_SIZE + 0]     = new RotateRun(RotateRun::LEFT, gControl[Control::TO_LAP_SIZE + 0], gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_LAP_SIZE + 0]   = new RotateAngleJudge(RotateAngleJudge::LEFT, gAngleMonitor);

    /* -------------------------------------------------------------
     * 概要　　：シーン２
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 1] = new GyroStraPD(gAngleMonitor);
    gRun[Scenario::TO_LAP_SIZE + 1]     = new StraRun(StraRun::FRONT, gControl[Control::TO_LAP_SIZE + 1], gLeftMotor, gRightMotor, Run::MID);
    gJudge[Scenario::TO_LAP_SIZE + 1]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン３
     * 走行方法：ラインサーチ走行
     * 判定方法：色判定
     * 制御方法：なし
     * ------------------------------------------------------------*/
    gRun[Scenario::TO_LAP_SIZE + 2]     = new LineSearchRun(gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_LAP_SIZE + 2]   = new ColorJudge(gColorDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン４
     * 走行方法：ライントレース走行
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 2] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[Scenario::TO_LAP_SIZE + 3]     = new LineTraceRun(LineTraceRun::LEFT, gControl[Control::TO_LAP_SIZE + 2], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[Scenario::TO_LAP_SIZE + 3]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン５
     * 走行方法：ライントレース走行
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 3] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[Scenario::TO_LAP_SIZE + 4]     = new LineTraceRun(LineTraceRun::LEFT, gControl[Control::TO_LAP_SIZE + 3], gLeftMotor, gRightMotor, Run::MID);
    gJudge[Scenario::TO_LAP_SIZE + 4]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン６
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 4] = new GyroStraPD(gAngleMonitor);
    gRun[Scenario::TO_LAP_SIZE + 5]     = new StraRun(StraRun::FRONT, gControl[Control::TO_LAP_SIZE + 4], gLeftMotor, gRightMotor, Run::HIGH);
    gJudge[Scenario::TO_LAP_SIZE + 5]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン７
     * 走行方法：ラインサーチ走行
     * 判定方法：色判定
     * 制御方法：なし
     * ------------------------------------------------------------*/
    gRun[Scenario::TO_LAP_SIZE + 6]     = new LineSearchRun(gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_LAP_SIZE + 6]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン８
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 5] = new GyroStopP(gAngleMonitor);
    gRun[Scenario::TO_LAP_SIZE + 7]     = new RotateRun(RotateRun::RIGHT, gControl[Control::TO_LAP_SIZE + 5], gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_LAP_SIZE + 7]   = new RotateAngleJudge(RotateAngleJudge::RIGHT, gAngleMonitor);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン９
     * 走行方法：ライントレース走行
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 6] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[Scenario::TO_LAP_SIZE + 8]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[Control::TO_LAP_SIZE + 6], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[Scenario::TO_LAP_SIZE + 8]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１０
     * 走行方法：ライントレース走行
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 7] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[Scenario::TO_LAP_SIZE + 9]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[Control::TO_LAP_SIZE + 7], gLeftMotor, gRightMotor, Run::MID);
    gJudge[Scenario::TO_LAP_SIZE + 9]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１１
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 8] = new GyroStopP(gAngleMonitor);
    gRun[Scenario::TO_LAP_SIZE + 10]     = new RotateRun(RotateRun::RIGHT, gControl[Control::TO_LAP_SIZE + 8], gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_LAP_SIZE + 10]   = new RotateAngleJudge(RotateAngleJudge::RIGHT, gAngleMonitor);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１２
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 9] = new GyroStraPD(gAngleMonitor);
    gRun[Scenario::TO_LAP_SIZE + 11]     = new StraRun(StraRun::FRONT, gControl[Control::TO_LAP_SIZE + 9], gLeftMotor, gRightMotor, Run::MID);
    gJudge[Scenario::TO_LAP_SIZE + 11]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１３
     * 走行方法：ラインサーチ走行
     * 判定方法：色判定
     * 制御方法：なし
     * ------------------------------------------------------------*/
    gRun[Scenario::TO_LAP_SIZE + 12]     = new LineSearchRun(gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_LAP_SIZE + 12]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１４
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 10] = new GyroStopP(gAngleMonitor);
    gRun[Scenario::TO_LAP_SIZE + 13]     = new RotateRun(RotateRun::LEFT, gControl[Control::TO_LAP_SIZE + 10], gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_LAP_SIZE + 13]   = new RotateAngleJudge(RotateAngleJudge::LEFT, gAngleMonitor);

    /* -------------------------------------------------------------
     * 概要　　：シーン１５
     * 走行方法：ライントレース走行
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 11] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[Scenario::TO_LAP_SIZE + 14]     = new LineTraceRun(LineTraceRun::LEFT, gControl[Control::TO_LAP_SIZE + 11], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[Scenario::TO_LAP_SIZE + 14]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１６
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 12] = new GyroStraPD(gAngleMonitor);
    gRun[Scenario::TO_LAP_SIZE + 15]     = new StraRun(StraRun::FRONT, gControl[Control::TO_LAP_SIZE + 12], gLeftMotor, gRightMotor, Run::MID);
    gJudge[Scenario::TO_LAP_SIZE + 15]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン１７
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 13] = new GyroStopP(gAngleMonitor);
    gRun[Scenario::TO_LAP_SIZE + 16]     = new RotateRun(RotateRun::LEFT, gControl[Control::TO_LAP_SIZE + 13], gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_LAP_SIZE + 16]   = new RotateAngleJudge(RotateAngleJudge::LEFT, gAngleMonitor);

    /* -------------------------------------------------------------
     * 概要　　：シーン１８
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 14] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.025, 2);
    gRun[Scenario::TO_LAP_SIZE + 17]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[Control::TO_LAP_SIZE + 14], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[Scenario::TO_LAP_SIZE + 17]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン１９
     * 走行方法：ライントレース走行（PWM = 45）
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[Control::TO_LAP_SIZE + 15] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.025, 2);
    gRun[Scenario::TO_LAP_SIZE + 18]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[Control::TO_LAP_SIZE + 15], gLeftMotor, gRightMotor, Run::MID);
    gJudge[Scenario::TO_LAP_SIZE + 18]   = new ColorJudge(gColorDetect);
    
    /* シーンオブジェクトを動的に確保 */
    for (i = Scenario::TO_LAP_SIZE; i < Scenario::TO_DOUBLE_SIZE; i++)
    {
        gScene[i] = new Scene(gRun[i], gJudge[i]);
    }

    /* ダブルループNEO走行シナリオオブジェクトを動的に確保 */
    gDoubleScenario = new Scenario(gScene, 7, 25);

    /* ダブルループNEO走行シナリオトレーサオブジェクトを動的に確保 */
    gScenarioTracer[0] = new ScenarioTracer(gDeviceManage, gDoubleScenario, gCountMonitor, gAngleMonitor, gHSVMonitor);

    /*----------------------------------------------------------------------------------------*/

    /*-----------------------------------ゴールまで--------------------------------------------*/
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_DOUBLE_SIZE + 0] = new GyroStraPD(gAngleMonitor);
    gRun[Scenario::TO_DOUBLE_SIZE + 0]     = new StraRun(StraRun::FRONT, gControl[Control::TO_DOUBLE_SIZE + 0], gLeftMotor, gRightMotor, Run::HIGH);
    gJudge[Scenario::TO_DOUBLE_SIZE + 0]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン２
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_DOUBLE_SIZE + 1] = new GyroStraPD(gAngleMonitor);
    gRun[Scenario::TO_DOUBLE_SIZE + 1]     = new StraRun(StraRun::BEHIND, gControl[Control::TO_DOUBLE_SIZE + 1], gLeftMotor, gRightMotor, Run::HIGH);
    gJudge[Scenario::TO_DOUBLE_SIZE + 1]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン３
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[Control::TO_DOUBLE_SIZE + 2] = new GyroStopP(gAngleMonitor);
    gRun[Scenario::TO_DOUBLE_SIZE + 2]     = new RotateRun(RotateRun::LEFT, gControl[Control::TO_DOUBLE_SIZE + 2], gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_DOUBLE_SIZE + 2]   = new RotateAngleJudge(RotateAngleJudge::LEFT, gAngleMonitor);

    /* -------------------------------------------------------------
     * 概要　　：シーン４
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[Control::TO_DOUBLE_SIZE + 3] = new GyroStraPD(gAngleMonitor);
    gRun[Scenario::TO_DOUBLE_SIZE + 3]     = new StraRun(StraRun::FRONT, gControl[Control::TO_DOUBLE_SIZE + 3], gLeftMotor, gRightMotor, Run::HIGH);
    gJudge[Scenario::TO_DOUBLE_SIZE + 3]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン５
     * 走行方法：ラインサーチ走行
     * 判定方法：色判定
     * 制御方法：なし
     * ------------------------------------------------------------*/
    gRun[Scenario::TO_DOUBLE_SIZE + 4]     = new LineSearchRun(gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_DOUBLE_SIZE + 4]   = new ColorJudge(gColorDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン６
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[Control::TO_DOUBLE_SIZE + 4] = new GyroStopP(gAngleMonitor);
    gRun[Scenario::TO_DOUBLE_SIZE + 5]     = new RotateRun(RotateRun::RIGHT, gControl[Control::TO_DOUBLE_SIZE + 4], gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_DOUBLE_SIZE + 5]   = new RotateAngleJudge(RotateAngleJudge::RIGHT, gAngleMonitor);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン７
     * 走行方法：ラインサーチ走行
     * 判定方法：色判定
     * 制御方法：なし
     * ------------------------------------------------------------*/
    gRun[Scenario::TO_DOUBLE_SIZE + 6]     = new LineSearchRun(gLeftMotor, gRightMotor);
    gJudge[Scenario::TO_DOUBLE_SIZE + 6]   = new ColorJudge(gColorDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン８
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[Control::TO_DOUBLE_SIZE + 5] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.025, 2);
    gRun[Scenario::TO_DOUBLE_SIZE + 7]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[Control::TO_DOUBLE_SIZE + 5], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[Scenario::TO_DOUBLE_SIZE + 7]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン８
     * 走行方法：ライントレース走行（PWM = 45）
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[Control::TO_DOUBLE_SIZE + 6] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.025, 2);
    gRun[Scenario::TO_DOUBLE_SIZE + 8]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[Control::TO_DOUBLE_SIZE + 6], gLeftMotor, gRightMotor, Run::MID);
    gJudge[Scenario::TO_DOUBLE_SIZE + 8]   = new ColorJudge(gColorDetect);
    
    /* シーンオブジェクトを動的に確保 */
    for (i = Scenario::TO_DOUBLE_SIZE; i < Scenario::ALL_SIZE; i++)
    {
        gScene[i] = new Scene(gRun[i], gJudge[i]);
    }
    
    /* ゴールまで走行シナリオオブジェクトを動的に確保 */
    gToGoalScenario = new Scenario(gScene, 26, 34);

    /* ゴールまで走行シナリオトレーサオブジェクトを動的に確保 */
    gScenarioTracer[1] = new ScenarioTracer(gDeviceManage, gToGoalScenario, gCountMonitor, gAngleMonitor, gHSVMonitor);

    /*----------------------------------------------------------------------------------------*/

    gHackSPiUnit2 = new HackSPiUnit2(gLAPScenarioTracerWithStarter, gScenarioTracer);
}

/* システムの破棄 */
void system_destroy()
{
    unsigned char i;

    /* 動的なオブジェクトの解放 */
    delete gHackSPiUnit2;
    gHackSPiUnit2 = nullptr;                    // HackSPi

    delete gLAPScenarioTracerWithStarter;
    gLAPScenarioTracerWithStarter = nullptr;    // LAP

    delete gLAPScenarioTracer;
    gLAPScenarioTracer = nullptr;               // LAP

    delete gLAPScenario;
    gLAPScenario = nullptr;                     // LAP

    delete gScenarioTracer[0];
    gScenarioTracer[0] = nullptr;               // Double
    
    delete gDoubleScenario;
    gDoubleScenario = nullptr;                  // Double

    delete gScenarioTracer[1];
    gScenarioTracer[1] = nullptr;               // ToGoal

    delete gToGoalScenario;
    gToGoalScenario = nullptr;                  // ToGoal

    for (i = 0; i < Scenario::ALL_SIZE; i++)
    {
        delete gScene[i];
        gScene[i] = nullptr;
    }

    for (i = 0; i < Scenario::ALL_SIZE; i++)
    {
        delete gRun[i];
        gRun[i] = nullptr;
    }

    for (i = 0; i < Scenario::ALL_SIZE; i++)
    {
        delete gJudge[i];
        gJudge[i] = nullptr;
    }

    for (i = 0; i < Control::ALL_SIZE; i++)
    {
        delete gControl[i];
        gControl[i] = nullptr;
    }

    delete gDeviceManage;
    gDeviceManage = nullptr;

    delete gRunDistDetect;
    gRunDistDetect = nullptr;
    
    delete gColorDetect;
    gColorDetect = nullptr;

    delete gAngleMonitor;
    gAngleMonitor = nullptr;
    
    delete gHSVMonitor;
    gHSVMonitor = nullptr;
    
    delete gCountMonitor;
    gCountMonitor = nullptr;

    printf("シナリオオブジェクトの解放！！\n\n");
}

}

/*----------------------------------------------------
*                    メインタスク
*-----------------------------------------------------*/
void main_task(intptr_t unused)
{
    system_create();

    /* 周期ハンドラ開始 */
    sta_cyc(CYC_COURCE2024);

    slp_tsk();  /* メインタスクの起床待ち */

    /* 周期ハンドラ停止 */
    stp_cyc(CYC_COURCE2024);

    system_destroy();  /* 終了処理 */

    ext_tsk();  /* タスクの終了 */
}

void cource2024_task(intptr_t exinf)
{
    gHackSPiUnit2->capture();
    
    if (gHackSPiUnit2->getState() == HackSPiUnit2::STOP || ev3_button_is_pressed(ENTER_BUTTON) == true)
    {
        wup_tsk(MAIN_TASK);
    }
}
