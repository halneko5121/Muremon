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

#define TEN_SECOND	(600)
#define M_TIMENUM_X	(375.f)
#define M_TIMENUM_Y	(125.f)
#define M_COMBO_X	(500.f)
#define M_COMBO_Y	(245.f)

 /**
  * @brief	�R���X�g���N�^
  */
MissionBase::MissionBase(MissionId id, Texture* texture, Vertex* vertex)
	: mId(id)
	, mTexture(texture)
	, mVertex(vertex)
	, mTime(0)
	, mKeyCount(0)
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
	mTime = TEN_SECOND;

	runImple();
}

void 
MissionBase::drawTime()
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
		mVertex->drawF(Vector2f(M_TIMENUM_X + 50.f * i, M_TIMENUM_Y), R_0_B + num % 10);
	}
}

void 
MissionBase::drawCombo()
{
	// �R���{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	for (int i = 0;i < 3;i++) {
		int num = mKeyCount;
		for (int j = 1;j < 3 - i;j++) {
			num = num / 10;
		}
		mVertex->drawF(Vector2f(M_COMBO_X + 50.f + 50.f * i, M_COMBO_Y), R_0_B + num % 10);
	}
	mVertex->drawF(Vector2f(M_COMBO_X, M_COMBO_Y), R_COMBO);
}