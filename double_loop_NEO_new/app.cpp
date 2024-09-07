/******************************************************************************
 *  ファイル名：app.cpp
 *　　　　内容：タスクであるmain_taskの実施
 *  　　作成日：2024/8/20
 *  　　作成者：近藤　悠太
 *****************************************************************************/
#include <stdio.h>

#include "app.h"

#include "Scenario.h"
#include "Scene.h"

#include "abstract_run.h"
#include "RotateRun.h"
#include "StraRun.h"
#include "LineTraceRun.h"

#include "PDcon.h"

#include "JudgeMent.h"
#include "RotateAngleJudgeMent.h"
#include "RunDistJudgeMent.h"
#include "ColorJudgeMent.h"

#include "RunDistDetect.h"
#include "ColorDetect.h"

#include "Motor.h"
#include "GyroSensor.h"
#include "ColorSensor.h"

using namespace ev3api;

Motor       gLeftMotor(PORT_C);
Motor       gRightMotor(PORT_B);
Motor       gLeftMotorEncoder(PORT_C);
Motor       gRightMotorEncoder(PORT_B);
GyroSensor  gJudgeGyro(PORT_4);
GyroSensor  gStraRunGyro(PORT_4);
GyroSensor  gResetGyro(PORT_4);
ColorSensor gColorSensor(PORT_2);

/*----------------------------------------------------
*                      内部結合
*-----------------------------------------------------*/
namespace {

    enum eDire { LEFT, RIGHT, };
    enum eColor { BLACK, BLUE, };
    enum eRun { STRAIGHT, LINETRACE };

    /* オブジェクトの定義 */
    ColorDetect*    gColorDetect;
    PDcon*          gPDconGyro;
    PDcon*          gPDconColor;
    RunDistDetect*  gRunDistDetect;
    Run*            gRun[13];
    JudgeMent*      gJudgeMent[13];
    Scene*          gScene[13];
    Scenario*       gScenario;

    /* システムの生成 */
    void system_create()
    {
        unsigned char i;
        /* オブジェクトを動的に確保 */
        gColorDetect = new ColorDetect(gColorSensor);
        gPDconGyro = new PDcon(STRAIGHT, gStraRunGyro, gColorDetect);
        gPDconColor = new PDcon(LINETRACE, gStraRunGyro, gColorDetect);
        gRunDistDetect = new RunDistDetect(gLeftMotorEncoder, gRightMotorEncoder);

        for (i = 0; i < 13; i++)
        {
            switch (i)
            {
                case  0:
                case 12:
                    gRun[i] = new RotateRun(RIGHT, gLeftMotor, gRightMotor);
                    break;
                case  4:
                case  8:
                    gRun[i] = new RotateRun(LEFT, gLeftMotor, gRightMotor);
                    break;
                case  1:
                case  5:
                case  9:
                case 11:
                    gRun[i] = new StraRun(gLeftMotor, gRightMotor, gPDconGyro);
                    break;
                case  2:
                case  3:
                case 10:
                    gRun[i] = new LineTraceRun(RIGHT, gLeftMotor, gRightMotor, gPDconColor);
                    break;
                case  6:
                case  7:
                    gRun[i] = new LineTraceRun(LEFT, gLeftMotor, gRightMotor, gPDconColor);
                    break;
                default:
                    break;
            }
        }

        gJudgeMent[0] = new RotateAngleJudgeMent(RIGHT, 1, gJudgeGyro);
        gJudgeMent[4] = new RotateAngleJudgeMent(LEFT, -1, gJudgeGyro);
        gJudgeMent[8] = new RotateAngleJudgeMent(LEFT, -2, gJudgeGyro);
        gJudgeMent[12] = new RotateAngleJudgeMent(RIGHT, 15, gJudgeGyro);

        gJudgeMent[1] = new RunDistJudgeMent(280, gRunDistDetect);
        gJudgeMent[5] = new RunDistJudgeMent(50, gRunDistDetect);
        gJudgeMent[9] = new RunDistJudgeMent(50, gRunDistDetect);
        gJudgeMent[11] = new RunDistJudgeMent(150, gRunDistDetect);

        gJudgeMent[2] = new ColorJudgeMent(BLUE, gColorDetect);
        gJudgeMent[3] = new ColorJudgeMent(BLACK, gColorDetect);
        gJudgeMent[6] = new ColorJudgeMent(BLUE, gColorDetect);
        gJudgeMent[7] = new ColorJudgeMent(BLACK, gColorDetect);
        gJudgeMent[10] = new ColorJudgeMent(BLUE, gColorDetect);

        for (i = 0; i < 13; i++)
        {
            gScene[i] = new Scene(gRun[i], gJudgeMent[i]);
        }

        gScenario = new Scenario(gScene, gLeftMotor, gRightMotor, gLeftMotorEncoder,
                                    gRightMotorEncoder, gResetGyro, gColorDetect);
    }

    /* システムの破棄 */
    void system_destroy()
    {
        unsigned char i;

        /* 動的なオブジェクトの解放 */
        delete gScenario;

        for (i = 0; i < 13; i++)
        {
            delete gScene[i];
        }

        for (i = 0; i < 13; i++)
        {
            delete gRun[i];
        }

        for (i = 0; i < 13; i++)
        {
            delete gJudgeMent[i];
        }

        delete gRunDistDetect;
        delete gPDconColor;
        delete gPDconGyro;
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
    sta_cyc(CYC_DOUBLE_LOOP_NEO);

    slp_tsk();  /* メインタスクの起床待ち */

    /* 周期ハンドラ停止 */
    stp_cyc(CYC_DOUBLE_LOOP_NEO);

    system_destroy();  /* 終了処理 */

    ext_tsk();  /* タスクの終了 */
}

void double_loop_NEO_task(intptr_t exinf)
{
    if (gScenario->finish() == true || ev3_button_is_pressed(ENTER_BUTTON) == true)
    {
        wup_tsk(MAIN_TASK);
    }
    else
    {
        gScenario->run();
    }
}
