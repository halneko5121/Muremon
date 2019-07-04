//---------------------------------------------
//
//      ゲームオーバー
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

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

class SceneGameOver : public SceneBase
{
private:
	int alpha;	//アルファ値

	int fade_flag;

	int alpha_count;

public:
	void Init() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void FadeControl();		//フェードコントロール		

	void FadeIn();			//フェードイン

	void FadeOut();			//フェードアウト

	SceneGameOver();
	~SceneGameOver();
};
