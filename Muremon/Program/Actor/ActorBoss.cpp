#include "ActorBoss.h"

#include "Program/Util/UtilSound.h"
#include "Program/Util/UtilGraphics.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

//�{�X�̃R���g���[���^�C�v
enum BOSS_CONTROLTYPE
{
	REFRESH_TYPE,	//�������胂�[�h
	NORMAL_TYPE,	//�m�[�}�����[�h
};

// �{�X�֘A
#define BOSS_INITIAL_LIFE			(3000)	//�{�X�̏������C�t
#define BOSS_GROW_LIFE				(1000)	//�{�X�����񂾎��������Ă������C�t
#define BOSS_ALPHA_APPEAR			(20)	//�{�X���o���������̃A���t�@���l
#define BOSS_ALPHA_FALL				(5)		//�{�X���ł������̃A���t�@���l
#define BOSS_APPEARANCE_POSITION	(950)	//�{�X�̏o�����S�ʒu
#define BOSS_REFRESH_X_STOP			(550)	//�X�b�L�����[�h�̃{�X�̎~�߂钆�S���W
#define BOSS_STABILITY_Y			(350)	//�{�XY�ʒu�̌Œ�
#define BOSS_DAMAGE_COUNT			(50)	//�{�X���U��������H��������ɒɂ���\��
#define BOSS_DAMAGE_TIME_DRAW		(60)	//�{�X�̒ɂ���\������
#define BOSS_FALL_TIME				(60)
#define BOSS_SPPEAR_TIME			(60)	//�{�X���t�F�[�h�A�E�g���鎞��
#define BOSS_NO_DRAWTIME			(120)	//NO��`�悷�鎞��

#define DAMAGE_RAND					(5)

#define NO_FONT						(25)

#define NO_POSITION_X				(150.f)
#define NO_POSITION_Y				(150.f)

#define BOSS_MOVECOUNT				(3)

#define HIT_EFFECT_X				(100)
#define HIT_FFFECT_Y				(450)
#define MISSION_CLEAR_SCORE			(50000)	//�~�b�V�����N���A���Z�X�R�A
#define BOSS_KO_SCORE				(10000)

ActorBoss::ActorBoss()
{
	vertex = new Vertex();
	texture = new Texture();
	UtilGraphics::loadVertexAndTexture(vertex, texture, "actor");

	//�{�X
	boss_fall_flag=false;

	boss_alpha_count=0;

	boss_movecount=0;
	
	boss_new_flag=false;

	hit_count=0;

	boss_damage_flag = false;

	boss_mode=M_BOSS_MOVE;
	
	boss_alpha=255;
		
	boss_fadeout_time=0;
	
	damage_time=0;
	
	boss_rect_data=R_BOSS_MOVE1;

	lv_count = 0;

	boss_life = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * lv_count); 

	max_boss_life = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * lv_count); 

	boss_move_x=BOSS_APPEARANCE_POSITION;
	boss_move_y=BOSS_STABILITY_Y;
	boss_movecount=0;
	boss_move_flag=true;

	boss_win_flag=false;

	no_font_alpha=0;
	no_draw_time=0;
	no_fade_flag=NF_FADE_IN;

	move_anime = 0;
	
	move_anime_time = 0;

	speed_x = 1;

	damage_x = 0;

	damage_y = 0;

	effect_font = 0;

	effect_font_move = false;
}

ActorBoss::~ActorBoss()
{
}

void ActorBoss::impleInit()
{
	//�{�X
	boss_alpha_count=0;

	boss_movecount=0;
	
	boss_new_flag=false;

	hit_count=0;

	boss_mode=M_BOSS_MOVE;
	
	boss_alpha=255;
		
	boss_fadeout_time=0;
	
	boss_damage_flag = false;

	damage_time=0;
	
	boss_rect_data=R_BOSS_MOVE1;

	boss_move_x=BOSS_APPEARANCE_POSITION;
	
	boss_movecount=0;

	boss_move_flag=true;

	boss_win_flag=false;

	no_font_alpha=0;
	no_draw_time=0;
	no_fade_flag=NF_FADE_IN;

	move_anime = 0;
	
	move_anime_time = 0;

	speed_x = 1;

	damage_x = 0;

	damage_y = 0;

	effect_font = 0;

	effect_font_move = false;

	boss_life = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * lv_count); 

	max_boss_life = BOSS_INITIAL_LIFE + (BOSS_GROW_LIFE * lv_count); 

	boss_new_flag=false;

	boss_fall_flag=false;
}

