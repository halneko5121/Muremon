//---------------------------------------------
//
//      ゲームクリア
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

enum TEXTURE_DATA_GAMECLEAR
{
	T_GAMECLEAR,
};

enum RECT_DATA_GAMECLEAR
{
	R_GAMECLEAR,
};

enum GAMECLEAR_FADE_MODE
{
	GC_FADE_IN,		//フェードイン
	GC_USUALLY,		//通常
	GC_FADE_OUT,	//フェードアウト
};

class C_GameClear:public C_SceneBase
{
public:
	void InitScene() override;
	bool ControlScene() override;
	void DrawScene() override;
	int EndScene() override;

	C_GameClear(void);
	~C_GameClear(void);
};
