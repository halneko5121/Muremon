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
	int		getCountKeyNikuman()		{ return cnt_key_nikuman; };
	int		getCountKeyYoshitaro()	{ return cnt_key_yoshitaro; };
	int		getCountKeyNoppo()		{ return cnt_key_noppo; };


	void	init(int cnt_nikuman,int cnt_yoshitaro,int cnt_noppo);

	int		update();

	void	draw();

	void	fadeIn();

	void	fadeOut();

	void	drawTime();		//時間を表示

	void	drawCombo();

	void	missionSelect();	//みっしょんを決めたり初期化したり

	void	updateMission();
	void	updateMissionD();

	void	updateMission1();	//『10秒以内に100回連打せよ！！』
	void	updateMission2();	//『10秒間でちょうど50回連打せよ！！』
	void	updateMission3();	//『10秒間でちょうど100回連打せよ！！』
	void	updateMission4();	//『「NIKUMANTOTUGEKI」と入力せよ！！』
	void	updateMission5();	//『「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！』
	void	updateMission6();	//『「YOSITAROHIPATACK」と入力せよ！！』
	void	updateMission7();	//『「YOSITAROHUSENSHOOT」と入力せよ！！』
	void	updateMission8();	//『「NOPPOKOKEPPETI」と入力せよ！！』
	void	updateMission9();	//『「NOPPOBOKＵSIRIKOPUTA」と入力せよ！！』
	void	updateMission10();	//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission11();	//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission12();	//『10秒以内に「にくまん」の連打数を一番高くしろ！』
	void	updateMission13();	//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
	void	updateMission14();	//『10秒以内に「のっぽ」の連打数を一番高くしろ！』

	void	updateMission1D();	//『10秒以内に100回連打せよ！！』
	void	updateMission2D();	//『10秒間でちょうど50回連打せよ！！』
	void	updateMission3D();	//『10秒間でちょうど100回連打せよ！！』
	void	updateMission4D();	//『「NIKUMANTOTUGEKI」と入力せよ！！』
	void	updateMission5D();	//『「NIKUMANINSEKIRAKKAJUTU」と入力せよ！！』
	void	updateMission6D();	//『「YOSITAROHIPATACK」と入力せよ！！』
	void	updateMission7D();	//『「YOSITAROHUSENSHOOT」と入力せよ！！』
	void	updateMission8D();	//『「NOPPOKOKEPPETI」と入力せよ！！』
	void	updateMission9D();	//『「NOPPOBOKＵSIRIKOPUTA」と入力せよ！！』
	void	updateMission10D();	//『10秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission11D();	//『5秒数えて前後1秒以内で「Ｚキー」を押せ！』
	void	updateMission12D();	//『10秒以内に「にくまん」の連打数を一番高くしろ！』
	void	updateMission13D();	//『10秒以内に「よしたろう」の連打数を一番高くしろ！』
	void	updateMission14D();	//『10秒以内に「のっぽ」の連打数を一番高くしろ！』

	Mission(Texture* m_texture,Vertex* m_vertex,LPDIRECT3DDEVICE9 apDev);
	~Mission(void);
};
