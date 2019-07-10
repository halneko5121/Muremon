#pragma once
/******************************************************************
 *	@file	ActorMgr.h
 *	@brief	�A�N�^�[�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class ActorBase;

enum ActorId
{
	cActorId_Null,			// �Ȃ�
	cActorId_Noppo,			// �m�b�|
	cActorId_Nikuman,		// �ɂ��܂�
	cActorId_Yoshi,			// �悵���낤
	cActorId_Count,			// �悵���낤
};

class ActorMgr
{
public:
	ActorMgr();
	~ActorMgr();

	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static ActorMgr*	getInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void			create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void			destroy();

	/**
	 * @brief	�A�N�^�[�̐���
	 */
	ActorBase*			createActor(ActorId id);

private:
	typedef std::vector<ActorBase*>	ActorList;

private:
	static ActorMgr*	mInstance;		// �C���X�^���X
	ActorList			mActorList;		// �A�N�^�[��ۊǂ��Ă������X�g
	int					mUniqId;		// ���j�[�NID

};

static ActorMgr* GetActorMgr() { return ActorMgr::getInstance(); }