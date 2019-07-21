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
	void				draw(const float& mission_guage, const int& time) const;

private:
	void				drawMissionGuage(const float& mission_guage) const;
	void				drawScore() const;
	void				drawTime(const int& time) const;

private:
	Texture*			mTexture;				// �e�N�X�`��
	Vertex*				mVertex;				// �o�[�e�b�N�X
	UIRefreshGame*		mUIRefreshGame;			// ���t���b�V���Q�[��UI
};