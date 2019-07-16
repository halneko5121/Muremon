#pragma once
/******************************************************************
 *	@file	MissionBase.h
 *	@brief	�~�b�V�������
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Texture;
class Vertex;
enum MissionId;

class MissionBase
{
public:
	MissionBase(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~MissionBase();

	void			run();

	virtual void	runImple() = 0;
	virtual void	update() = 0;
	virtual void	draw() = 0;
	virtual bool	isSuccess() const = 0;
	virtual bool	isFailure() const = 0;

	void			drawTime();
	void			drawCombo();

protected:
	MissionId		mId;
	Texture*		mTexture;		// �e�N�X�`��
	Vertex*			mVertex;		// �o�[�e�b�N�X
	int				mTime;
	int				mKeyCount;
};