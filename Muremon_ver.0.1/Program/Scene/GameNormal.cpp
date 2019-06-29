//---------------------------------------------
//
//      ゲーム本編
//      作成開始日:	3月17日
//			更新日:	3月18日
//			作成者:	平野
//
//---------------------------------------------
#include "GameNormal.h"

POS_CC<float> boss_cc2 = { 600, 350 };

C_GameNormal::C_GameNormal(void)
{
	vertex  = new C_Vertex();
	texture = new C_Texture();
	key		= new C_Control();
	sound	= new C_DSound();

	score = 0;

	flag_pose = false;

	time = TIME_LIMIT;

	start_alpha = alpha = 0;	//アルファ値

	alpha_count = 0;

	flag_fade = GS_FADE_IN;

	game_state = G_START_SCENE;

	key_state = 0;

	cnt_key_nikuman = cnt_key_yoshitaro = cnt_key_noppo = 0;

	mission_state_keep = 0;

	flag_fade_start = 0;

	flag_fade_in = false;

	flag_init = false;

	scene_change = true;

	mission_gage = 0;

	flag_red = false;

	hit_effect_alpha = 0;
	hit_effect_flag = false;
	hit_effect_time = 0;

	hit_niku = false;

	hit_yoshi = false;

	hit_noppo = false;

	chara_atk_y = 0;

	flag_sound = true;

	//奥義
	alpha_font = 0;
	time_cnt = 0;
	wave_posi.x = WAVE_INIT_X;
	wave_posi.y = WAVE_INIT_Y;

	//NEGATIVE
	negative_state = NO_NEGATIVE;
	negative_damege = 1;
}

C_GameNormal::~C_GameNormal(void)
{
}

void C_GameNormal::InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score)
{
	C_SceneManage::InitScene(apDev,/*apinput,*/apFont,apSound,0);

	sound = apSound;

	pNiku	= new C_ActorNikuman(vertex, texture, apSound);
	pNoppo	= new C_ActorNoppo(vertex, texture, apSound);
	pYoshi	= new C_ActorYoshi(vertex, texture, apSound);

	pNiku->Init();
	pNoppo->Init();
	pYoshi->Init();

	boss = new C_Boss(texture,vertex,pDevice,apSound);

	texture->LoadTextureData("Data\\TextureData\\gamenormal.txt",apDev);		//絵の読み込み
	vertex->LoadRect("Data\\RectData\\gamenormal.txt");

	mission = new C_Mission(texture,vertex,pDevice,apSound);
}

bool C_GameNormal::RunScene()
{
	ControlScene();
	DrawScene();
	return scene_change;
}

