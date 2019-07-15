/******************************************************************
 *	@file	UIRefreshGame.cpp
 *	@brief	���t���b�V���Q�[��UI
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UIRefreshGame.h"

#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/DefineGame.h"

namespace
{
	// �\���ʒu
	// ...
}

/**
 * @brief	�R���X�g���N�^
 */
UIRefreshGame::UIRefreshGame()
	: mTexture(nullptr)
	, mVertex(nullptr)
{
	mTexture = new Texture();
	mVertex = new Vertex();
}

/**
 * @brief	�f�X�g���N�^
 */
UIRefreshGame::~UIRefreshGame()
{
}

/**
 * @brief	������
 */
void
UIRefreshGame::init()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "title");
}

/**
 * @brief	�X�V
 */
void
UIRefreshGame::update()
{
}

/**
 * @brief	�`��
 */
void
UIRefreshGame::draw(const ActorBoss& boss)
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	// �X�e�[�^�X�g�`��
	mVertex->drawF(cDispStateFramePos, R_STATE_FRAME);

	mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconNikumanPosY), R_F_NIKUMAN);	//�ɂ��܂��
	mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconYoshiPosY), R_F_YOSHITARO);	//�悵���낤��
	mVertex->drawF(Vector2f(cDispFaceIconPosX, cDispFaceIconNoppoPosY), R_F_NOPPO);		//�̂��ۊ�

	drawKeyCount();
	drawHpGauge(boss);
}

/**
 * @brief	�A�Ő��`��
 */
void 
UIRefreshGame::drawKeyCount()
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	//�ɂ��܂�
	for (int i = 0;i < 4;i++) {
		int num = UtilBattle::getWeakAtkCount();
		for (int j = 1;j < 4 - i;j++) {
			num = (num / 10);
		}
		mVertex->drawF(Vector2f(cDispPushKeyCountPosX + 20.f * i, cDispFaceIconNikumanPosY), R_0 + num % 10);
	}
	//�悵���낤
	for (int i = 0;i < 4;i++) {
		int num = UtilBattle::getMediumAtkCount();
		for (int j = 1;j < 4 - i;j++) {
			num = (num / 10);
		}
		mVertex->drawF(Vector2f(cDispPushKeyCountPosX + 20.f * i, cDispFaceIconYoshiPosY), R_0 + num % 10);
	}
	//�̂���
	for (int i = 0;i < 4;i++) {
		int num = UtilBattle::getStrongAtkCount();
		for (int j = 1;j < 4 - i;j++) {
			num = (num / 10);
		}
		mVertex->drawF(Vector2f(cDispPushKeyCountPosX + 20.f * i, cDispFaceIconNoppoPosY), R_0 + num % 10);
	}
}

/**
 * @brief	HP�Q�[�W�̕`��
 */
void
UIRefreshGame::drawHpGauge(const ActorBoss& boss)
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	// �u��������̗̑́v
	mVertex->drawF(cDispBossHpPos, R_HP);

	// ���ۂ̗̑̓Q�[�W��
	float num = boss.mLife / boss.mMaxLife;
	mVertex->setScale(num, 1.0f);
	mVertex->setColor(255, 255, 0, 0);
	mVertex->drawF(Vector2f(cDispGaugePos.x - (1.f - num) * 100.f, cDispGaugePos.y), R_GAGE_IN);	//�̗̓Q�[�W

	// �̗̓Q�[�W�́u�g�v
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	mVertex->drawF(cDispGaugePos, R_GAGE_FRAME);
}