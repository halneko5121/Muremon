//---------------------------------------------
//
//      ゲーム本編
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#pragma once

#include "Program/gManage/SceneManage.h"
#include "Library/Texture.h"
#include "Library/Vertex.h"
#include "Program/Scene/Mission.h"
#include "Program/Actor/Boss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/Util/Control.h"
#include "Program/D_Game.h"

#define NEGATIVE_PAR1	(40)
#define NEGATIVE_PAR2	(60)
#define NEGATIVE_PAR3	(70)
#define NEGATIVE_PAR4	(100)

enum NEGATIVE_DATA
{
	NO_NEGATIVE,
	SPEED_UP,
	RECOVER,
	SLIDE_IN,
	ATTACK_DOWN,
};

class C_GameNormal:public C_SceneManage
{
public:
	C_GameNormal(void);
	~C_GameNormal(void);

	void InitScene(LPDIRECT3DDEVICE9 apDev, /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound, int score);

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void DrawNum();		//連打数
	void DrawNumS();	//スコア
	void DrawNumT();	//タイム
	void DrawGageHp();
	void DrawGageMission();

	void ControlMissionOugi();		// アクシデント奥義のコントロール
	void DrawMissionOugi();			// アクシデント奥義を描画
	void ControlMissionNegative();	// ミッション失敗時の処理
	void NegativeSelect();			// どの処理にするかを判断
	void DrawMissionNegative();		// ミッション失敗時の処理

	void ReCover();					// ミッション失敗で下がったものを元に戻す
	void FadeControl();				// フェードコントロール		
	void FadeIn();					// フェードイン
	void FadeOut();					// フェードアウト
	void HitEffectDraw();

private:
	C_Texture	*texture;
	C_Vertex	*vertex;
	C_DSound	*sound;
	C_Control	*key;
	C_Mission	*mission;

	C_Boss		*boss;

	C_ActorNikuman		*pNiku;
	C_ActorNoppo		*pNoppo;
	C_ActorYoshi		*pYoshi;

	int time;	//時間をはかる

	bool flag_pose;	//ポーズをしているかしていないか

	int score;

	int alpha;	//アルファ値

	int alpha_count;	//アルファのディレイ

	int start_alpha;	//げ～むすた～とのアルファ差分

	int game_state;		//ゲームの状態(スタート・すっきりゲーム)

	int flag_fade;		//フェードインアウトなどの段階を知らせる

	int flag_fade_start;	//げ～むすた～とのフェードイン・フェードアウトを知らせるのに使用

	bool flag_fade_in;		//フェードインが終わった状態かを知らせる

	int key_state;			//キーの状態

	int mission_state_keep;	//ミッションの状態をキープ

	int cnt_key_nikuman;	//にくまんの押されたキーの数をカウント

	int cnt_key_yoshitaro;	//吉たろうの押されたキーの数をカウント

	int cnt_key_noppo;		//のっぽの押されたキーの数をカウント

	int flag_init;			//初期化したかどうか

	bool flag_red;			//色かえる

	int mission_gage;		//必殺ゲージ

	bool hit_niku;

	bool hit_yoshi;

	bool hit_noppo;

	bool hit_effect_flag;

	//ヒットエフェクト

	int hit_effect_alpha;

	int hit_effect_time;

	float chara_atk_y;

	bool flag_sound;

	//奥義内で使用
	int alpha_font;
	int time_cnt;

	int speed_x;

	POSI wave_posi;

	//NEGATIVEで使用
	int negative_state;
	int negative_damege;
	
	bool scene_change;	//シーンが変わる時を知らせる
};
