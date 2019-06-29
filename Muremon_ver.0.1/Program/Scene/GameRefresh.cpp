//---------------------------------------------
//
//      ゲーム本編
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#include "GameRefresh.h"

POS_CC<float> boss_cc = { 600, 350 };

C_GameRefresh::C_GameRefresh(void)
{
	vertex  = new C_Vertex();
	texture = new C_Texture();
	key		= new C_Control();
	sound	= new C_DSound();

	start_alpha = alpha = 0;	//アルファ値

	alpha_count = 0;

	flag_fade = GS_FADE_IN;

	game_state = G_START_SCENE;

	key_state = 0;

	cnt_key_nikuman = cnt_key_yoshitaro = cnt_key_noppo = 0;

	flag_fade_start = 0;

	flag_fade_in = false;

	scene_change = true;

	hit_effect_alpha = 0;
	hit_effect_flag = false;
	hit_effect_time = 0;

	hit_niku = false;

	hit_yoshi = false;

	hit_noppo = false;

	chara_atk_y = 0;
}

C_GameRefresh::~C_GameRefresh(void)
{
}

void C_GameRefresh::InitScene(LPDIRECT3DDEVICE9 apDev , C_DFont *apFont, C_DSound *apSound,int score)
{
	C_SceneManage::InitScene(apDev,apFont,apSound,0);

	sound = apSound;

	pNiku	= new C_Chara_Nikuman(vertex,texture,apDev,apSound);
	pNoppo	= new C_Chara_Noppo(vertex,texture,apDev,apSound);
	pYoshi	= new C_Chara_Yoshi(vertex,texture,apDev,apSound);

	pNiku->Init();
	pNoppo->Init();
	pYoshi->Init();
	
	//boss->Init();

	boss = new C_Boss(texture,vertex,pDevice,apSound);

	texture->LoadTextureData("Data\\TextureData\\gamenormal.txt",apDev);		//絵の読み込み
	vertex->LoadRect("Data\\RectData\\gamenormal.txt");
}

bool C_GameRefresh::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_GameRefresh::ControlScene()
{
	if(game_state == G_START_SCENE){
		sound->SoundPlay(false,S_GAME_START);
		FadeControl();
	}
	else if(game_state == G_GAME_SCENE){

		boss_cc.x =	boss->boss_move_x;
		boss_cc.y = boss->boss_move_y;
	
		sound->SoundPlay(true,S_BGM_BATTLE);

		key_state = key->KeyCheckGame();

		pNiku->Control(key_state, boss_cc, S_NIKUMAN,R_NIKU_G_ATK1,boss->boss_fall_flag);

		pYoshi->Control(key_state, boss_cc, S_YOSHI_HIP,R_YOSHI_G_ATK1,boss->boss_fall_flag);

		pNoppo->Control(key_state, boss_cc, S_NOPPO_KOKE,R_NOPPO_G_ATK1,boss->boss_fall_flag);
	
		hit_niku  = pNiku->GetFlagHit();//あたったというフラグが帰ってきます
		
		hit_yoshi = pYoshi->GetFlagHit();//これをつかってダメージなどを

		hit_noppo = pNoppo->GetFlagHit();//反映させてください

		if(hit_niku)
		{
			boss->hit_count++;
			boss->boss_life-=NIKUMAN_DAMAGE;
			hit_effect_flag = true;
			chara_atk_y = pNiku->m_chara_y;
			pNiku->SetFlagHit(false);
		}

		if(hit_yoshi)
		{
			boss->hit_count++;
			boss->boss_life-=YOSHITARO_DAMAGE;
			hit_effect_flag = true;
			chara_atk_y = pYoshi->m_chara_y;
			pYoshi->SetFlagHit(false);
		}

		if(hit_noppo)
		{
			boss->hit_count++;
			boss->boss_life-=NOPPO_DAMAGE;
			hit_effect_flag = true;
			chara_atk_y = pNoppo->m_chara_y;
			pNoppo->SetFlagHit(false);
		}

		if(key_state == KEY_GROUND_2 || key_state == KEY_SKY_2){
			cnt_key_nikuman++;
		}
		else if(key_state == KEY_GROUND_1 || key_state == KEY_SKY_1){
			cnt_key_yoshitaro++;
		}
		else if(key_state == KEY_GROUND_3 || key_state == KEY_SKY_3){
			cnt_key_noppo++;
		}

		if(GetAsyncKeyState(VK_RETURN)){	//エンターキーが押されたらタイトルに戻る
			scene_change = false;
		}

		//boss->RefreshControl();
		boss->BossControl(PLAY_REFRESH);

		if(!boss->boss_fall_flag)
		{
			if(hit_effect_flag) 
			{
				hit_effect_alpha = 255;
				hit_effect_time++;
				if(hit_effect_time == 1)
				{
					hit_effect_flag=false;
					hit_effect_time=0;
				}		
			}
			else{
					hit_effect_alpha = 0;
					hit_effect_time = 0;
			}
		}
		else{
			hit_effect_flag = false;
			hit_effect_alpha=0;
		}
	}
}

