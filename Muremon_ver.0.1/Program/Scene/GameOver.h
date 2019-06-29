//---------------------------------------------
//
//      ゲームオーバー
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"

enum TEXTURE_DATA_GAMEOVER
{
	T_GAMEOVER,
};

enum RECT_DATA_GAMEOVER
{
	R_GAMEOVER,
};

enum GAMEOVER_FADE_MODE
{
	GO_FADE_IN,		//フェードイン
	GO_USUALLY,		//通常
	GO_FADE_OUT,	//フェードアウト
};

class C_GameOver:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;

	int alpha;	//アルファ値

	int fade_flag;

	int alpha_count;

	bool scene_change;	//シーンが変わる時を知らせる
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev, C_DFont* apFont, C_DSound* apSound, int score) override;

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void FadeControl();		//フェードコントロール		

	void FadeIn();			//フェードイン

	void FadeOut();			//フェードアウト

	C_GameOver(void);
	~C_GameOver(void);
};
