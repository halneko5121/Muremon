#pragma once
/******************************************************************
 *	@file	UtilGame.h
 *	@brief	�Q�[���֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Rect;
class ActorBase;

namespace UtilGame
{
	// �Q�[�����[�h
	void				setGameModeRefresh();
	void				setGameModeNormal();
	bool				isGameModeRefresh();
	bool				isGameModeNormal();

	// �X�R�A�֘A
	void				setScore(int score);
	int					getScore();
	void				addScore(int add_score);
	void				mulScore(int mul_score);

	// ���̑�
	float				getGroundPosY();
	bool				isScreenOut(const ActorBase& owner);
	bool				isScreenOutWithoutLeft(const ActorBase& owner);
}