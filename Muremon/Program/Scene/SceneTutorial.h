//---------------------------------------------
//
//      操作説明
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

#define TR_RIGHT_X	(1200.f)
#define TR_CENTER_X	(400.f)
#define TR_LEFT_X	(-400.f)
#define TR_Y		(300.f)

enum TEXTURE_DATA_TUTORIAL
{
	T_TUTORIAL1,
	T_TUTORIAL2,
};

enum RECT_DATA_TUTORIAL
{
	R_TUTORIAL1,
	R_TUTORIAL2,
};

enum TUTORIAL_FADE_MODE
{
	TR_FADE_IN,		//フェードイン
	TR_USUALLY,		//通常
	TR_FADE_OUT,	//フェードアウト
};

enum TUTORIAL_MODE
{
	TR_REFRESH,
	TR_NORMAL,
	TR_END,
};

class SceneTutorial : public SceneBase
{
private:

	int flag_draw_state;	//描画しているものを知らせる
	int slide_state;

	D3DXVECTOR2 tutorial[2];

	int fade_flag;	//フェードのフラグ

	int alpha;	//アルファ値

	int alpha_count;	//アルファ値のカウント

public:
	void impleInit() override;
	bool update() override;
	void draw() override;
	int end() override;

	void KeyControl();		//キー操作

	void DrawPosi();		//描画位置などを決める

	void FadeControl();		//フェードコントロール		

	void FadeIn();			//フェードイン

	void FadeOut();			//フェードアウト

	SceneTutorial();
	~SceneTutorial();
};
