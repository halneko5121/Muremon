/******************************************************************
 *	@file	ActorBase.cpp
 *	@brief	�A�N�^�[���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "ActorBase.h"

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

	// �`��ʒu
	const float cDispBossRadiusX = 150.f;		// BOSS�̔��a(X)
	const float cDispBossRadiusY = 200.f;		// BOSS�̔��a(Y)


	const float cDeadLinePosX = 300.f;			// �Q�[���I�[�o�[���C��
}

//l,t,r,b
//���S����A�㉺���E�̕�
RECT rect_pos_p[] = {
	{ cNikumanRadius ,cNikumanRadius ,cNikumanRadius ,cNikumanRadius },
	{ cYoshiHitRadius.x, cYoshiHitRadius.y, cYoshiHitRadius.x, cYoshiHitRadius.y },
	{ cNoppoHitRadius.x, cNoppoHitRadius.y, cNoppoHitRadius.x ,cNoppoHitRadius.y },
};

RECT rect_pos_e = {
	cDispBossRadiusX, cDispBossRadiusY, cDispBossRadiusX, cDispBossRadiusY
};

/**
 * @brief �R���X�g���N�^
 */
ActorBase::ActorBase(ActorId actor_id, int uniq_id, Texture* texture, Vertex* vertex)
	: mActorId(actor_id)
	, mUniqId(uniq_id)
	, mOrbit(nullptr)
	, mTexture(texture)
	, mVertex(vertex)
	, mRect(Vector2f(0.0f, 0.0f), 1.0f, 1.0f)
	, mRectStartNum(0)
	, mSoundStartNum(0)
	, mSpeed(0.0f)
	, mAnimation(0)
	, mRectNum(0)
	, mAlpha(255)
	, mNowPos(0.0f, 0.0f)
	, mScore(0)
	, mMissionPower(0)
	, mAtkPower(0)
	, mIsAtk1(false)
	, mIsAtk2(false)
	, mAngleDegree(0.0f)
	, mIsHitCheck(false)
	, mIsRun(false)
	, mHitPos(0.0f, 0.0f)
{
	mOrbit	 = new OrbitCalculation();
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
float
ActorBase::getSpeed() const
{
	return (float)(rand() % SPEED_RAND) + SPEED_MIN;
}

float
ActorBase::getNikumanSpeed() const
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
 * @brief �U������
 */
void
ActorBase::updateAttack1()
{
	// �E�Ɉړ�
	mNowPos.x += mSpeed;
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
		if (owner.getNowPos().y < 50) return false;
	case cActorId_Nikuman:
		if (owner.getNowPos().y < 75) return false;
	case cActorId_Noppo:
		if (owner.getNowPos().y < 0) return false;
	}

	/*
	if ((check_rect_p.right >= check_rect_e.left) && (check_rect_p.left <= check_rect_e.right) &&
		(check_rect_p.top <= check_rect_e.bottom) && (check_rect_p.bottom >= check_rect_e.top)) {
		return TRUE;
	}
	*/

	return FALSE;
}