void C_GameNormal::ControlScene()
{
	if(game_state == G_START_SCENE){
		sound->SoundPlay(false,S_GAME_START);
		FadeControl();
	}
	else if(game_state == G_GAME_SCENE){

		boss_cc2.x = boss->boss_move_x;
		boss_cc2.y = boss->boss_move_y;

		if(game_state != G_GAME_OVER){
			if((boss_cc2.x - 150) < 500){
				sound->SoundPlay(true,S_SAIREN);
			}
			else sound->SoundStop(true,S_SAIREN);
		}

		key_state = key->KeyCheckGame();

		if(key_state == KEY_ENTER){
			if(flag_pose){
				flag_pose = false;
			}
			else{
				flag_pose = true;
			}
		}

		if(flag_pose){
			return;
		}

		//ミッションが起動する段階までいったら
		//mission_gage = 5000;
		if(mission_gage >= MISSION_GAGE_MAX){
			if(!flag_init){
				sound->SoundPlay(false,S_OSIRASE);
				mission->Init(cnt_key_nikuman,cnt_key_yoshitaro,cnt_key_noppo);
				flag_init = true;
			}
			if(mission_state_keep < MISSION_OUGI){
				mission_state_keep = mission->Control();
				if(cnt_key_nikuman != mission->GetCntKeyNikuman()){
					cnt_key_nikuman = mission->GetCntKeyNikuman();
				}
				if(cnt_key_yoshitaro != mission->GetCntKeyYoshitaro()){
					cnt_key_yoshitaro = mission->GetCntKeyYoshitaro();
				}
				if(cnt_key_noppo != mission->GetCntKeyNoppo()){
					cnt_key_noppo = mission->GetCntKeyNoppo();
				}
			}
			else if(mission_state_keep == MISSION_OUGI){
				ControlMissionOugi();
			}
			else if(mission_state_keep == MISSION_NEGATIVE){
				ControlMissionNegative();
			}
			else if(mission_state_keep == MISSION_END){
				negative_state = NO_NEGATIVE;
				time_cnt = 0;
				mission_state_keep = 0;
				mission_gage = 0;
				flag_init = false;
			}
			return ;
		}

		if(time == 0){
			game_state = G_GAME_CLEAR;
			flag_fade_start = 0;
			return ;
		}

		sound->SoundPlay(true,S_BGM_BATTLE);

		pNiku->Control(key_state, boss_cc2, S_NIKUMAN,R_NIKU_G_ATK1,boss->boss_fall_flag);

		pYoshi->Control(key_state, boss_cc2, S_YOSHI_HIP,R_YOSHI_G_ATK1,boss->boss_fall_flag);

		pNoppo->Control(key_state, boss_cc2, S_NOPPO_KOKE,R_NOPPO_G_ATK1,boss->boss_fall_flag);

		time -= 1;

		hit_niku  = pNiku->GetFlagHit();//あたったというフラグが帰ってきます

		hit_yoshi = pYoshi->GetFlagHit();//これをつかってダメージなどを

		hit_noppo = pNoppo->GetFlagHit();//反映させてください

		if(hit_niku)
		{
			boss->hit_count++;
			boss->boss_life -= NIKUMAN_DAMAGE / negative_damege;
			mission_gage += NIKUMAN_GAGE;
			score += NIKUMAN_SCORE;
			hit_effect_flag = true;
			chara_atk_y = pNiku->m_chara_y;
			pNiku->SetFlagHit(false);
		}

		if(hit_yoshi)
		{
			boss->hit_count++;
			boss->boss_life -= YOSHITARO_DAMAGE / negative_damege;
			mission_gage += YOSHITARO_GAGE;
			score += YOSHITARO_SCORE;
			hit_effect_flag = true;
			chara_atk_y = pYoshi->m_chara_y;
			pYoshi->SetFlagHit(false);
		}

		if(hit_noppo)
		{
			boss->hit_count++;
			boss->boss_life -= NOPPO_DAMAGE / negative_damege;
			mission_gage += NOPPO_GAGE;
			score += YOSHITARO_SCORE;
			hit_effect_flag = true;
			chara_atk_y = pNoppo->m_chara_y;
			pNoppo->SetFlagHit(false);
		}

		if(key_state == KEY_GROUND_2 || key_state == KEY_SKY_2){	//にくまん
			cnt_key_nikuman++;
		}
		else if(key_state == KEY_GROUND_1 || key_state == KEY_SKY_1){	//よしたろう
			cnt_key_yoshitaro++;
		}
		else if(key_state == KEY_GROUND_3 || key_state == KEY_SKY_3){	//のっぽ
			cnt_key_noppo++;
		}

		ReCover();

		//if(GetAsyncKeyState(VK_RETURN)){	//エンターキーが押されたらタイトルに戻る
		//	scene_change = false;
		//}
		
		//boss->NormalControl();
		boss->BossControl(PLAY_NORMAL);

		//ゲームオーバー条件
		if(boss->boss_win_flag)
		{
			game_state = G_GAME_OVER;
			flag_fade_start = 0;
			sound->SoundStop(true,S_SAIREN);
			return ;
		}

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
	else if(game_state == G_GAME_OVER){
		FadeControl();
	}
	else if(game_state == G_GAME_CLEAR){
		FadeControl();
	}
}

void C_GameNormal::DrawScene()
{
	vertex->SetTextureData(texture->GetTextureData(T_GAME_BG),pDevice);

	/*if((boss_cc2.x - 150) < 500){
		if(flag_red){
			vertex->SetColor(alpha - 55,200,0,0);
			flag_red = false;
		}
		else{
			vertex->SetColor(alpha - 55,255,255,255);
			flag_red = true;
		}
	}*/
	if(alpha - 55 < 0){
		vertex->SetColor(0,255,255,255);
	}
	else{
		vertex->SetColor(alpha - 55,255,255,255);
	}

	vertex->DrawF(G_BG_X,G_BG_Y,R_GAME_BG);

	vertex->DrawF(G_FLAG_X,G_FLAG_Y,R_FLAG);

	if(game_state == G_START_SCENE){
		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);

		vertex->SetColor(alpha - start_alpha,255,255,255);

		vertex->DrawF(G_BG_X,G_BG_Y,R_GAME_START);	//ゲームスタート
	}
	else if(game_state == G_GAME_SCENE){

		boss->BossDraw();

		boss->FallDraw();

		HitEffectDraw();
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
	}
	else if(game_state == G_GAME_OVER){
		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
		vertex->SetColor(alpha - start_alpha,255,255,255);
		vertex->DrawF(G_BG_X,G_BG_Y,R_GAME_OVER);	//ゲームオーバー
		if(flag_sound){
			sound->SoundPlay(false,S_OVER);
			flag_sound = false;
		}
	}
	else if(game_state == G_GAME_CLEAR){
		vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);
		vertex->SetColor(alpha - start_alpha,255,255,255);
		vertex->DrawF(G_BG_X,G_BG_Y,R_GAME_CLEAR);	//ゲームクリア
		if(flag_sound){
			sound->SoundPlay(false,S_G_CLEAR);
			flag_sound = false;
		}
	}

	if(mission_state_keep == MISSION_OUGI){
		DrawMissionOugi();
	}
	else if(mission_state_keep == MISSION_NEGATIVE){
		DrawMissionNegative();
	}

	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);

	vertex->SetColor(alpha,255,255,255);

	vertex->DrawF(G_STATE_FRAME_X,G_STATE_FRAME_Y,R_STATE_FRAME);	//ステータス枠描画

	vertex->DrawF(G_SCORE_X,G_SCORE_Y,R_SCORE);		//すこあ

	DrawNumS();

	vertex->DrawF(G_TIME_X,G_TIME_Y,R_TIME);		//たいむ

	DrawNumT();

	vertex->DrawF(G_FACE_X,G_F_NIKUMAN_Y,R_F_NIKUMAN);	//にくまん顔
	vertex->DrawF(G_FACE_X,G_F_YOSHITARO_Y,R_F_YOSHITARO);	//よしたろう顔
	vertex->DrawF(G_FACE_X,G_F_NOPPO_Y,R_F_NOPPO);	//のっぽ顔

	DrawNum();

	vertex->DrawF(G_MISSION_X,G_MISSION_Y,R_MISSION_GAGE);	//みっしょんげ～じ
	vertex->DrawF(G_GAGE_M_X,G_GAGE_M_Y,R_GAGE_IN);	//みっしょんゲージ

	DrawGageMission();

	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);

	vertex->DrawF(G_GAGE_M_X,G_GAGE_M_Y,R_GAGE_FRAME);	//みっしょんゲージ枠

	vertex->DrawF(G_HP_X,G_HP_Y,R_HP);	//しゃっくの体力
	vertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ

	DrawGageHp();

	vertex->SetTextureData(texture->GetTextureData(T_GAME_FONT),pDevice);

	vertex->DrawF(G_GAGE_X,G_GAGE_Y,R_GAGE_FRAME);	//体力ゲージ枠

	if(mission_gage >= MISSION_GAGE_MAX){
		mission->Draw();
	}
}

