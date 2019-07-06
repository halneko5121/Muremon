//---------------------------------------------
//
//      タイトル
//      作成開始日:	3月17日
//			更新日:	3月20日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/Scene/SceneBase.h"

class SceneTitle : public SceneBase
{
private:
	D3DXVECTOR2 cursor_posi;
	D3DXVECTOR2 title_posi;

	int time_count;			//ロゴのタイムカウント

	int alpha_z;			//

	int draw_scene_change;	//ロゴ内のグラフィックの変化を知らせる。

	int flag_select;		//カーソルが選択しているものを判別。

	int flag_scene_change;	//どのシーンに変わるかを判断

	unsigned int anime_cursor;	//カーソルアニメーション

	bool flag_z;

	int flag_draw;

	int cnt_move;
public:
	void ImpleInit() override;
	bool Update() override;
	void Draw() override;
	int End() override;

	void PosiDrawControl();

	void KeyControl();

	SceneTitle();
	~SceneTitle();
};
