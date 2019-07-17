/******************************************************************
 *	@file	MissionBase.cpp
 *	@brief	�~�b�V�������
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "MissionBase.h"

#include "Library/Graphics/Vertex.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/DefineGame.h"

namespace
{
	const int cTimeLimitFrame = 600;
	const Vector2f cDispMissionTimePos = { 375.0f, 125.0f };
	const Vector2f cDispCombo = { 500.0f, 245.0f };
}

 /**
  * @brief	�R���X�g���N�^
  */
MissionBase::MissionBase(MissionId id, Texture* texture, Vertex* vertex)
	: mId(id)
	, mTexture(texture)
	, mVertex(vertex)
	, mKeyCount(0)
	, mSuccessTypingCount(1)
	, mTime(0)
{
}

/**
 * @brief	�f�X�g���N�^
 */
MissionBase::~MissionBase()
{
}

/**
 * @brief	���s
 */
void
MissionBase::run()
{
	mTime = cTimeLimitFrame;
	mKeyCount = 0;
	mSuccessTypingCount = 1;

	runImple();
}

/**
 * @brief	�X�V
 */
void
MissionBase::update()
{
	updateImple();
}

/**
 * @brief	���Ԑ؂ꂩ�H
 */
bool
MissionBase::isTimeOver() const
{
	return (mTime == 0);
}

void 
MissionBase::drawTime() const
{
	// �^�C��
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	for (int i = 0;i < 2;i++) {
		int num = mTime;
		for (int j = 0;j < 2 - i;j++) {
			if (j == 0) {
				num = num / 60;
			}
			else {
				num = num / 10;
			}
		}
		mVertex->drawF(Vector2f(cDispMissionTimePos.x + 50.f * i, cDispMissionTimePos.y), R_0_B + num % 10);
	}
}

void 
MissionBase::drawCombo() const
{
	// �R���{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	for (int i = 0;i < 3;i++) {
		int num = mKeyCount;
		for (int j = 1;j < 3 - i;j++) {
			num = num / 10;
		}
		mVertex->drawF(Vector2f(cDispCombo.x + 50.f + 50.f * i, cDispCombo.y), R_0_B + num % 10);
	}
	mVertex->drawF(cDispCombo, R_COMBO);
}