#pragma once

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/DefineGame.h"

enum MISSION_STATE
{
	MISSION_START,
	MISSION_MIDDLE,
	MISSION_SEIKO,
	MISSION_SIPPAI,
	MISSION_OUGI,
	MISSION_NEGATIVE,
	MISSION_END,
};

class Mission
{
private:
	Texture	*texture;
	Vertex	*vertex;

	LPDIRECT3DDEVICE9 pDevice;

	D3DXVECTOR2 mission_start;	//みっしょん開始の位置

	int alpha_count;	//

	int alpha;			//

	int alpha_push_z;	//

	int flag_z;			//

	int flag_draw;		//

	bool flag_sound;	//

	bool flag_sound2;	//

	int cnt_move;		//

	int mission_no;		//どのミッションが選択されたかを記憶

	int mission_state;	//ミッションが今どの状況か

	int time;	//時間

	int flag_time_cnt;	//タイムカウントのフラグ

	int success_type_count;	//タイピング時正解しているか判定

	int flag_mission_state;	//ミッション成功・失敗

	bool flag_init;		//初期化したかしてないか

	int key_cnt;		//キーの連打数を保存する変数

	int key_state;		//キーの状態を保存する変数

	int cnt_key_nikuman;	//にくまんの押されたキーの数をカウント

	int cnt_key_yoshitaro;	//吉たろうの押されたキーの数をカウント

	int cnt_key_noppo;		//のっぽの押されたキーの数をカウント
public:
	int GetCntKeyNikuman()		{ return cnt_key_nikuman; };
	int GetCntKeyYoshitaro()	{ return cnt_key_yoshitaro; };
	int GetCntKeyNoppo()		{ return cnt_key_noppo; };


	void Init(int cnt_nikuman,int cnt_yoshitaro,int cnt_noppo);

	int Control();

	void Draw();

	void FadeIn();

	void FadeOut();

	void DrawNumT();		//時間を表示

	void DrawCombo();

	void MissionSelect();	//みっしょんを決めたり初期化したり

	void MissionControl();
	void MissionControlD();

	void Mission1();	//『10秒以内に100回連打せよ！！』
	void Mission2();	//『10秒間でちょうど50回連打せよ！！』
	void Mission3();	//『10秒間でちょうど100回連打せよ！！』
	void Mission4();	//『「NIKUMANTOTUGEKI」と入力せよ！！』
	void Mission5();	//『「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！』
	void Mission6();	//『「YOSITAROHIPATACK」と入力せよ！！』
	void Mission7();	//『「YOSITAROHUSENSHOOT」と入力せよ！！』
	void Mission8();	//『「NOPPOKOKEPPETI」と入力せよ！！』
	void Mission9();	//『「NOPPOBOKＵSIRIKOPUTA」と入力せよ！！』
	void Mission10();	//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void Mission11();	//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void Mission12();	//『10秒以内に「にくまん」の連打数を一番高くしろ！』
	void Mission13();	//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
	void Mission14();	//『10秒以内に「のっぽ」の連打数を一番高くしろ！』

	void Mission1D();	//『10秒以内に100回連打せよ！！』
	void Mission2D();	//『10秒間でちょうど50回連打せよ！！』
	void Mission3D();	//『10秒間でちょうど100回連打せよ！！』
	void Mission4D();	//『「NIKUMANTOTUGEKI」と入力せよ！！』
	void Mission5D();	//『「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！』
	void Mission6D();	//『「YOSITAROHIPATACK」と入力せよ！！』
	void Mission7D();	//『「YOSITAROHUSENSHOOT」と入力せよ！！』
	void Mission8D();	//『「NOPPOKOKEPPETI」と入力せよ！！』
	void Mission9D();	//『「NOPPOBOKＵSIRIKOPUTA」と入力せよ！！』
	void Mission10D();	//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void Mission11D();	//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void Mission12D();	//『10秒以内に「にくまん」の連打数を一番高くしろ！』
	void Mission13D();	//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
	void Mission14D();	//『10秒以内に「のっぽ」の連打数を一番高くしろ！』

	Mission(Texture* m_texture,Vertex* m_vertex,LPDIRECT3DDEVICE9 apDev);
	~Mission(void);
};
