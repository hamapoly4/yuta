/******************************************************************************
 *  ファイル名：Scenario.cpp
 *　　　　内容：シナリオクラスの定義
 *  　　作成日：2024/8/22
 *  　　作成者：近藤　悠太
 *****************************************************************************/

/*-------------------ヘッダファイルのインクルード----------------------*/

#include "Scenario.h"
#include <stdio.h>

/*--------------------------コンストラクタ--------------------------------*/

Scenario::Scenario()
	: mscene_no(TOP), mscene_switch_flag(false), mscenario_fin_flag(false)
{
	mScene[TOP] = new Scene(mscene_no);	// シーン①を確保
}

Scenario::~Scenario()
{
	delete mScene[LAST];				// シーン⑯を解放

	printf("シナリオオブジェクトの解放！！\n");
}

void Scenario::run()
{
	mScene[mscene_no]->run();
	mscene_switch_flag = mScene[mscene_no]->fin_judge();
	switch_scene();
}

void Scenario::switch_scene()
{
	if (mscene_switch_flag == true)
	{
		if (mscene_no >= LAST)
		{
			mscenario_fin_flag = true;
		}
		else
		{
			delete mScene[mscene_no];
			mscene_no++;
			mScene[mscene_no] = new Scene(mscene_no);
			mscene_switch_flag = false;
		}
	}
}

bool Scenario::finish()
{
	return mscenario_fin_flag;
}
