#pragma once

#include "Library/StateMachine.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"
#include "Program/DefineGame.h"

class ActorBoss;

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

class MissionMgr
{
public:
	MissionMgr(Texture* texture, Vertex* vertex, ActorBoss* boss);
	~MissionMgr();

	int		getCountKeyNikuman() { return mKeyCountNikuman; };
	int		getCountKeyYoshitaro() { return mKeyCountYoshitaro; };
	int		getCountKeyNoppo() { return mKeyCountNoppo; };

	void	init(int cnt_nikuman, int cnt_yoshitaro, int cnt_noppo);
	void	update();
	void	draw();

	int		getMissionState() const;
	int		getBadStatusAtkLv() const;
	void	resetBadStatusAtkLv();

private:
	void	drawTime();		//���Ԃ�\��
	void	drawCombo();

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

private:
	// �X�e�[�g�֐�
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(StartShake);
	DECLAR_STATE_FUNC2(StartFadeOut);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(Success);
	DECLAR_STATE_FUNC2(Failure);
	DECLAR_STATE_FUNC2(Ougi);
	DECLAR_STATE_FUNC2(BadStatus);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine<MissionMgr>	mState;	// �X�e�[�g
	Texture*				mTexture;
	Vertex*					mVertex;
	ActorBoss*				mActorBoss;

	Vector2f				mMissionStartPos;	//�݂������J�n�̈ʒu

	int						mAlpha;			//
	int						mAlphaPushZ;	//

	int						mFlagZ;			//
	int						mFlagDraw;		//

	int						mMoveCount;		//
	int						mCurrentMissionNo;		// �ǂ̃~�b�V�������I�����ꂽ�����L��
	int						mMissionState;			// �~�b�V���������ǂ̏󋵂�

	int						mAlphaFont;
	Vector2f				mWavePos;

	int						mNegativeAlpha;
	int						mNegativeState;
	int						mNegativeAtkLv;

	int						mTime;					// ����
	int						mFlagTimeCount;			// �^�C���J�E���g�̃t���O
	int						mSuccessTypingCount;	// �^�C�s���O���������Ă��邩����
	int						mFlagMissionState;		// �~�b�V���������E���s

	int						mKeyCount;				// �L�[�̘A�Ő���ۑ�����ϐ�

	int						mKeyCountNikuman;		// �ɂ��܂�̉����ꂽ�L�[�̐����J�E���g
	int						mKeyCountYoshitaro;		// �g���낤�̉����ꂽ�L�[�̐����J�E���g
	int						mKeyCountNoppo;			// �̂��ۂ̉����ꂽ�L�[�̐����J�E���g
};