int C_GameNormal::EndScene()
{
	//ゲームオーバーの場合
	ChangeScene(RANKING);

	sound->SoundStop(true,S_BGM_BATTLE);

	texture->AllReleaseTexture();
	vertex->AllReleaseRect();
	delete mission;

	return score;
}

void C_GameNormal::FadeControl()
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

void C_GameNormal::FadeIn()
{
	if(flag_fade_start > 60){
		start_alpha += G_ALPHA_INCREASE - 10;
		if(start_alpha > 255){
			start_alpha = 255;
			if(game_state == G_START_SCENE){
				game_state = G_GAME_SCENE;
			}
			else if(game_state == G_GAME_OVER || game_state == G_GAME_CLEAR){
				scene_change = false;
			}
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

void C_GameNormal::FadeOut()
{
	if(alpha == 0) { return ; }
	else if(alpha_count++ > 1){
		alpha -= G_ALPHA_INCREASE;
		if(alpha < 0) { alpha = 0; }
		alpha_count = 0;
	}
}

void C_GameNormal::DrawNum()
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
			num = num / 10;
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

void C_GameNormal::DrawNumS()
{
	//スコア
	for(int i = 0;i < 9;i++){
		int num = score;
		for(int j = 1; j < 9 - i;j++){
			num = num / 10;
		}
		vertex->DrawF(G_SCORENUM_X + 20.f * i,G_SCORENUM_Y,R_0 + num%10);
	}
}

void C_GameNormal::DrawNumT()
{
	//タイム
	for(int i = 0;i < 5;i++){
		int num = time;
		if(i != 2){
			int a = 0;
			if(i > 2){
				a = i - 1;
			}
			else{
				a = i;
			}
			for(int j = 0;j < 4 - a;j++){
				if(j == 0){
					num = num / 60;
				}
				else if(j == 2){
					num = num / 6;
				}
				else{
					num = num / 10;
				}
			}
			if(i == 0 || i == 3){
				vertex->DrawF(G_TIMENUM_X + 20.f * i,G_TIMENUM_Y,R_0 + num%6);
			}
			else{
				vertex->DrawF(G_TIMENUM_X + 20.f * i,G_TIMENUM_Y,R_0 + num%10);
			}
		}
		else{
			vertex->DrawF(G_TIMENUM_X + 20.f * i,G_TIMENUM_Y,R_SEMICORON);
		}
	}
}

void C_GameNormal::DrawGageHp()
{
	float num = boss->boss_life / boss->max_boss_life;

	vertex->SetScale(num,1.f);

	vertex->SetColor(alpha,200,30,30);
	
	vertex->DrawF(G_GAGE_X - (1.f - num) * 100.f,G_GAGE_Y,R_GAGE_IN);	//体力ゲージ
}

void C_GameNormal::HitEffectDraw()
{
	vertex->SetTextureData(texture->GetTextureData(T_GAME_EFFECT),pDevice);
	vertex->SetColor(hit_effect_alpha,255,255,255);
	vertex->DrawF(boss->boss_move_x - HIT_EFFECT_X,chara_atk_y,R_HIT_EFFECT);
}
void C_GameNormal::DrawGageMission()
{
	float num = (float)mission_gage / (float)MISSION_GAGE_MAX;

	vertex->SetScale(num,1.f);

	vertex->SetColor(alpha,30,30,200);
	
	vertex->DrawF(G_GAGE_M_X - (1.f - num) * 100.f,G_GAGE_M_Y,R_GAGE_IN);	//ミッションゲージ
}

void C_GameNormal::ControlMissionOugi()
{
	if(time_cnt >= 0 && 60 > time_cnt){
		alpha_font += 5;
		if(alpha_font > 255){
			alpha_font = 255;
		}
	}
	else if(time_cnt >= 60 && 120 > time_cnt){
		alpha_font = 255;
	}
	else if(time_cnt >= 120 && 180 > time_cnt){
		alpha_font -= 5;
		if(alpha_font < 0){
			alpha_font = 0;
		}
	}
	else if(time_cnt >= 180 && 210 > time_cnt){
		if(time_cnt == 180){
			sound->SoundPlay(false,S_NAMI);
		}
	}
	else if(time_cnt >= 210 && 420 > time_cnt){		//波を動かす(3.5sec)
		wave_posi.x += WAVE_SPEED_X;
		wave_posi.y -= WAVE_UP_Y;
		if(time_cnt % 10 <= 4){
			wave_posi.y -= 2.f;
		}
		else if(time_cnt % 10 <= 9){
			wave_posi.y += 2.f;
		}
	}
	else if(time_cnt >= 420 && 450 > time_cnt){
	}
	else if(time_cnt >= 450 && 630 > time_cnt){
	}
	if(time_cnt > 630){
		boss->boss_life -= 7000;
		ReCover();
		mission_state_keep = MISSION_END;
		wave_posi.x = WAVE_INIT_X;
		wave_posi.y = WAVE_INIT_Y;
		score+=MISSION_CLEAR_SCORE;
	}
	time_cnt++;
}

void C_GameNormal::DrawMissionOugi()
{
	vertex->SetTextureData(texture->GetTextureData(T_MISSION),pDevice);

	vertex->SetColor(alpha_font,255,255,255);

	vertex->DrawF(400.f,300.f,R_MISSION_OSIRASE);

	vertex->DrawF(400.f,300.f,R_OUGI_FONT);

	vertex->SetTextureData(texture->GetTextureData(T_GAME_EFFECT),pDevice);

	vertex->DrawF(wave_posi.x,wave_posi.y,R_OUGI);
}

void C_GameNormal::ControlMissionNegative()
{
	NegativeSelect();

	negative_state = SLIDE_IN;

	if(time_cnt >= 0 && 60 > time_cnt){
		alpha_font += 5;
		if(alpha_font > 255){
			alpha_font = 255;
		}
	}
	else if(time_cnt >= 60 && 120 > time_cnt){
		alpha_font = 255;
	}
	else if(time_cnt >= 120 && 180 > time_cnt){
		alpha_font -= 5;
		if(alpha_font < 0){
			alpha_font = 0;
		}
	}
	else if(time_cnt >= 180){
		switch(negative_state)
		{
		case SPEED_UP:
			boss->speed_x = 3;
			break;
		case RECOVER:
			boss->boss_life = boss->max_boss_life;
			break;
		case SLIDE_IN:
			boss->boss_move_x = 500;
			break;
		case ATTACK_DOWN:
			negative_damege += 1;
			break;
		}
		mission_state_keep = MISSION_END;
	}
	time_cnt++;
}

void C_GameNormal::DrawMissionNegative()
{
	vertex->SetTextureData(texture->GetTextureData(T_MISSION),pDevice);

	vertex->SetColor(alpha_font,255,255,255);

	vertex->DrawF(400.f,300.f,R_MISSION_OSIRASE);

	vertex->DrawF(400.f,300.f,R_NEGATIVE1 + negative_state - 1);
}

void C_GameNormal::NegativeSelect()
{
	if(negative_state != 0){
		return ;
	}

	negative_state = rand()%100+1;

	if(negative_state > 0 && negative_state <= NEGATIVE_PAR1){
		negative_state = SPEED_UP;
	}
	else if(negative_state > NEGATIVE_PAR1 && negative_state <= NEGATIVE_PAR2){
		negative_state = RECOVER;
	}
	else if(negative_state > NEGATIVE_PAR2 && negative_state <= NEGATIVE_PAR3){
		negative_state = SLIDE_IN;
	}
	else if(negative_state > NEGATIVE_PAR3 && negative_state <= NEGATIVE_PAR4){
		negative_state = ATTACK_DOWN;
	}
}

void C_GameNormal::ReCover()
{
	if(boss->boss_life <= 0){
		negative_damege = 1;
	}
}
