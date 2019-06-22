//---------------------------------------------
//
//      ゲームクリア
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"

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

class C_GameClear:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;

	bool scene_change;	//シーンが変わる時を知らせる
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound);
	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();
	C_GameClear(void);
	~C_GameClear(void);
};
