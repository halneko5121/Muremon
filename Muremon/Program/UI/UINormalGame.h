#pragma once
/******************************************************************
 *	@file	UINormalGame.h
 *	@brief	�m�[�}���Q�[��UI
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Texture;
class Vertex;
class ActorBoss;
class UIRefreshGame;

class UINormalGame
{
public:
	UINormalGame();
	~UINormalGame();
	void				init();
	void				update();
	void				draw(const ActorBoss& boss, const float& mission_guage, const int& time);

private:
	void				drawMissionGuage(const float& mission_guage);
	void				drawScore();
	void				drawTime(const int& time);

private:
	Texture*			mTexture;				// �e�N�X�`��
	Vertex*				mVertex;				// �o�[�e�b�N�X
	UIRefreshGame*		mUIRefreshGame;			// ���t���b�V���Q�[��UI
};