/******************************************************************
 *	@file	UINormalGame.cpp
 *	@brief	�m�[�}���Q�[��UI
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "UINormalGame.h"

#include "Library/Graphics/Vertex.h"
#include "Library/Graphics/Texture.h"
#include "Program/Util/UtilGraphics.h"
#include "Program/Util/UtilBattle.h"
#include "Program/Util/UtilGame.h"
#include "Program/Actor/ActorBoss.h"
#include "Program/UI/UIRefreshGame.h"

namespace
{
	// �\���ʒu
	const Vector2f cDispScorePos = { 60.0f, 20.0f };
	const Vector2f cDispTimePos = { 60.0f, 70.0f };

	const float cMaxMissionGauge = 5000.0f;
}

/**
 * @brief	�R���X�g���N�^
 */
UINormalGame::UINormalGame()
	: mTexture(nullptr)
	, mVertex(nullptr)
{
	mTexture = new Texture();
	mVertex = new Vertex();
	mUIRefreshGame = new UIRefreshGame();
}

/**
 * @brief	�f�X�g���N�^
 */
UINormalGame::~UINormalGame()
{
	mTexture->release();
	APP_SAFE_DELETE(mTexture);
	mVertex->release();
	APP_SAFE_DELETE(mVertex);
}

/**
 * @brief	������
 */
void
UINormalGame::init()
{
	UtilGraphics::loadVertexAndTexture(mVertex, mTexture, "gamenormal");
	mUIRefreshGame->init();
}

/**
 * @brief	�X�V
 */
void
UINormalGame::update()
{
}

/**
 * @brief	�`��
 */
void
UINormalGame::draw(const ActorBoss& boss, const float& mission_guage, const int& time) const
{
	mUIRefreshGame->draw(boss);

	drawMissionGuage(mission_guage);

	drawScore();

	drawTime(time);
}

/**
 * @brief	�~�b�V�����Q�[�W�̕`��
 */
void
UINormalGame::drawMissionGuage(const float& mission_guage) const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	// �u�݂������Q�[�W�v
	mVertex->drawF(cDispMissionPos, R_MISSION_GAGE);

	// ���ۂ̃~�b�V�����Q�[�W��
	float num = mission_guage / cMaxMissionGauge;
	mVertex->setScale(num, 1.f);
	mVertex->setColor(255, 30, 30, 200);
	mVertex->drawF(Vector2f(cDispMissionGaugePos.x - (1.f - num) * 100.f, cDispMissionGaugePos.y), R_GAGE_IN);

	// �~�b�V�����Q�[�W�́u�g�v
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);
	mVertex->drawF(cDispMissionGaugePos, R_GAGE_FRAME);	//�݂������Q�[�W�g
}

/**
 * @brief	�X�R�A�̕`��
 */
void
UINormalGame::drawScore() const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	mVertex->drawF(cDispScorePos, R_SCORE);		//������

	//�X�R�A
	for (int i = 0;i < 9;i++) {
		int num = UtilGame::getScore();
		for (int j = 1; j < 9 - i;j++) {
			num = num / 10;
		}
		mVertex->drawF(Vector2f(cDispScoreNumPos.x + 20.f * i, cDispScoreNumPos.y), R_0 + num % 10);
	}
}

/**
 * @brief	�^�C���̕`��
 */
void
UINormalGame::drawTime(const int& time) const
{
	UtilGraphics::setTexture(mVertex, *mTexture, T_GAME_FONT);

	mVertex->drawF(cDispTimePos, R_TIME);		//������

	//�^�C��
	for (int i = 0;i < 5;i++)
	{
		int num = time;
		if (i != 2)
		{
			int a = 0;
			if (i > 2)
			{
				a = i - 1;
			}
			else
			{
				a = i;
			}
			for (int j = 0;j < 4 - a;j++)
			{
				if (j == 0)
				{
					num = num / 60;
				}
				else if (j == 2)
				{
					num = num / 6;
				}
				else
				{
					num = num / 10;
				}
			}
			if (i == 0 || i == 3)
			{
				mVertex->drawF(Vector2f(cDispTimeNumPos.x + 20.f * i, cDispTimeNumPos.y), R_0 + num % 6);
			}
			else
			{
				mVertex->drawF(Vector2f(cDispTimeNumPos.x + 20.f * i, cDispTimeNumPos.y), R_0 + num % 10);
			}
		}
		else
		{
			mVertex->drawF(Vector2f(cDispTimeNumPos.x + 20.f * i, cDispTimeNumPos.y), R_SEMICORON);
		}
	}
}

