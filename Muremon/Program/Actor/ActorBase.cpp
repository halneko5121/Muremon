/******************************************************************
 *	@file	ActorBase.cpp
 *	@brief	�A�N�^�[���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "ActorBase.h"

#include "Library/Math/Rect.h"
#include "Library/Graphics/DirectGraphics.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Actor/ActorMgr.h"

namespace
{
	// ���x�֌W
	const int SPEED_RAND		= (450 / 60);	// �L�����̑���		
	const int SPEED_MIN			= (200 / 60);

	// ���܂�(����)
	const int SPEED_RAND_NIKU	= 15;			// ���̉񐔂������ĖړI�n�_�ɓ��B����
	const int SPEED_MIN_NIKU	= 15;

	const float cDeadLinePosX = 300.f;			// �Q�[���I�[�o�[���C��
}

/**
 * @brief �R���X�g���N�^
 */
ActorBase::ActorBase(ActorId actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: mActorId(actor_id)
	, mUniqId(uniq_id)
	, mTexture(texture)
	, mVertex(vertex)
	, mRect(Vector2f(0.0f, 0.0f), 1.0f, 1.0f)
	, mRectNum(0)
	, mRectStartNum(0)
	, mSoundStartNum(0)
	, mNowPos(0.0f, 0.0f)
	, mSpeed(0.0f)
	, mAngleDegree(0.0f)
	, mAnimation(0)
	, mAlpha(255)
	, mScore(0)
	, mMissionPower(0)
	, mAtkPower(0)
	, mIsAtk1(false)
	, mIsAtk2(false)
	, mIsHitCheck(false)
	, mIsRun(false)
{
}

/**
 * @brief �f�X�g���N�^
 */
ActorBase::~ActorBase()
{
}

/**
 * @brief ������
 */
void
ActorBase::init()
{
	initImple();
}

/**
 * @brief ���s
 */
void
ActorBase::run()
{
	mIsRun = true;

	runImple();
}

/**
 * @brief �X�V
 */
void
ActorBase::update()
{
	updateImple();
}

/**
 * @brief �`��
 */
void
ActorBase::draw() const
{
	drawImple();
}


/**
 * @brief �X�s�[�h�̐ݒ�
 */
void
ActorBase::setSpeed(float speed)
{
	mSpeed = speed;
}

/**
 * @brief �X�s�[�h�̎擾
 */
float
ActorBase::getSpeed() const
{
	return mSpeed;
}

/**
 * @brief �����_���ȃX�s�[�h�̎擾
 */
float
ActorBase::getRandomSpeed() const
{
	return (float)(rand() % SPEED_RAND) + SPEED_MIN;
}

float
ActorBase::getRandomNikumanSpeed() const
{
	return (float)(rand() % SPEED_RAND_NIKU) + SPEED_MIN_NIKU;
}

/**
 * @brief	�U���t���O�̐ݒ�
 * @param	start_x	�J�n�ʒu
 * @return	�L�����f�[�^(�t���O�̏��)
 */
void
ActorBase::setGroundAtkFlag()
{
	mIsAtk1 = true;
}
void
ActorBase::setSkyAtkFlag()
{
	mIsAtk2 = true;
}

/**
 * @brief �Փ˃`�F�b�N
 */
bool
ActorBase::isHit(const ActorBase& owner, const ActorBase& target) const
{
	if (owner.getNowPos().x < cDeadLinePosX) return false;

	switch (owner.getActorId()) {
	case cActorId_Yoshi:
		if (owner.getNowPos().y < 50)		return false;
	case cActorId_Nikuman:
		if (owner.getNowPos().y < 75)		return false;
	case cActorId_Noppo:
		if (owner.getNowPos().y < 0)		return false;
	}

	// ��`�̏d�Ȃ���`�F�b�N
	if (owner.getRect().isInclude(target.getRect()))
	{
		return true;
	}

	return false;
}