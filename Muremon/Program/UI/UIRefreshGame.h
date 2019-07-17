#pragma once
/******************************************************************
 *	@file	UIRefreshGame.h
 *	@brief	���t���b�V���Q�[��UI
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Texture;
class Vertex;
class ActorBoss;

class UIRefreshGame
{
public:
	UIRefreshGame();
	~UIRefreshGame();
	void				init();
	void				update();
	void				draw(const ActorBoss& boss) const;

private:
	void				drawKeyCount() const;
	void				drawHpGauge(const ActorBoss& boss) const;

private:
	Texture*			mTexture;				// �e�N�X�`��
	Vertex*				mVertex;				// �o�[�e�b�N�X
};