#pragma once
/******************************************************************
 *	@file	SceneTutorial.h
 *	@brief	�`���[�g���A���V�[��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Program/Scene/SceneBase.h"
#include "Library/Graphics/Texture.h"
#include "Library/Graphics/Vertex.h"

class SceneTutorial : public SceneBase
{
public:
	SceneTutorial();
	~SceneTutorial();

	void			impleInit() override;
	bool			update() override;
	void			draw() override;
	int				end() override;

	void			updateInput();		// �L�[����
	void			updateDrawPos();	// �`��ʒu�Ȃǂ����߂�
	void			fadeControl();		// �t�F�[�h�R���g���[��		
	void			fadeIn();			// �t�F�[�h�C��
	void			fadeOut();			// �t�F�[�h�A�E�g

private:

	int				mDrawState;			// �`�悵�Ă�����̂�m�点��
	int				mSlideState;
	D3DXVECTOR2		mTutorial[2];

	int				mFadeFlag;			// �t�F�[�h�̃t���O
	int				mAlpha;				// �A���t�@�l
	int				mAlphaCount;		// �A���t�@�l�̃J�E���g
};
