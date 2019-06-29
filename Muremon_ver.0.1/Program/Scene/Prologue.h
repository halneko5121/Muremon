//---------------------------------------------
//
//      あらすじ
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"
#include "Program/Util/Control.h"

#define OUTLINE_CENTER	(300)	//今の所、仮設定

enum TEXTURE_DATA_PROLOGUE
{
	T_PROLOGUE,
};

enum RECT_DATA_PROLOGUE
{
	R_PROLOGUE,
};

enum PROLOGUE_FADE_MODE
{
	PR_USUALLY,		//通常
	PR_FADE_OUT,	//フェードアウト
};

class C_Prologue:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;
	C_DSound	*sound;
	C_Control	*key;

	int move_count;	//タイムカウント

	int alpha;	//アルファ値

	float add_outline;

	bool outline_center;

	int fade_flag;

	int alpha_count;	//アルファカウント

	bool scene_change;	//シーンが変わる時を知らせる
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score);

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void FadeControl();		//フェードコントロール

	void FadeOut();			//フェードアウト

	C_Prologue(void);
	~C_Prologue(void);
};
