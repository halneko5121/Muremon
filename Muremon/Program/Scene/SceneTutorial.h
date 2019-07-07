#pragma once
/******************************************************************
 *	@file	SceneTutorial.h
 *	@brief	チュートリアルシーン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

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
	void		impleInit() override;
	bool		update() override;
	void		draw() override;
	int			end() override;

	void		updateInput();		//キー操作
	void		updateDrawPos();	//描画位置などを決める
	void		fadeControl();		//フェードコントロール		
	void		fadeIn();			//フェードイン
	void		fadeOut();			//フェードアウト

	SceneTutorial();
	~SceneTutorial();
};
