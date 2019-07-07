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
	Texture	*texture;
	Vertex	*vertex;

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
	int		getCountKeyNikuman()		{ return cnt_key_nikuman; };
	int		getCountKeyYoshitaro()	{ return cnt_key_yoshitaro; };
	int		getCountKeyNoppo()		{ return cnt_key_noppo; };


	void	init(int cnt_nikuman,int cnt_yoshitaro,int cnt_noppo);

	int		update();

	void	draw();

	void	fadeIn();

	void	fadeOut();

	void	drawTime();		//���Ԃ�\��

	void	drawCombo();

	void	missionSelect();	//�݂����������߂��菉����������

	void	updateMission();
	void	updateMissionD();

	void	updateMission1();	//�w10�b�ȓ���100��A�ł���I�I�x
	void	updateMission2();	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
	void	updateMission3();	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
	void	updateMission4();	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
	void	updateMission5();	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
	void	updateMission6();	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
	void	updateMission7();	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
	void	updateMission8();	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
	void	updateMission9();	//�w�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�x
	void	updateMission10();	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	void	updateMission11();	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	void	updateMission12();	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
	void	updateMission13();	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
	void	updateMission14();	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x

	void	updateMission1D();	//�w10�b�ȓ���100��A�ł���I�I�x
	void	updateMission2D();	//�w10�b�Ԃł��傤��50��A�ł���I�I�x
	void	updateMission3D();	//�w10�b�Ԃł��傤��100��A�ł���I�I�x
	void	updateMission4D();	//�w�uNIKUMANTOTUGEKI�v�Ɠ��͂���I�I�x
	void	updateMission5D();	//�w�uNIKUMANINSEKIRAKKAJUTU�v�Ɠ��͂���I�I�x
	void	updateMission6D();	//�w�uYOSITAROHIPATACK�v�Ɠ��͂���I�I�x
	void	updateMission7D();	//�w�uYOSITAROHUSENSHOOT�v�Ɠ��͂���I�I�x
	void	updateMission8D();	//�w�uNOPPOKOKEPPETI�v�Ɠ��͂���I�I�x
	void	updateMission9D();	//�w�uNOPPOBOK�tSIRIKOPUTA�v�Ɠ��͂���I�I�x
	void	updateMission10D();	//�w10�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	void	updateMission11D();	//�w5�b�����đO��1�b�ȓ��Łu�y�L�[�v�������I�x
	void	updateMission12D();	//�w10�b�ȓ��Ɂu�ɂ��܂�v�̘A�Ő�����ԍ�������I�x
	void	updateMission13D();	//�w10�b�ȓ��Ɂu�悵���낤�v�̘A�Ő�����ԍ�������I�x
	void	updateMission14D();	//�w10�b�ȓ��Ɂu�̂��ہv�̘A�Ő�����ԍ�������I�x

	Mission(Texture* m_texture,Vertex* m_vertex,LPDIRECT3DDEVICE9 apDev);
	~Mission(void);
};
