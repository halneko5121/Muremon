#pragma once
/******************************************************************
 *	@file	EffectMgr.h
 *	@brief	�G�t�F�N�g�Ǘ�
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Define.h"

enum EffectId
{
	cEffectId_Null = -1,	// �Ȃ�
	cEffectId_HitEffect1,	// �q�b�g�������̃G�t�F�N�g
	cEffectId_HitEffect2,	//�w�x�`���b�I�I�x	
	cEffectId_HitEffect3,	//�w�ڂ�[��x		
	cEffectId_HitEffect4,	//�w�ς���I�x	
	cEffectId_HitEffect5,	//�w�y�`�b�x	
	cEffectId_HitEffect6,	//�w�S�b�I�x
	cEffectId_HitEffect7,	//�wNO�`�I�I�x
	cEffectId_Count,
};

class EffectBase;
class Texture;
class Vertex;

class EffectMgr
{
public:
	typedef std::list<EffectBase*>::iterator EffectIterator;

public:
	EffectMgr();
	~EffectMgr();

	/**
	 * @brief	�C���X�^���X�̎擾
	 */
	static EffectMgr*	getInstance();

	/**
	 * @brief	�C���X�^���X�̐���
	 */
	static void			create();

	/**
	 * @brief	�C���X�^���X�̔j��
	 */
	static void			destroy();

	/**
	 * @brief	����
	 */
	void				createEffect(EffectId id, Texture*	texture, Vertex* vertex, POS_CC<float> pos);

	/**
	 * @brief	�X�V
	 */
	void				update();

	/**
	 * @brief	�`��
	 */
	void				draw();

private:
	typedef std::list<EffectBase*>	EffectList;

private:
	static EffectMgr*	mInstance;			// �C���X�^���X
	EffectList			mEffectList;		// �G�t�F�N�g��ۊǂ��Ă������X�g
};

static EffectMgr* GetEffectMgr() { return EffectMgr::getInstance(); }