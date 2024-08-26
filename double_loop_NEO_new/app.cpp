/******************************************************************************
 *  ファイル名：app.cpp
 *　　　　内容：タスクであるmain_taskの実施
 *  　　作成日：2024/8/20
 *  　　作成者：近藤　悠太
 *****************************************************************************/

/*------------ヘッダファイルのインクルード-------------*/

#include "app.h"
#include "Scenario.h"

/*----------------------------------------------------
*                      内部結合
*-----------------------------------------------------*/
namespace {

    Scenario* gScenario;            // シナリオオブジェクトを指すポインタを定義

    /* システムの生成 */
    void system_create()
    {
        gScenario = new Scenario;   // シナリオオブジェクトを動的に確保
    }

    /* システムの破棄 */
    void system_destroy()
    {
        delete gScenario;           // 動的に確保したシナリオオブジェクトの解放
    }
}

/*----------------------------------------------------
*                    メインタスク
*-----------------------------------------------------*/
void main_task(intptr_t unused)
{
    system_create();                // シナリオオブジェクトの生成

    sta_cyc(CYC_DOUBLE_LOOP_NEO);   // 周期ハンドラ開始

    slp_tsk();                      // メインタスクの起床待ち（スリーブ）

    stp_cyc(CYC_DOUBLE_LOOP_NEO);   // 周期ハンドラ停止

    system_destroy();               // シナリオオブジェクトの破棄

    ext_tsk();                      // タスクの終了
}

/*----------------------------------------------------
*            ダブルループNEO走行攻略タスク
*-----------------------------------------------------*/
void double_loop_NEO_task(intptr_t exinf)
{
    /* シナリオが終了したら判定 */
    if (gScenario->finish() == true)
    {
        wup_tsk(MAIN_TASK);     // メインタスクの起床
    }
    /* シナリオが実行中なら判定 */
    else
    {
        gScenario->run();       // シナリオを実行
    }
}
