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
	int alpha;	//�A���t�@�l

	int alpha_count;	//�A���t�@�̃f�B���C

	int start_alpha;	//���`�ނ����`�Ƃ̃A���t�@����

	int game_state;		//�Q�[���̏��(�X�^�[�g�E��������Q�[��)

	int flag_fade;		//�t�F�[�h�C���A�E�g�Ȃǂ̒i�K��m�点��

	int flag_fade_start;	//���`�ނ����`�Ƃ̃t�F�[�h�C���E�t�F�[�h�A�E�g��m�点��̂Ɏg�p

	bool flag_fade_in;		//�t�F�[�h�C�����I�������Ԃ���m�点��

	int key_state;			//�L�[�̏��

	int cnt_key_nikuman;	//�ɂ��܂�̉����ꂽ�L�[�̐����J�E���g

	int cnt_key_yoshitaro;	//�g���낤�̉����ꂽ�L�[�̐����J�E���g

	int cnt_key_noppo;		//�̂��ۂ̉����ꂽ�L�[�̐����J�E���g

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

	bool scene_change;	//�V�[�����ς�鎞��m�点��
public:
	void InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, C_DSound *apSound,int score);

	bool RunScene();
	void ControlScene();
	void DrawScene();
	int EndScene();

	void DrawNum();

	void DrawGageHp();

	void FadeControl();		//�t�F�[�h�R���g���[��		

	void FadeIn();			//�t�F�[�h�C��

	void FadeOut();			//�t�F�[�h�A�E�g

	void BossDraw();
	
	void BossControl();

	void Calculate(int getchara);	//�v�Z�����i���_���[�W�A�K�E�Q�[�W�����j

	void ScoreDamageDraw();	//���_���[�W�X�R�A

	void HitFlagInit();

	void HitEffectDraw();

	C_GameRefresh(void);
	~C_GameRefresh(void);
};
