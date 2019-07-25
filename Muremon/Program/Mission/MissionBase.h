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
	explicit MissionBase(const MissionId& id, Texture* texture, Vertex* vertex);
	virtual ~MissionBase();

	void			run();
	void			update();

	// override �p
	virtual void	runImple() {};
	virtual void	updateImple() {};
	virtual void	draw() const = 0;
	virtual bool	isRunning() const = 0;	// ���s�����H
	virtual bool	isSuccess() const = 0;	// �����������H
	virtual bool	isFailure() const = 0;	// ���s�������H

protected:
	void			drawTime() const;
	void			drawCombo() const;

protected:
	MissionId		mId;
	Texture*		mTexture;			// �e�N�X�`��
	Vertex*			mVertex;			// �o�[�e�b�N�X
	int				mKeyCount;			// �L�[���͐�
	int				mTime;				// �~�b�V��������
};