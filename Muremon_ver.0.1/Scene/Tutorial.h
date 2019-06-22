//---------------------------------------------
//
//      操作説明
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"
#include "Control.h"

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

class C_Tutorial:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;
	C_Control	*key;
	C_DSound	*sound;

	int key_state;	//キーの状態

	int keep_key_state;

	int flag_draw_state;	//描画しているものを知らせる

	POSI tutorial[2];

	int fade_flag;	//フェードのフラグ

	int alpha;	//アルファ値

	int alpha_count;	//アルファ値のカウント

	bool scene_change;	//シーンが変わる時を知らせる
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score);

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void KeyControl();		//キー操作

	void DrawPosi();		//描画位置などを決める

	void FadeControl();		//フェードコントロール		

	void FadeIn();			//フェードイン

	void FadeOut();			//フェードアウト

	C_Tutorial(void);
	~C_Tutorial(void);
};