void ActorBoss::control(int play_mode)
{
	//�{�X�̈ړ��R���g���[��
	if(boss_move_flag)
	{
		boss_movecount++;
		move_anime_time++;
	}

	//�{�X�̈ړ����x����
	if(boss_movecount>=BOSS_MOVECOUNT)
	{
		boss_move_x-=1;
		boss_movecount=0;
		if(play_mode==PLAY_REFRESH)
		{
			if(boss_move_x<=BOSS_REFRESH_X_STOP)
			{
				boss_move_x=BOSS_REFRESH_X_STOP;
				boss_move_flag=false;
			}
		}else{
			if(boss_move_x<=BOSS_WIN_POSITOIN)
			{
				boss_move_x=BOSS_WIN_POSITOIN;
				boss_move_flag=false;
				boss_win_flag=true;
			}
		}
	}
	
	//�{�X�̈ړ��A�j���[�V�����R���g���[��
	if(move_anime_time % 16 ==15)
	{
		move_anime++;
	}

	//�{�X�̈ړ��X�g�b�v�R���g���[��
	//�K��񐔂̃_���[�W�R���g���[��
	if(hit_count==BOSS_DAMAGE_COUNT)
	{
		boss_move_flag = false;
		boss_damage_flag=true;
		hit_count=0;
	}

	//���C�t���O�ɂȂ������̃R���g���[��
	if(boss_life<0)
	{
		boss_life=0;
	}
	if(boss_life==0)
	{
		boss_fall_flag=true;
		boss_move_flag=false;
	}
	
	//�{�X�����񂾌�̏�����
	if(boss_new_flag)
	{
		if(lv_count<7)
		{
			lv_count++;
		}else lv_count = 7;
		impleInit();
	}
	
	if(!boss_fall_flag)
	{
		//�{�X���_���[�W�H��������̏���
		if(boss_damage_flag)
		{
			boss_mode=M_BOSS_DAMEGE;
			damage_x = rand()% DAMAGE_RAND;
			damage_y = rand()% DAMAGE_RAND;
		}
	}

	//�{�X���{�X�����񂾎��̃t�F�[�h�A�E�g�V�[��
	if(boss_fall_flag)
	{
		boss_mode=M_BOSS_FALL;
		boss_fadeout_time++;
		effect_font_move = true;
		if(boss_fadeout_time>BOSS_FALL_TIME)
		{
			if(boss_alpha_count++>1)
			{
				boss_alpha-=BOSS_ALPHA_FALL;
				boss_alpha_count=0;
			}
			if(boss_alpha<0)
			{
				boss_alpha=0;
				boss_alpha_count=0;
			}

			if(boss_alpha==0)
			{
				boss_alpha=0;
				boss_alpha_count=0;
				boss_new_flag=true;
			}
		}

		if(effect_font_move)
		{
			effect_font++;
			if(effect_font>NO_FONT){
			effect_font_move=false;
			effect_font = NO_FONT;
			}
		}

		if (boss_fadeout_time == BOSS_FALL_TIME)
		{
			UtilSound::playOnce(S_DEAD);
		}

		//�uNo�`�v�̃t�F�[�h�C���A�E�g
		switch(no_fade_flag)
		{
			case NF_FADE_IN:
				no_font_alpha+=5;
				if(no_font_alpha>=255)
				{
					no_font_alpha=255;
					no_fade_flag=NF_USUALLY;
				}
				break;
			case NF_USUALLY:
				no_font_alpha=255;
				no_draw_time++;
				if(no_draw_time>=60)
				{
					no_fade_flag=NF_FADE_OUT;
				}
				break;
			case NF_FADE_OUT:
				no_font_alpha-=5;
				if(no_font_alpha<=0)
				{
					no_font_alpha=0;
				}
				break;
		}
	}

	//�{�X�̕`��A���[�h
	switch(boss_mode)
	{
		case M_BOSS_MOVE:
			boss_rect_data=R_BOSS_MOVE1 + move_anime%2;
			if(play_mode==PLAY_REFRESH)
			{
				if(boss_move_x==BOSS_REFRESH_X_STOP)
				{
					boss_move_flag=false;
					boss_mode=M_BOSS_USUALLY;
				}
			}
			break;
		case M_BOSS_USUALLY:
			boss_rect_data=R_BOSS_USUALLY;
			break;
		case M_BOSS_DAMEGE:
			boss_rect_data=R_BOSS_DAMAGE;
			damage_time++;
			if(damage_time==60)
			{
				boss_damage_flag=false;
				damage_x = 0;
				damage_y = 0;
				if(play_mode==PLAY_REFRESH)
				{
					if(boss_move_x==BOSS_REFRESH_X_STOP)
					{
						boss_move_flag=false;
						boss_mode=M_BOSS_USUALLY;
						damage_time=0;
					}else{ 
						boss_mode=M_BOSS_MOVE;
						boss_move_flag=true;
						damage_time=0;
					}
				}else{
					boss_mode=M_BOSS_MOVE;
					boss_move_flag=true;
					damage_time=0;
				}
			}
			break;
		case M_BOSS_FALL:
			boss_rect_data=R_BOSS_FALL;
			break;
	}
}

void ActorBoss::draw()
{
	UtilGraphics::setTexture(vertex, *texture, T_CAHRA_BOSS);
	vertex->setColor(boss_alpha,255,255,255);
	vertex->drawF(boss_move_x + damage_x,boss_move_y + damage_y,boss_rect_data);
}

void ActorBoss::fallDraw()
{
	UtilGraphics::setTexture(vertex, *texture, T_GAME_EFFECT);
	vertex->setColor(no_font_alpha,255,255,255);
	vertex->drawF(boss_move_x - NO_POSITION_X - effect_font,NO_POSITION_Y - effect_font,R_BOSS_EFFECT);
}

