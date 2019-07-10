#pragma once
/******************************************************************
 *	@file	ActorMgr.h
 *	@brief	�A�N�^�[�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

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

private:
	static ActorMgr*	mInstance;		// �C���X�^���X
};

static ActorMgr* GetDirectFont() { return ActorMgr::getInstance(); }