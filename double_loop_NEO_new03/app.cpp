/******************************************************************************
 *  ファイル名：app.cpp
 *　　　　内容：タスクであるmain_taskの実施
 *  　　作成日：2024/8/20
 *  　　作成者：近藤　悠太
 *****************************************************************************/
#include <stdio.h>

#include "app.h"

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

using namespace ev3api;

Motor       gLeftMotor(PORT_C);
Motor       gRightMotor(PORT_B);
Motor       gLeftMotorEncoder(PORT_C);
Motor       gRightMotorEncoder(PORT_B);
GyroSensor  gGyroSensor(PORT_4);
ColorSensor gColorSensor(PORT_2);

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

Control*        gControl[Control::SIZE] = {nullptr};

Run*            gRun[Scenario::SIZE] = {nullptr};
Judge*          gJudge[Scenario::SIZE] = {nullptr};

Scene*          gScene[Scenario::SIZE] = {nullptr};
Scenario*       gScenario = nullptr;
DeviceManage*   gDeviceManage = nullptr;
ScenarioTracer* gScenarioTracer = nullptr;

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

    /* -------------------------------------------------------------
     * 概要　　：シーン１
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[0] = new GyroStopP(gAngleMonitor);
    gRun[0]     = new RotateRun(RotateRun::RIGHT, gControl[0], gLeftMotor, gRightMotor);
    gJudge[0]   = new RotateAngleJudge(RotateAngleJudge::RIGHT, gAngleMonitor);

    /* -------------------------------------------------------------
     * 概要　　：シーン２
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[1] = new GyroStraPD(gAngleMonitor);
    gRun[1]     = new StraRun(gControl[1], gLeftMotor, gRightMotor, Run::MID);
    gJudge[1]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン３
     * 走行方法：ラインサーチ走行
     * 判定方法：色判定
     * 制御方法：なし
     * ------------------------------------------------------------*/
    gRun[2]     = new LineSearchRun(gLeftMotor, gRightMotor);
    gJudge[2]   = new ColorJudge(gColorDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン４
     * 走行方法：ライントレース走行
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[2] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[3]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[2], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[3]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン５
     * 走行方法：ライントレース走行
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[3] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[4]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[3], gLeftMotor, gRightMotor, Run::MID);
    gJudge[4]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン６
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[4] = new GyroStraPD(gAngleMonitor);
    gRun[5]     = new StraRun(gControl[4], gLeftMotor, gRightMotor, Run::HIGH);
    gJudge[5]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン７
     * 走行方法：ラインサーチ走行
     * 判定方法：色判定
     * 制御方法：なし
     * ------------------------------------------------------------*/
    gRun[6]     = new LineSearchRun(gLeftMotor, gRightMotor);
    gJudge[6]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン８
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[5] = new GyroStopP(gAngleMonitor);
    gRun[7]     = new RotateRun(RotateRun::LEFT, gControl[5], gLeftMotor, gRightMotor);
    gJudge[7]   = new RotateAngleJudge(RotateAngleJudge::LEFT, gAngleMonitor);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン９
     * 走行方法：ライントレース走行
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[6] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[8]     = new LineTraceRun(LineTraceRun::LEFT, gControl[6], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[8]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１０
     * 走行方法：ライントレース走行
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[7] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[9]     = new LineTraceRun(LineTraceRun::LEFT, gControl[7], gLeftMotor, gRightMotor, Run::MID);
    gJudge[9]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１１
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[8] = new GyroStopP(gAngleMonitor);
    gRun[10]     = new RotateRun(RotateRun::LEFT, gControl[8], gLeftMotor, gRightMotor);
    gJudge[10]   = new RotateAngleJudge(RotateAngleJudge::LEFT, gAngleMonitor);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１２
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[9] = new GyroStraPD(gAngleMonitor);
    gRun[11]     = new StraRun(gControl[9], gLeftMotor, gRightMotor, Run::MID);
    gJudge[11]   = new RunDistJudge(gRunDistDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１３
     * 走行方法：ラインサーチ走行
     * 判定方法：色判定
     * 制御方法：なし
     * ------------------------------------------------------------*/
    gRun[12]     = new LineSearchRun(gLeftMotor, gRightMotor);
    gJudge[12]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１４
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[10] = new GyroStopP(gAngleMonitor);
    gRun[13]     = new RotateRun(RotateRun::RIGHT, gControl[10], gLeftMotor, gRightMotor);
    gJudge[13]   = new RotateAngleJudge(RotateAngleJudge::RIGHT, gAngleMonitor);

    /* -------------------------------------------------------------
     * 概要　　：シーン１５
     * 走行方法：ライントレース走行
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PD)
     * ------------------------------------------------------------*/
    gControl[11] = new LineTracePID(gHSVMonitor, 70, 0.5, 0, 2);
    gRun[14]     = new LineTraceRun(LineTraceRun::RIGHT, gControl[11], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[14]   = new ColorJudge(gColorDetect);
    
    /* -------------------------------------------------------------
     * 概要　　：シーン１６
     * 走行方法：直進走行
     * 判定方法：走行距離判定
     * 制御方法：まっすぐ走るための制御(PD)
     * ------------------------------------------------------------*/
    gControl[12] = new GyroStraPD(gAngleMonitor);
    gRun[15]     = new StraRun(gControl[12], gLeftMotor, gRightMotor, Run::MID);
    gJudge[15]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン１７
     * 走行方法：旋回走行
     * 判定方法：旋回角度判定
     * 制御方法：旋回角度に近づくたび減速する制御(P)
     * ------------------------------------------------------------*/
    gControl[13] = new GyroStopP(gAngleMonitor);
    gRun[16]     = new RotateRun(RotateRun::RIGHT, gControl[13], gLeftMotor, gRightMotor);
    gJudge[16]   = new RotateAngleJudge(RotateAngleJudge::RIGHT, gAngleMonitor);

    /* シーンオブジェクトを動的に確保 */
    for (i = 0; i < Scenario::SIZE; i++)
    {
        gScene[i] = new Scene(gRun[i], gJudge[i]);
    }

    /* シナリオオブジェクトを動的に確保 */
    gScenario = new Scenario(gScene);

    /* デバイス管理オブジェクトを動的に確保 */
    gDeviceManage = new DeviceManage(gLeftMotor, gRightMotor, gLeftMotorEncoder, gRightMotorEncoder, gGyroSensor);

    /* シナリオトレーサオブジェクトを動的に確保 */
    gScenarioTracer = new ScenarioTracer(gDeviceManage, gScenario, gCountMonitor, gAngleMonitor, gHSVMonitor);
}

/* システムの破棄 */
void system_destroy()
{
    unsigned char i;

    /* 動的なオブジェクトの解放 */
    delete gScenarioTracer;
    gScenarioTracer = nullptr;
    
    delete gDeviceManage;
    gDeviceManage = nullptr;
    
    delete gScenario;
    gScenario = nullptr;

    for (i = 0; i < Scenario::SIZE; i++)
    {
        delete gScene[i];
        gScene[i] = nullptr;
    }

    for (i = 0; i < Scenario::SIZE; i++)
    {
        delete gRun[i];
        gRun[i] = nullptr;
    }

    for (i = 0; i < Scenario::SIZE; i++)
    {
        delete gJudge[i];
        gJudge[i] = nullptr;
    }

    for (i = 0; i < Control::SIZE; i++)
    {
        delete gControl[i];
        gControl[i] = nullptr;
    }

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
    sta_cyc(CYC_DOUBLE_LOOP_NEO);

    slp_tsk();  /* メインタスクの起床待ち */

    /* 周期ハンドラ停止 */
    stp_cyc(CYC_DOUBLE_LOOP_NEO);

    system_destroy();  /* 終了処理 */

    ext_tsk();  /* タスクの終了 */
}

void double_loop_NEO_task(intptr_t exinf)
{
    gScenarioTracer->capture();
    
    //gLeftMotor.setPWM(40);
    //printf("hahahha\n");
    
    if (gScenarioTracer->getState() == ScenarioTracer::STOP || ev3_button_is_pressed(ENTER_BUTTON) == true)
    {
        wup_tsk(MAIN_TASK);
    }
}
