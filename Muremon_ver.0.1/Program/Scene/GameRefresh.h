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
#include "Program/Actor/Boss.h"
#include "Program/Actor/Actornikuman.h"
#include "Program/Actor/ActorNoppo.h"
#include "Program/Actor/ActorYoshi.h"
#include "Program/Util/Control.h"
#include "Program/D_Game.h"

class C_GameRefresh:public C_SceneManage
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;
	C_DSound	*sound;
	C_Control	*key;

	C_Chara_Nikuman		*pNiku;
	C_Chara_Noppo		*pNoppo;
	C_Chara_Yoshi		*pYoshi;

	C_Boss				*boss;

private:
	int alpha;	//アルファ値

	int alpha_count;	//アルファのディレイ

	int start_alpha;	//げ～むすた～とのアルファ差分

	int game_state;		//ゲームの状態(スタート・すっきりゲーム)

	int flag_fade;		//フェードインアウトなどの段階を知らせる

	int flag_fade_start;	//げ～むすた～とのフェードイン・フェードアウトを知らせるのに使用

	bool flag_fade_in;		//フェードインが終わった状態かを知らせる

	int key_state;			//キーの状態

	int cnt_key_nikuman;	//にくまんの押されたキーの数をカウント

	int cnt_key_yoshitaro;	//吉たろうの押されたキーの数をカウント

	int cnt_key_noppo;		//のっぽの押されたキーの数をカウント

	bool hit_niku;

	bool hit_yoshi;

	bool hit_noppo;

	bool hit_effect_flag;

	int hit_effect_alpha;

	int hit_effect_time;

	float chara_atk_y;

	float niku_atk_y;

	float yoshi_atk_y;

	float noppo_atk_y;

	bool scene_change;	//シーンが変わる時を知らせる
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score);

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void DrawNum();

	void DrawGageHp();

	void FadeControl();		//フェードコントロール		

	void FadeIn();			//フェードイン

	void FadeOut();			//フェードアウト

	void BossDraw();
	
	void BossControl();

	void Calculate(int getchara);	//計算処理（総ダメージ、必殺ゲージ増加）

	void ScoreDamageDraw();	//総ダメージスコア

	void HitFlagInit();

	void HitEffectDraw();

	C_GameRefresh(void);
	~C_GameRefresh(void);
};
