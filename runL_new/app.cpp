/******************************************************************************
 *  ファイル名：app.cpp
 *　　　　内容：タスクであるmain_taskの実施
 *  　　作成日：2024/8/20
 *  　　作成者：近藤　悠太
 *****************************************************************************/
#define SIZE 7

#include <stdio.h>

#include "app.h"

#include "ScenarioTracer.h"
#include "Scenario.h"
#include "Scene.h"

#include "abstract_run.h"
#include "LineTraceRun.h"

#include "PIDcon.h"

#include "JudgeMent.h"
#include "RunDistJudgeMent.h"
#include "ColorJudgeMent.h"

#include "RunDistDetect.h"
#include "ColorDetect.h"

#include "Motor.h"
#include "ColorSensor.h"
#include "SonarSensor.h"

using namespace ev3api;

Motor       gLeftMotor(PORT_C);
Motor       gRightMotor(PORT_B);
Motor       gLeftMotorEncoder(PORT_C);
Motor       gRightMotorEncoder(PORT_B);
ColorSensor gColorSensor(PORT_2);
SonarSensor gSonarSensor(PORT_3);
Motor       gResetLeft(PORT_C);
Motor       gResetRight(PORT_B);

/*----------------------------------------------------
*                      内部結合
*-----------------------------------------------------*/
namespace {
    enum eEdge  { LEFT, RIGHT, };
    enum eColor { BLACK, BLUE, };
    enum eSpeed { LOW, HIGH, };

    int dist_array[6] = {
        50, 2700, 400, 1700, 400, 420,
    };

    /* オブジェクトの定義 */
    ColorDetect*    gColorDetect;
    PIDcon*         gPIDcon[2];
    RunDistDetect*  gRunDistDetect;
    Run*            gRun[SIZE];
    JudgeMent*      gJudgeMent[SIZE];
    Scene*          gScene[SIZE];
    Scenario*       gScenario;
    ScenarioTracer* gScenarioTracer;

    /* システムの生成 */
    void system_create()
    {
        unsigned char i;
        /* オブジェクトを動的に確保 */
        gColorDetect = new ColorDetect(gColorSensor);
        gPIDcon[LOW] = new PIDcon(LOW, gColorDetect);
        gPIDcon[HIGH] = new PIDcon(HIGH, gColorDetect);
        gRunDistDetect = new RunDistDetect(gLeftMotorEncoder, gRightMotorEncoder);

        for (i = 0; i < SIZE; i++)
        {
            if (i % 2 == 0)
            {
                gRun[i] = new LineTraceRun(LEFT, LOW, gLeftMotor, gRightMotor, gPIDcon[LOW]);
            }
            else
            {
                gRun[i] = new LineTraceRun(LEFT, HIGH, gLeftMotor, gRightMotor, gPIDcon[HIGH]);
            }
        }

        for (i = 0; i < SIZE; i++)
        {
            if (i < (SIZE - 1))
            {
                gJudgeMent[i] = new RunDistJudgeMent(dist_array[i], gRunDistDetect);
            }
            else
            {
                gJudgeMent[i] = new ColorJudgeMent(BLUE, gColorDetect);
            }
        }

        for (i = 0; i < SIZE; i++)
        {
            gScene[i] = new Scene(gRun[i], gJudgeMent[i]);
        }

        gScenario = new Scenario(gScene, gLeftMotor, gRightMotor, gLeftMotorEncoder,
                                    gRightMotorEncoder, gResetLeft, gResetRight, gColorDetect);

        gScenarioTracer = new ScenarioTracer(gScenario, gSonarSensor);
    }

    /* システムの破棄 */
    void system_destroy()
    {
        unsigned char i;

        /* 動的なオブジェクトの解放 */
        delete gScenarioTracer;
        delete gScenario;

        for (i = 0; i < SIZE; i++)
        {
            delete gScene[i];
        }

        for (i = 0; i < SIZE; i++)
        {
            delete gRun[i];
        }

        for (i = 0; i < SIZE; i++)
        {
            delete gJudgeMent[i];
        }

        delete gRunDistDetect;
        delete gPIDcon[LOW];
        delete gPIDcon[HIGH];
        delete gColorDetect;

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
    if (gScenarioTracer->getState() == ScenarioTracer::FIN || ev3_button_is_pressed(ENTER_BUTTON) == true)
    {
        wup_tsk(MAIN_TASK);
    }
    else
    {
        gScenarioTracer->run();
    }
}
