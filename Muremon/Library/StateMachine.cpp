/******************************************************************
 *	@file	StateMachine.cpp
 *	@brief	�X�e�[�g�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "StateMachine.h"

 /**
  * @brief	�R���X�g���N�^
  */
StateMachine::StateMachine()
	: mMaxStateNum(0)
	, mFirstStateIndex(-1)
	, mCurrentStateIndex(-1)
	, mPrevStateIndex(-1)
	, mCurrentStateCounter(0)
	, mPrevStateCounter(0)
	, mIsChangeStateInExe(false)
{
	for (int i = 0; i < cMaxRegistState; i++)
	{
		mDelegate[i] = nullptr;
	}
}

/**
 * @brief	�f�X�g���N�^
 */
StateMachine::~StateMachine()
{
	for (int i = 0; i < mMaxStateNum; i++)
	{
		SAFE_DELETE(mDelegate[i]);
	}
}

/**
 * @brief	������
 * @param	max_state_count		�ő�X�e�[�g��
 * @param	first_state_index	�����X�e�[�g�ԍ�
 */
void
StateMachine::initialize(int max_state_num, int first_state_index)
{
	if ((cMaxRegistState <= max_state_num))
	{
		OutputDebugString("�ő�o�^���𒴂��܂���");
		assert(false);
	}

	mFirstStateIndex = first_state_index;
	mMaxStateNum = max_state_num;
	mCurrentStateIndex = mFirstStateIndex;
	mPrevStateIndex = mFirstStateIndex;
}

/**
 * @brief	�X�e�[�g�̃��Z�b�g
 */
void
StateMachine::resetState()
{
	mCurrentStateIndex = -1;
	mCurrentStateCounter = 0;
	mPrevStateIndex = -1;
	mPrevStateCounter = 0;
}

/**
 * @brief	�X�e�[�g�֐��̎��s
 */
void
StateMachine::executeState()
{
	if ((mCurrentStateIndex == -1))
	{
		OutputDebugString("Initialize() ���Ă�ŉ�����");
		assert(false);
	}

	mIsChangeStateInExe = false;

	exeState_();

	// �X�e�[�g���s���ɃX�e�[�g�ύX����Ă��Ȃ�������t���[�����Z
	if (!mIsChangeStateInExe)
	{
		mCurrentStateCounter++;
	}
}

/**
 * @brief	�X�e�[�g�̏I��
 */
void
StateMachine::exitState()
{
	exitState_(-1);
	changeState_(-1);
}

/**
 * @brief	�ŏ��̃X�e�[�g�ɕύX
 */
void
StateMachine::changeFirstState()
{
	changeState_(mFirstStateIndex);
	enterState_();
}

/**
 * @brief	�w��X�e�[�g�ɕύX
 * @param	state_index	�X�e�[�g�ԍ�
 */
void
StateMachine::changeState(int next_state_index)
{
	if ((next_state_index == -1))
	{
		OutputDebugString("Initialize() ���Ă�ŉ�����");
		assert(false);
	}

	exitState_(next_state_index);
	changeState_(next_state_index);
	enterState_();
}

/**
 * @brief	�w��X�e�[�g�ɕύX
 * @param	next_state_index	�X�e�[�g�ԍ�
 * @note	�����Ȃ牽�����Ȃ�
 */
bool
StateMachine::changeStateIfDiff(int next_state_index)
{
	if (mCurrentStateIndex == next_state_index)
	{
		return false;
	}

	changeState(next_state_index);
	return true;
}

/**
 * @brief	�X�e�[�g�ԍ��̎擾
 */
int
StateMachine::getStateIndex() const
{
	return mCurrentStateIndex;
}

/**
 * @brief	�O��̃X�e�[�g�ԍ��̎擾
 */
int
StateMachine::getPrevStateIndex() const
{
	return mPrevStateIndex;
}

/**
 * @brief	�o�^�X�e�[�g�ő吔�̎擾
 */
int
StateMachine::getMaxStateNum() const
{
	return mMaxStateNum;
}

/**
 * @brief	�X�e�[�g���s�t���[�����̎擾
 */
int
StateMachine::getStateCount()
{
	return mCurrentStateCounter;
}

/**
 * @brief	�X�e�[�g���؂�ւ���Ă���ŏ��̃t���[����
 */
bool
StateMachine::isStateCountFirst() const
{
	return (mCurrentStateCounter == 0);
}

/**
 * @brief	�w�肵���X�e�[�g�Ɠ����X�e�[�g��
 */
bool
StateMachine::isEqual(int state_index) const
{
	return (state_index == getStateIndex());
}

/**
 * @brief	�������H
 */
bool
StateMachine::isInvalid() const
{
	return (getStateIndex() == -1);
}

/**
 * @brief	�L�����H
 */
bool
StateMachine::isValid() const
{
	return (!isInvalid());
}

/**
 * @brief	�X�e�[�g�̕ύX
 */
void
StateMachine::changeState_(int state_index)
{
	mPrevStateIndex = mCurrentStateIndex;
	mPrevStateCounter = mCurrentStateCounter;
	mCurrentStateIndex = state_index;
	mCurrentStateCounter = 0;
	mIsChangeStateInExe = true;
}

/**
 * @brief	�X�e�[�g�̊J�n
 */
void
StateMachine::enterState_()
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->enter();
	}
}

/**
 * @brief	�X�e�[�g�̎��s
 */
void
StateMachine::exeState_()
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->exe();
	}
}

/**
 * @brief	�X�e�[�g�̏I��
 */
void
StateMachine::exitState_(int next_state_index)
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->exit(next_state_index);
	}
}