#include "ActorYoshi.h"

CHARADATA init_charadata_yoshi = {
	(0.0f),0,0,(MAX_ALPHA),
	//�X�s�[�h,�A�j���[�V����,��`,���ߓx
	false,false,false,false,false,false,false,false,
	//�e�t���O
	(-RADIUS_YOSHI),(GAMESIZE_WIDE + 50.f + RADIUS_YOSHI),
	//���S���W
};

/**
 * @brief �R���X�g���N�^
 */
C_Chara_Yoshi::C_Chara_Yoshi(C_Vertex *vertex , C_Texture  *texture, LPDIRECT3DDEVICE9  device, C_DSound *sound)
{
	m_pTexture	= new C_Texture();
	m_pVertex		= new C_Vertex();

	m_pTexture	= texture;
	m_pVertex		= vertex;
	m_pDevice		= device;
	m_pSound		= sound;

}

/**
 * @brief �f�X�g���N�^
 */
C_Chara_Yoshi::~C_Chara_Yoshi(void)
{
}

/**
 * @brief ������
 */
void
C_Chara_Yoshi::Init()											
{
	m_pOrbit->pWave->InitWave(WAVE_AMPLIT_YOSHI,WAVE_CYCLE_YOSHI,NULL,WAVE_MODE_GAME);

	//praivate�ϐ�
	s_atk_start_y = 0.f;
	//protected�ϐ�
	m_randspeed	 = 0.f;
	m_delay		 = m_max_animetion = m_chara_num = 0;
	m_flag_turn2 = m_set_hitcheck  = false;
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		//�\����
		m_charadata[i].flag_atk1		= m_charadata[i].flag_atk2		 = false;
		m_charadata[i].flag_death		= m_charadata[i].flag_deathfade	 = false;
		m_charadata[i].flag_effect		= m_charadata[i].flag_effectfont = false;
		m_charadata[i].flag_hit			= m_charadata[i].flag_death_next = false;
		m_charadata[i].draw_cc.x		= (-RADIUS_NOPPO);						//�L�������W�̏�����
		m_charadata[i].draw_cc.y		= (GAME_GROUND - RADIUS_NOPPO);			//�L�������W�̏�����
		m_charadata[i].speed			= 0.f;
		m_charadata[i].animetion		= 0;									//�A�j���[�V����������ő喇��
		m_charadata[i].rect_num			= 0;
		m_charadata[i].alpha			= 0;

		pos_effectfont[i].x	= pos_effectfont[i].y =	rand_acc[i] = rand_move_x[i] = m_deg_spin[i] = draw_deg[i] = 0.f;
		m_count_effect[i]				= 0;
		init[i]							= true;
	}
}

/**
 * @brief �X�V
 */
