#pragma once
/******************************************************************
 *	@file	EffectBase.h
 *	@brief	�G�t�F�N�g���
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Define.h"

class Texture;
class Vertex;
enum EffectId;

class EffectBase
{
public:
	EffectBase(EffectId	id, Texture* texture, Vertex* vertex, int rect_index, POS_CC<float> pos);
	virtual ~EffectBase();

	virtual void	update() = 0;
	virtual void	draw() = 0;
	virtual bool	isEnd() = 0;

protected:
	EffectId		mId;
	Texture*		mTexture;		// �e�N�X�`��
	Vertex*			mVertex;		// �o�[�e�b�N�X
	int				mRectIndex;
	POS_CC<float>	mPos;

};