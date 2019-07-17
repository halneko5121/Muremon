#pragma once
/******************************************************************
 *	@file	ActorMgr.h
 *	@brief	�A�N�^�[�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "ActorBase.h"

enum ActorId
{
	cActorId_Null = -1,		// �Ȃ�
	cActorId_Noppo,			// �m�b�|
	cActorId_Nikuman,		// �ɂ��܂�
	cActorId_Yoshi,			// �悵���낤
	cActorId_Boss,			// �{�X
	cActorId_Count,
};

class ActorMgr
{
public:
	typedef std::vector<ActorBase*>::iterator ActorIterator;
	typedef std::vector<ActorBase*>::const_iterator ActorConstIterator;

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
	ActorBase*			createActor(ActorId id, Texture* texture, Vertex* vertex);

	/**
	 * @brief	�A�N�^�[�̏�����
	 */
	void				init();

	/**
	 * @brief	�A�N�^�[�̍X�V
	 */
	void				update(Vector2f boss_cc);

	/**
	 * @brief	�A�N�^�[�̕`��
	 */
	void				draw() const;

	/**
	 * @brief	�C�e���[�^�[�̎擾
	 */
	ActorIterator		begin();
	ActorConstIterator	cbegin();

	/**
	 * @brief	�C�e���[�^�[�̎擾
	 */
	ActorIterator		end();
	ActorConstIterator	cend();

private:
	typedef std::vector<ActorBase*>	ActorList;

private:
	static ActorMgr*	mInstance;		// �C���X�^���X
	ActorList			mActorList;		// �A�N�^�[��ۊǂ��Ă������X�g
	int					mUniqId;		// ���j�[�NID

};

static ActorMgr* GetActorMgr() { return ActorMgr::getInstance(); }