void
C_Chara_Yoshi::Control(int key,  POS_CC<float> boss_cc, int sound_startnum, int rect_startnum, bool boss_death)
{
	m_randspeed = 0.f;

	//���[�̃`�F�b�N:�U���J�n
	if( (key == KEY_GROUND_1) || (key == KEY_SKY_1) ){
		if(m_flag_turn2){
			m_charadata[m_chara_num]	= init_charadata_yoshi;
			m_count_effect[m_chara_num] = 0;
			init[m_chara_num] = true;
		}
		m_charadata[m_chara_num]		= SetAtk_Flag(key,m_charadata[m_chara_num]);
		m_charadata[m_chara_num].speed  = SetSpeed(key);

		switch(key){
		case KEY_GROUND_1:
			rand_deg[m_chara_num]	 = (float)(rand() % DEG_RAND_YOSHI + DEG_RAND_YOSHI_MIN);
			m_charadata[m_chara_num].draw_cc = SetAtk_Pos(RADIUS_YOSHI,G_ATK_1_START_Y);
			m_deg_spin[m_chara_num]  = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);

			break;
		case KEY_SKY_1:
			s_atk_start_y			 = (float)(rand() % RAND_Y_YOSHI + RAND_Y_MIN_YOSHI);
			rand_acc[m_chara_num]	 = (float)(rand() % PARA_RAND_ACC_YOSHI		+ PARA_RAND_ACC_YOSHI_MIN);	
			rand_move_x[m_chara_num] = (float)(rand() % PARA_RAND_MOVE_X_YOSHI  + PARA_RAND_MOVE_X_YOSHI_MIN);	
			m_deg_spin[m_chara_num]  = (float)(rand() % SPIN_RAND + SPIN_RAND_MIN);
			
			m_charadata[m_chara_num].draw_cc = SetAtk_Pos(RADIUS_YOSHI,s_atk_start_y);
			break;
		}
		if(m_chara_num >= (MAX_VALLUE_PLAYER-1) ){ m_chara_num = 0; m_flag_turn2 = true; }	//�ő吔�𒴂�����1�̖ڂ�			
		else m_chara_num++;																//2�̖ځA3�̖ځ`
	}


	//�L�����̓���(������100�̕�)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		//�����蔻��
		if(!m_charadata[i].flag_death){
			if(!boss_death){
				if(HitCheck(m_charadata[i].draw_cc,boss_cc,ID_YOSHI)){
					m_charadata[i].flag_hit		= true;
					m_charadata[i].flag_death	= true;
					SetFlagHit(true);
					m_chara_y = m_charadata[i].draw_cc.y;

					if(m_charadata[i].flag_atk1){
						if(m_pSound->SoundPlayCheck(S_YOSHI_HIP)) m_pSound->SoundStop(true,S_YOSHI_HIP);
						m_pSound->SoundPlay(false,S_YOSHI_HIP);
					}
					if(m_charadata[i].flag_atk2){
						if(m_pSound->SoundPlayCheck(S_YOSHI_HUSEN)) m_pSound->SoundStop(true,S_YOSHI_HUSEN);
						m_pSound->SoundPlay(false,S_YOSHI_HUSEN);
					}
				}
			}

			if(m_charadata[i].flag_atk1){
				if(m_charadata[i].draw_cc.x - RADIUS_YOSHI < GAMESIZE_WIDE){
					m_charadata[i].draw_cc	 = CharaAttack_1(i);
					m_charadata[i].animetion = SetAnimetion(ANIME_G_ATK4_YOSHI,m_charadata[i].animetion,NULL,i);
				}
			}
			else if(m_charadata[i].flag_atk2){
				if(m_charadata[i].draw_cc.x - RADIUS_YOSHI < GAMESIZE_WIDE){
					m_pOrbit->pWave->SetSpeed(m_charadata[i].speed);
					m_charadata[i].draw_cc	 = CharaAttack_2(i);
					m_charadata[i].animetion = SetAnimetion(NULL,m_charadata[i].animetion,ANIME_S_ATK1_YOSHI,i);
				}
			}
		}
		else DeathControl(i,sound_startnum,rect_startnum);

		//����������̏���
		if(m_charadata[i].flag_hit){
			//���S���W����ʊO�Ȃ玀�S
			if( (m_charadata[i].draw_cc.x < -RADIUS_YOSHI) || (m_charadata[i].draw_cc.x > GAMESIZE_WIDE + RADIUS_YOSHI) &&
				(m_charadata[i].draw_cc.y < -RADIUS_YOSHI) || (m_charadata[i].draw_cc.y > GAMESIZE_HEGHT + RADIUS_YOSHI) ){
					m_charadata[i].flag_death = true;
			}
			
			if(!m_charadata[i].flag_effectfont){
				if(m_count_effect[i]++ < FONT_SET){
					pos_effectfont[i] = SetE_Font(m_charadata[i].draw_cc,RADIUS_NIKU,POS_HITFONT_X);
					m_charadata[i].flag_effectfont	= true;
				}	
			}
			else{
				if(m_count_effect[i]++ < FONT_DELETE){
					pos_effectfont[i] = EffectShake(SHAKE_X,SHAKE_Y,pos_effectfont[i]);
				}
				else{ m_charadata[i].flag_effectfont = false; m_count_effect[i] = 0;}
			}
		}
	}
}

/**
 * @brief �A�j���ݒ�
 */
int
C_Chara_Yoshi::SetAnimetion(int max_animetion, int anime_count ,int rect_num ,int m_chara_num)
{
	static int delay = 0;

	if(delay++ > 15){
		if(max_animetion == 0) anime_count = 0;
		else{
			if(anime_count < max_animetion) anime_count++;
			else anime_count = 0;
		}
		delay = 0;
	}

	m_charadata[m_chara_num].rect_num	= rect_num;

	return anime_count;
}

/**
 * @brief �t�H���g�̕`�揈��
 */
void
C_Chara_Yoshi::DrawEffectFont(int t_num, int rect_startnum,LPDIRECT3DDEVICE9 device_data)
{
	int rect_change = 0;

	//�t�H���g�G�t�F�N�g�̕`��(������100�̕�)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		if(m_charadata[i].flag_hit){
			if(m_count_effect[i]++ < FONT_DELETE){
				if(m_charadata[i].flag_atk1)		rect_change = 0; 
				else if(m_charadata[i].flag_atk2)	rect_change = 1;
				m_pVertex->DrawF(pos_effectfont[i].x,pos_effectfont[i].y,rect_startnum + rect_change);
			}
		}
	}
}

