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
}

//l,t,r,b
//���S����A�㉺���E�̕�
RectF rect_pos_p[] = {
	{ cNikumanRadius ,cNikumanRadius ,cNikumanRadius ,cNikumanRadius },
	{ cYoshiHitRadius.x, cYoshiHitRadius.y, cYoshiHitRadius.x, cYoshiHitRadius.y },
	{ cNoppoHitRadius.x, cNoppoHitRadius.y, cNoppoHitRadius.x ,cNoppoHitRadius.y },
};

RectF rect_pos_e = {
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
	, mBossPos(0.0f, 0.0f)
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
ActorBase::update(Vector2f boss_cc)
{
	updateImple(boss_cc);
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
ActorBase::isHit(const Vector2f& draw_cc_p, const Vector2f& draw_cc_e, int chara_id) const
{
	if (draw_cc_p.x < cDeadLinePosX) return FALSE;

	switch (chara_id) {
	case ID_YOSHI:
		if (draw_cc_p.y < 50) return FALSE;	break;
	case ID_NIKUMAN:
		if (draw_cc_p.y < 75) return FALSE;	break;
	case ID_NOPPO:
		if (draw_cc_p.y < 0) return FALSE;	break;
	}

	RectF check_rect_p = { 0.f,0.f,0.f,0.f };
	RectF check_rect_e = { 0.f,0.f,0.f,0.f };
	calculateBackRect(&check_rect_p, rect_pos_p[chara_id], draw_cc_p);
	calculateBackRect(&check_rect_e, rect_pos_e, draw_cc_e);

	if ((check_rect_p.right >= check_rect_e.left) && (check_rect_p.left <= check_rect_e.right) &&
		(check_rect_p.top <= check_rect_e.bottom) && (check_rect_p.bottom >= check_rect_e.top)) {
		return TRUE;
	}

	return FALSE;
}

/**
 * @brief ���S���W�����`���t�Z
 */
void
ActorBase::calculateBackRect(RectF* dst_pos, const RectF& rect_pos, const Vector2f& draw_cc) const
{
	APP_POINTER_ASSERT(dst_pos);

	// ���S���W���炻�ꂼ��G�̔��a�����E���Z 
	dst_pos->left = (draw_cc.x - rect_pos.left);
	dst_pos->top = (draw_cc.y - rect_pos.top);
	dst_pos->right = (draw_cc.x + rect_pos.right);
	dst_pos->bottom = (draw_cc.y + rect_pos.bottom);
}
