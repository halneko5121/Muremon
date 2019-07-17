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
 * @brief �G�t�F�N�g�t�H���g�ʒu�̐ݒ�
 * @param	font_cc			�J�n�ʒu
 * @param	chara_radius	�L�������a
 * @param	range_font		�t�H���g�̑傫��
 * @return	���S���W
 */
Vector2f
ActorBase::setEffectFont(Vector2f font_cc ,float chara_radius, float range_font)
{
	Vector2f pos_effectfont = { 0.f	,0.f };

	//�w�׃`���I�x�Ƃ��\���ʒu(���S���W���獶��)
	pos_effectfont.x = (font_cc.x - (chara_radius + range_font) );
	pos_effectfont.y = (font_cc.y - (chara_radius + range_font) );

	return pos_effectfont;
}

/**
 * @brief �V�F�C�N����
 * @param	change_x		�h�ꕝ
 * @param	change_y		�h�ꕝ
 * @param	font_cc			�t�H���g�̒��S�ʒu
 * @return	���S���W
 */
Vector2f
ActorBase::setEffectShake(float change_x ,float change_y, Vector2f font_cc)
{
	static float shake_x	,shake_y	= 0.f; 
	static bool  flag_shake_right,flag_shake_down = false; 
	static int	 shake_count = 0;

	if(shake_x > change_x)			{ flag_shake_right = false; shake_count++; }
	else if(shake_x < (-change_x))	{ flag_shake_right = true;  shake_count++; }

	if(shake_y > change_y)		  { flag_shake_down = false; }
	else if(shake_y <-(change_y)) { flag_shake_down = true;  }

	if(shake_count > 5)	{ flag_shake_down = true;  shake_count = 0; }

	font_cc.x += (flag_shake_right) ? shake_x++ : shake_x--;
	font_cc.y += (flag_shake_down ) ? shake_y++ : shake_y--;

	return font_cc;
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
ActorBase::isHit(Vector2f draw_cc_p, Vector2f draw_cc_e, int chara_id) const
{
	RectF check_rect_p = { 0.f,0.f,0.f,0.f };
	RectF check_rect_e = { 0.f,0.f,0.f,0.f };

	if (draw_cc_p.x < cDeadLinePosX) return FALSE;

	switch (chara_id) {
	case ID_YOSHI:
		if (draw_cc_p.y < 50) return FALSE;	break;
	case ID_NIKUMAN:
		if (draw_cc_p.y < 75) return FALSE;	break;
	case ID_NOPPO:
		if (draw_cc_p.y < 0) return FALSE;	break;
	}

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
