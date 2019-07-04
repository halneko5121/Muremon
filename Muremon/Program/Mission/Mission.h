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
	C_Texture	*texture;
	C_Vertex	*vertex;

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

	int success_type_count;	//�^�C�s���O���������Ă��邩����

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

	Mission(C_Texture* m_texture,C_Vertex* m_vertex,LPDIRECT3DDEVICE9 apDev);
	~Mission(void);
};