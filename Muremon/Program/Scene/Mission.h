#pragma once

#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/Util/Control.h"
#include "Program/DefineGame.h"

#define TEN_SECOND	(600)

#define M_TIMENUM_X	(375.f)
#define M_TIMENUM_Y	(125.f)

#define M_COMBO_X	(500.f)
#define M_COMBO_Y	(245.f)

#define MISSION4_FONT_NUM	(16)
#define MISSION5_FONT_NUM	(23)
#define MISSION6_FONT_NUM	(17)
#define MISSION7_FONT_NUM	(19)
#define MISSION8_FONT_NUM	(15)
#define MISSION9_FONT_NUM	(20)

#define MISSION_1PAR	(10)
#define MISSION_2PAR	(20)
#define MISSION_3PAR	(25)
#define MISSION_4PAR	(35)
#define MISSION_5PAR	(40)
#define MISSION_6PAR	(50)
#define MISSION_7PAR	(55)
#define MISSION_8PAR	(65)
#define MISSION_9PAR	(70)
#define MISSION_10PAR	(75)
#define MISSION_11PAR	(85)
#define MISSION_12PAR	(90)
#define MISSION_13PAR	(95)
#define MISSION_14PAR	(100)

#define MISSION_ALPHA_INCREASE	(5)
#define MISSION_ALPHA_MAX	(255)

#define MISSION_HASSEI_X	(400.f)
#define MISSION_HASSEI_Y	(50.f)

#define MISSION_OSIRASE_X	(400.f)
#define MISSION_OSIRASE_Y	(300.f)

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

enum MISSION_NUMBER
{
	MISSION_1,	//�w10�b�ȓ���100��A�ł���I�I�x
	MISSION_2,	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
	MISSION_3,	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
	MISSION_4,	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
	MISSION_5,	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
	MISSION_6,	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
	MISSION_7,	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
	MISSION_8,	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
	MISSION_9,	//�w�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�x
	MISSION_10,	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	MISSION_11,	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	MISSION_12,	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
	MISSION_13,	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
	MISSION_14,	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x
};

class C_Mission
{
private:
	C_Texture	*texture;
	C_Vertex	*vertex;
	C_Control	*key;

	LPDIRECT3DDEVICE9 pDevice;

	D3DXVECTOR2 mission_start;	//�݂������J�n�̈ʒu

	int alpha_count;	//

	int alpha;			//

	int alpha_push_z;	//

	int flag_z;			//

	int flag_draw;		//

	bool flag_sound;	//

	bool flag_sound2;	//

	int cnt_move;		//

	int mission_no;		//�ǂ̃~�b�V�������I�����ꂽ�����L��

	int mission_state;	//�~�b�V���������ǂ̏󋵂�

	int time;	//����

	int flag_time_cnt;	//�^�C���J�E���g�̃t���O

	int type_key;		//�^�C�s���O���������Ă��邩����

	int flag_mission_state;	//�~�b�V���������E���s

	bool flag_init;		//���������������ĂȂ���

	int key_cnt;		//�L�[�̘A�Ő���ۑ�����ϐ�

	int key_state;		//�L�[�̏�Ԃ�ۑ�����ϐ�

	int cnt_key_nikuman;	//�ɂ��܂�̉����ꂽ�L�[�̐����J�E���g

	int cnt_key_yoshitaro;	//�g���낤�̉����ꂽ�L�[�̐����J�E���g

	int cnt_key_noppo;		//�̂��ۂ̉����ꂽ�L�[�̐����J�E���g
public:
	int GetCntKeyNikuman()		{ return cnt_key_nikuman; };
	int GetCntKeyYoshitaro()	{ return cnt_key_yoshitaro; };
	int GetCntKeyNoppo()		{ return cnt_key_noppo; };


	void Init(int cnt_nikuman,int cnt_yoshitaro,int cnt_noppo);

	int Control();

	void Draw();

	void FadeIn();

	void FadeOut();

	void DrawNumT();		//���Ԃ�\��

	void DrawCombo();

	void MissionSelect();	//�݂����������߂��菉����������

	void MissionControl();
	void MissionControlD();

	void Mission1();	//�w10�b�ȓ���100��A�ł���I�I�x
	void Mission2();	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
	void Mission3();	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
	void Mission4();	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
	void Mission5();	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
	void Mission6();	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
	void Mission7();	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
	void Mission8();	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
	void Mission9();	//�w�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�x
	void Mission10();	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	void Mission11();	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	void Mission12();	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
	void Mission13();	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
	void Mission14();	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x

	void Mission1D();	//�w10�b�ȓ���100��A�ł���I�I�x
	void Mission2D();	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
	void Mission3D();	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
	void Mission4D();	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
	void Mission5D();	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
	void Mission6D();	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
	void Mission7D();	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
	void Mission8D();	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
	void Mission9D();	//�w�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�x
	void Mission10D();	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	void Mission11D();	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	void Mission12D();	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
	void Mission13D();	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
	void Mission14D();	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x

	C_Mission(C_Texture* m_texture,C_Vertex* m_vertex,LPDIRECT3DDEVICE9 apDev);
	~C_Mission(void);
};