/**
 * @brief �`�揈��
 */
void
C_Chara_Yoshi::Draw(int t_num, int rect_startnum, LPDIRECT3DDEVICE9 device_data)
{
	//�L�����̕`��(������100�̕�)
	for(int i = 0;i < MAX_VALLUE_PLAYER;i++){
		if(m_charadata[i].flag_atk1){
			m_pVertex->SetAngle(0.f);
			m_pVertex->DrawF(m_charadata[i].draw_cc.x,m_charadata[i].draw_cc.y, (rect_startnum + m_charadata[i].rect_num + m_charadata[i].animetion) );
		}
		else if(m_charadata[i].flag_atk2){
			if(m_charadata[i].flag_death_next){
				m_pVertex->SetAngle(m_deg_spin[i] += m_deg_spin[i]);
			}
			else m_pVertex->SetAngle(0.f);
			m_pVertex->DrawF(m_charadata[i].draw_cc.x,m_charadata[i].draw_cc.y, (rect_startnum + m_charadata[i].rect_num + m_charadata[i].animetion) );
		}
	}
}

/**
 * @brief �U������
 */
POS_CC<float>
C_Chara_Yoshi::CharaAttack_2(int m_chara_num)														//�L�[���͂ɂ�铮�삻��2
{
	m_charadata[m_chara_num].draw_cc = m_pOrbit->pWave->OrbitSinWave(WAVE_LIMIT_X_YOSHI,m_charadata[m_chara_num].draw_cc,m_chara_num);

	return m_charadata[m_chara_num].draw_cc;
}

/**
 * @brief ���S����
 */
void
C_Chara_Yoshi::DeathControl(int m_chara_num, int sound_num, int rect_startnum)						//���S����
{

	if(init[m_chara_num]){
		if(m_charadata[m_chara_num].animetion != 0) m_charadata[m_chara_num].animetion = 0;
		init[m_chara_num] = false;
	}
	if(m_charadata[m_chara_num].flag_atk1){
		if(!m_charadata[m_chara_num].flag_death_next){
			m_charadata[m_chara_num].animetion = SetAnimetion((ANIME_MOTION3_YOSHI - ANIME_G_ATK4_YOSHI),m_charadata[m_chara_num].animetion,ANIME_MOTION1_YOSHI,m_chara_num);
			if(m_charadata[m_chara_num].animetion == 3){
				m_charadata[m_chara_num].flag_death_next = true;
			}
		}
		if(m_charadata[m_chara_num].flag_death_next){
			m_charadata[m_chara_num].animetion = 0;																//�`����Œ�
			m_charadata[m_chara_num].rect_num  = ANIME_DEATH_YOSHI;
	
			m_charadata[m_chara_num].draw_cc	 = m_pOrbit->pRebound->OrbitRebound(rand_deg[m_chara_num],m_charadata[m_chara_num].speed,m_charadata[m_chara_num].draw_cc);
		}
	}
	else if(m_charadata[m_chara_num].flag_atk2){
		if(!m_charadata[m_chara_num].flag_death_next){
			m_charadata[m_chara_num].animetion = SetAnimetion((ANIME_S_ATK4_YOSHI - ANIME_S_ATK1_YOSHI),m_charadata[m_chara_num].animetion,ANIME_S_ATK2_YOSHI,m_chara_num);
			if(m_charadata[m_chara_num].animetion == 3){
				m_charadata[m_chara_num].flag_death_next = true;
			}
		}
		if(m_charadata[m_chara_num].flag_death_next){
			m_charadata[m_chara_num].animetion = 0;																//�`����Œ�
			m_charadata[m_chara_num].rect_num  = ANIME_DEATH_YOSHI;

			m_charadata[m_chara_num].draw_cc	 = m_pOrbit->pParadora->OrbitParabola(rand_acc[m_chara_num],rand_move_x[m_chara_num],PARA_LIMIT_Y_YOSHI,m_charadata[m_chara_num].draw_cc,m_chara_num);
		}
	}

	if( (m_charadata[m_chara_num].draw_cc.y < -RADIUS_YOSHI) || (m_charadata[m_chara_num].draw_cc.y > GAMESIZE_HEGHT + RADIUS_YOSHI) ){
		m_charadata[m_chara_num].flag_atk1  = m_charadata[m_chara_num].flag_atk2  = false;
		m_charadata[m_chara_num].flag_death = m_charadata[m_chara_num].flag_hit	  = false;
		m_charadata[m_chara_num].flag_death_next = false;
	}
}