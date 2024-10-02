/******************************************************************************
 *  ファイル名：app.cpp
 *　　　　内容：タスクであるmain_taskの実施
 *  　　作成日：2024/8/20
 *  　　作成者：近藤　悠太
 *****************************************************************************/
#include <stdio.h>

#include "app.h"

#include "ScenarioTracerWithStarter.h"
#include "ScenarioTracer.h"
#include "DeviceManage.h"
#include "Scenario.h"
#include "Scene.h"

#include "Run.h"
#include "LineTraceRun.h"

#include "Control.h"
#include "LineTracePID.h"

#include "Judge.h"
#include "RunDistJudge.h"
#include "ColorJudge.h"

#include "RunDistDetect.h"
#include "ColorDetect.h"

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
CountMonitor*   gCountMonitor;
HSVMonitor*     gHSVMonitor;

ColorDetect*    gColorDetect;
RunDistDetect*  gRunDistDetect;

Control*        gControl[Control::SIZE];

Run*            gRun[Scenario::SIZE];
Judge*          gJudge[Scenario::SIZE];

Scene*          gScene[Scenario::SIZE];
Scenario*       gScenario;
DeviceManage*   gDeviceManage;
ScenarioTracer* gScenarioTracer;
ScenarioTracerWithStarter* gScenarioTracerWithStarter;

/* システムの生成 */
void system_create()
{
    unsigned char i;
    /* 監視(Monitor)オブジェクトを動的に確保 */
    gCountMonitor = new CountMonitor(gLeftMotorEncoder, gRightMotorEncoder);
    gHSVMonitor   = new HSVMonitor(gColorSensor);

    /* 検出(Detect)オブジェクトを動的に確保 */
    gColorDetect   = new ColorDetect(gHSVMonitor);
    gRunDistDetect = new RunDistDetect(gCountMonitor);

    /* -------------------------------------------------------------
     * 概要　　：シーン１
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[0] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.005, 2);
    gRun[0]     = new LineTraceRun(LineTraceRun::LEFT, gControl[0], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[0]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン２
     * 走行方法：ライントレース走行（PWM = 70）
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[1] = new LineTracePID(gHSVMonitor, 40, 0.1, 0.005, 3);
    gRun[1]     = new LineTraceRun(LineTraceRun::LEFT, gControl[1], gLeftMotor, gRightMotor, Run::HIGH);
    gJudge[1]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン３
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[2] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.005, 2);
    gRun[2]     = new LineTraceRun(LineTraceRun::LEFT, gControl[2], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[2]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン４
     * 走行方法：ライントレース走行（PWM = 70）
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[3] = new LineTracePID(gHSVMonitor, 40, 0.1, 0.005, 3);
    gRun[3]     = new LineTraceRun(LineTraceRun::LEFT, gControl[3], gLeftMotor, gRightMotor, Run::HIGH);
    gJudge[3]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン５
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[4] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.005, 2);
    gRun[4]     = new LineTraceRun(LineTraceRun::LEFT, gControl[4], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[4]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン６
     * 走行方法：ライントレース走行（PWM = 45）
     * 判定方法：走行距離判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[5] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.025, 2);
    gRun[5]     = new LineTraceRun(LineTraceRun::LEFT, gControl[5], gLeftMotor, gRightMotor, Run::MID);
    gJudge[5]   = new RunDistJudge(gRunDistDetect);

    /* -------------------------------------------------------------
     * 概要　　：シーン７
     * 走行方法：ライントレース走行（PWM = 35）
     * 判定方法：色判定
     * 制御方法：ラインに沿って走行するための制御(PID)
     * ------------------------------------------------------------*/
    gControl[6] = new LineTracePID(gHSVMonitor, 40, 0.5, 0.025, 2);
    gRun[6]     = new LineTraceRun(LineTraceRun::LEFT, gControl[6], gLeftMotor, gRightMotor, Run::LOW);
    gJudge[6]   = new ColorJudge(gColorDetect);

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
    gScenarioTracer = new ScenarioTracer(gDeviceManage, gScenario, gCountMonitor, gHSVMonitor);

    /* スターター付きシナリオトレーサオブジェクトを動的に確保 */
    gScenarioTracerWithStarter = new ScenarioTracerWithStarter(gScenarioTracer, gSonarSensor);
}

/* システムの破棄 */
void system_destroy()
{
    unsigned char i;

    /* 動的なオブジェクトの解放 */
    delete gScenarioTracerWithStarter;
    delete gScenarioTracer;
    delete gDeviceManage;
    delete gScenario;

    for (i = 0; i < Scenario::SIZE; i++)
    {
        delete gScene[i];
    }

    for (i = 0; i < Scenario::SIZE; i++)
    {
        delete gRun[i];
    }

    for (i = 0; i < Scenario::SIZE; i++)
    {
        delete gJudge[i];
    }

    for (i = 0; i < Control::SIZE; i++)
    {
        delete gControl[i];
    }

    delete gRunDistDetect;
    delete gColorDetect;

    delete gHSVMonitor;
    delete gCountMonitor;

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
    sta_cyc(CYC_RUNL);

    slp_tsk();  /* メインタスクの起床待ち */

    /* 周期ハンドラ停止 */
    stp_cyc(CYC_RUNL);

    system_destroy();  /* 終了処理 */

    ext_tsk();  /* タスクの終了 */
}

void runL_task(intptr_t exinf)
{
    gScenarioTracerWithStarter->capture();
    
    if (gScenarioTracerWithStarter->getState() == ScenarioTracerWithStarter::STOP || ev3_button_is_pressed(ENTER_BUTTON) == true)
    {
        wup_tsk(MAIN_TASK);
    }
}
