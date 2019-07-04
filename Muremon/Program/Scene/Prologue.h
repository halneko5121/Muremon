//---------------------------------------------
//
//      あらすじ
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
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

class C_Prologue:public C_SceneBase
{
private:
	C_Control	*key;

	int move_count;	//タイムカウント

	int alpha;	//アルファ値

	float add_outline;

	bool outline_center;

	int fade_flag;

	int alpha_count;	//アルファカウント

public:
	void Init() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void FadeControl();		//フェードコントロール

	void FadeOut();			//フェードアウト

	C_Prologue(void);
	~C_Prologue(void);
};
