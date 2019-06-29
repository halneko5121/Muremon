//---------------------------------------------
//
//      �Q�[���{��
//      �쐬�J�n��:	3��17��
//			�X�V��:	3��18��
//			�쐬��:	����
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

	void DrawNum();		//�A�Ő�
	void DrawNumS();	//�X�R�A
	void DrawNumT();	//�^�C��
	void DrawGageHp();
	void DrawGageMission();

	void ControlMissionOugi();		// �A�N�V�f���g���`�̃R���g���[��
	void DrawMissionOugi();			// �A�N�V�f���g���`��`��
	void ControlMissionNegative();	// �~�b�V�������s���̏���
	void NegativeSelect();			// �ǂ̏����ɂ��邩�𔻒f
	void DrawMissionNegative();		// �~�b�V�������s���̏���

	void ReCover();					// �~�b�V�������s�ŉ����������̂����ɖ߂�
	void FadeControl();				// �t�F�[�h�R���g���[��		
	void FadeIn();					// �t�F�[�h�C��
	void FadeOut();					// �t�F�[�h�A�E�g
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

	int time;	//���Ԃ��͂���

	bool flag_pose;	//�|�[�Y�����Ă��邩���Ă��Ȃ���

	int score;

	int alpha;	//�A���t�@�l

	int alpha_count;	//�A���t�@�̃f�B���C

	int start_alpha;	//���`�ނ����`�Ƃ̃A���t�@����

	int game_state;		//�Q�[���̏��(�X�^�[�g�E��������Q�[��)

	int flag_fade;		//�t�F�[�h�C���A�E�g�Ȃǂ̒i�K��m�点��

	int flag_fade_start;	//���`�ނ����`�Ƃ̃t�F�[�h�C���E�t�F�[�h�A�E�g��m�点��̂Ɏg�p

	bool flag_fade_in;		//�t�F�[�h�C�����I�������Ԃ���m�点��

	int key_state;			//�L�[�̏��

	int mission_state_keep;	//�~�b�V�����̏�Ԃ��L�[�v

	int cnt_key_nikuman;	//�ɂ��܂�̉����ꂽ�L�[�̐����J�E���g

	int cnt_key_yoshitaro;	//�g���낤�̉����ꂽ�L�[�̐����J�E���g

	int cnt_key_noppo;		//�̂��ۂ̉����ꂽ�L�[�̐����J�E���g

	int flag_init;			//�������������ǂ���

	bool flag_red;			//�F������

	int mission_gage;		//�K�E�Q�[�W

	bool hit_niku;

	bool hit_yoshi;

	bool hit_noppo;

	bool hit_effect_flag;

	//�q�b�g�G�t�F�N�g

	int hit_effect_alpha;

	int hit_effect_time;

	float chara_atk_y;

	bool flag_sound;

	//���`���Ŏg�p
	int alpha_font;
	int time_cnt;

	int speed_x;

	POSI wave_posi;

	//NEGATIVE�Ŏg�p
	int negative_state;
	int negative_damege;
	
	bool scene_change;	//�V�[�����ς�鎞��m�点��
};
