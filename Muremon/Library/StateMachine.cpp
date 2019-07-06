/******************************************************************
 *	@file	StateMachine.cpp
 *	@brief	�X�e�[�g�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "StateMachine.h"

#include <windows.h>
#include <assert.h>

 /**
  * @brief	�R���X�g���N�^
  */
template<class OWNER>
StateMachine<OWNER>::StateMachine()
	: mMaxStateNum(0)
	, mFirstStateIndex(-1)
	, mCurrentStateIndex(-1)
	, mPrevStateIndex(-1)
	, mCurrentStateCounter(0)
	, mPrevStateCounter(0)
	, mIsChangeStateInExe(false)
	, mDelegateList(nullptr)
{
}

/**
 * @brief	�f�X�g���N�^
 */
template <typename OWNER>
StateMachine<OWNER>::~StateMachine()
{
}

/**
 * @brief	������
 * @param	max_state_num		�ő�X�e�[�g��
 * @param	first_state_index	�����X�e�[�g�ԍ�
 */
template <typename OWNER>
void
StateMachine<OWNER>::initialize(int max_state_num, int first_state_index)
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
 * @brief	�X�e�[�g�֐��̓o�^
 * @param	owner		�o�^����I�[�i�[
 * @param	EnterFunc	�o�^����J�n�֐�
 * @param	ExeFunc		�o�^������s�֐�
 * @param	ExitFunc	�o�^����I���֐�
 */
template <typename OWNER>
void
StateMachine<OWNER>::registState(OWNER* owner, void (OWNER::*enterFunc)(), void (OWNER::*exeFunc)(), void (OWNER::*exitFunc)(int), int state_index)
{
	// �͈͊O
	if ((state_index < 0 )||
		(max_state_num <= state_index))
	{
		OutputDebugString("�w��X�e�[�g�ԍ��͔͈͊O�ł�");
		assert(false);
	}

	typedef Delegate<OWNER> DelegateImple;
	mDelegateList[state_index] = new DelegateImple(owner, enterFunc, exeFunc, exitFunc);
}

/**
 * @brief	�X�e�[�g�֐��̎��s
 */
template <typename OWNER>
void
StateMachine<OWNER>::executeState()
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
 * @brief	�ŏ��̃X�e�[�g�ɕύX
 */
template <typename OWNER>
void
StateMachine<OWNER>::changeFirstState()
{
	changeState_(mFirstStateIndex);
	enterState_();
}


/**
 * @brief	�w��X�e�[�g�ɕύX
 * @param	next_state_index	�X�e�[�g�ԍ�
 */
template <typename OWNER>
void
StateMachine<OWNER>::changeState(int next_state_index)
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
template <typename OWNER>
bool
StateMachine<OWNER>::changeStateIfDiff(int next_state_index)
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
template <typename OWNER>
int
StateMachine<OWNER>::getStateIndex() const
{
	return mCurrentStateIndex;
}

/**
 * @brief	�O��̃X�e�[�g�ԍ��̎擾
 */
template <typename OWNER>
int
StateMachine<OWNER>::getPrevStateIndex() const
{
	return mPrevStateIndex;
}

/**
 * @brief	�o�^�X�e�[�g�ő吔�̎擾
 */
template <typename OWNER>
int
StateMachine<OWNER>::getMaxStateNum() const
{

}

/**
 * @brief	�X�e�[�g���s�t���[�����̎擾
 */
template <typename OWNER>
int
StateMachine<OWNER>::getStateCount()
{
	return mCurrentStateCounter;
}

/**
 * @brief	�X�e�[�g���؂�ւ���Ă���ŏ��̃t���[����
 */
template <typename OWNER>
bool
StateMachine<OWNER>::isStateCountFirst()
{
	return (getStateCount() == 0);
}

/**
 * @brief	�w�肵���X�e�[�g�Ɠ����X�e�[�g��
 */
template <typename OWNER>
bool
StateMachine<OWNER>::isEqual(int state_index) const
{
	return (state_index == getStateIndex());
}

/**
 * @brief	�������H
 */
template <typename OWNER>
bool
StateMachine<OWNER>::isInvalid() const
{
	return (getStateIndex() == -1);
}

/**
 * @brief	�L�����H
 */
template <typename OWNER>
bool
StateMachine<OWNER>::isValid() const
{
	return (!isInvalid());
}

/**
 * @brief	�X�e�[�g�̕ύX
 */
template <typename OWNER>
void
StateMachine<OWNER>::changeState_(int state_index)
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
template <typename OWNER>
void
StateMachine<OWNER>::enterState_()
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->enter();
	}
}

/**
 * @brief	�X�e�[�g�̎��s
 */
template <typename OWNER>
void
StateMachine<OWNER>::exeState_()
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->exe();
	}
}

/**
 * @brief	�X�e�[�g�̏I��
 */
template <typename OWNER>
void
StateMachine<OWNER>::exitState_()
{
	if (mDelegate[mCurrentStateIndex] != nullptr)
	{
		mDelegate[mCurrentStateIndex]->exit();
	}
}