void C_GameRefresh::DrawScene()
{
	if(game_state == G_START_SCENE){
		vertex->SetTextureData(texture->GetTextureData(T_GAME_BG),pDevice);

		vertex->SetColor(alpha,255,255,255);

		vertex->DrawF(G_BG_X,G_BG_Y,R_GAME_BG);

		vertex->DrawF(G_FLAG_X,G_FLAG_Y,R_FLAG);

		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);

		vertex->SetColor(alpha,255,255,255);

		vertex->DrawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//ステータス枠描画

		vertex->DrawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);				//にくまん顔
		vertex->DrawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);			//よしたろう顔
		vertex->DrawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);					//のっぽ顔

		DrawNum();

		vertex->DrawF(G_HP_X,G_HP_Y,R_HP);								//しゃっくの体力
		vertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);						//体力ゲージ

		DrawGageHp();

		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);

		vertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);					//体力ゲージ枠

		vertex->SetColor(alpha - start_alpha,255,255,255);
		vertex->DrawF(G_BG_X,G_BG_Y,R_GAME_START);						//ゲームスタート
	}
	else if(game_state == G_GAME_SCENE){
		vertex->SetTextureData(texture->GetTextureData(T_GAME_BG),pDevice);

		vertex->SetColor(alpha,255,255,255);

		vertex->DrawF(G_BG_X,G_BG_Y,R_GAME_BG);	//背景

		vertex->DrawF(G_FLAG_X,G_FLAG_Y,R_FLAG);	//旗

		boss->BossDraw();
		boss->FallDraw();

		//BossDraw();
		//BossNoFontDraw();

		HitEffectDraw();

		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);

		vertex->SetColor(alpha,255,255,255);

		vertex->DrawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//ステータス枠描画

		vertex->DrawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);	//にくまん顔
		vertex->DrawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);	//よしたろう顔
		vertex->DrawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);	//のっぽ顔

		DrawNum();

		vertex->DrawF(G_HP_X,G_HP_Y,R_HP);	//しゃっくの体力
		vertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ

		DrawGageHp();

		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);

		vertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//体力ゲージ枠

		//キャラ達
		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);

		vertex->SetTextureData(texture->GetTextureData(T_CAHRA_NOPPO),pDevice);
		pNoppo->Draw(R_NOPPO_G_ATK1);

		vertex->SetTextureData(texture->GetTextureData(T_CAHRA_YOSHI),pDevice);
		pYoshi->Draw(R_YOSHI_G_ATK1);

		vertex->SetTextureData(texture->GetTextureData(T_CAHRA_NIKU),pDevice);
		pNiku->Draw(R_NIKU_G_ATK1);

		//エフェクトフォント類
		vertex->SetTextureData(texture->GetTextureData(T_GAME_EFFECT),pDevice);
		pNoppo->DrawEffectFont(R_NOPPO_PETI);
		pYoshi->DrawEffectFont(R_YOSHI_BOYO);
		pNiku->DrawEffectFont(R_NIKU_BETYA);

		vertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//体力ゲージ枠
	}
}

int C_GameRefresh::EndScene()
{
	//タイトルへ
	ChangeScene(TITLE);

	sound->SoundStop(true,S_BGM_BATTLE);

	texture->AllReleaseTexture();
	vertex->AllReleaseRect();

	return 0;
}

void C_GameRefresh::FadeControl()
{
	switch(flag_fade)
	{
	case GS_FADE_IN:
		FadeIn();
		break;
	case GS_USUALLY:
		FadeOut();
		break;
	}
}

void C_GameRefresh::FadeIn()
{
	if(flag_fade_start > 60){
		start_alpha += G_ALPHA_INCREASE - 10;
		if(start_alpha > 255){
			start_alpha = 255;
			game_state = G_GAME_SCENE;
		}
		return ;
	}
	else if(flag_fade_start >= 1){
		flag_fade_start++;
		return ;
	}

	if(flag_fade_in){
		start_alpha -= G_ALPHA_INCREASE - 10;
		if(start_alpha < 0){
			start_alpha = 0;
			flag_fade_start = 1;
			//サウンド鳴らす予定
		}
		return ; 
	}
	else if(alpha_count++ > 1){
		alpha += G_ALPHA_INCREASE;
		if(alpha > G_MAX_ALPHA){
			alpha = G_MAX_ALPHA;
			flag_fade_in = true;
		}
		alpha_count = 0;
		start_alpha = alpha;
	}
}

void C_GameRefresh::FadeOut()
{
	if(alpha == 0) { return ; }
	else if(alpha_count++ > 1){
		alpha -= G_ALPHA_INCREASE;
		if(alpha < 0) { alpha = 0; }
		alpha_count = 0;
	}
}

void C_GameRefresh::DrawNum()
{
	//にくまん
	for(int i = 0;i < 4;i++){
		int num = cnt_key_nikuman;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		vertex->DrawF(G_PUSHNUM + 20.f * i,G_F_NIKUMAN_Y,R_0 + num%10);
	}
	//よしたろう
	for(int i = 0;i < 4;i++){
		int num = cnt_key_yoshitaro;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		vertex->DrawF(G_PUSHNUM + 20.f * i,G_F_YOSHITARO_Y,R_0 + num%10);
	}
	//のっぽ
	for(int i = 0;i < 4;i++){
		int num = cnt_key_noppo;
		for(int j = 1;j < 4 - i;j++){
			num = (num / 10);
		}
		vertex->DrawF(G_PUSHNUM + 20.f * i,G_F_NOPPO_Y,R_0 + num%10);
	}
}

void C_GameRefresh::DrawGageHp()
{
	float num = boss->boss_life / boss->max_boss_life;

	vertex->SetScale(num,1.f);

	vertex->SetColor(alpha,255,0,0);
	
	vertex->DrawF(G_GAGE_X - (1.f - num) * 100.f,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ
}

void C_GameRefresh::HitEffectDraw()
{
	vertex->SetTextureData(texture->GetTextureData(T_GAME_EFFECT),pDevice);
	vertex->SetColor(hit_effect_alpha,255,255,255);
	vertex->DrawF((float)boss->boss_move_x - HIT_EFFECT_X,chara_atk_y,R_HIT_EFFECT);
}

void C_GameRefresh::HitFlagInit()
{
	hit_niku = false;

	hit_yoshi = false;

	hit_noppo = false;
}