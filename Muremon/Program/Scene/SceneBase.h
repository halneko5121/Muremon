#pragma once
/******************************************************************
 *	@file	SceneBase.h
 *	@brief	�V�[���x�[�X
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"
#include "Library/Input/DirectInput.h"

class DirectInputKey;
class DirectInputMouse;
class C_DWaveSound;
class Texture;
class Vertex;
class C_Sprite;
class C_Animetion;
namespace Dix
{
	class C_PCMPlayer;
}

enum SceneName
{
	cSceneName_Logo,		// ���S
    cSceneName_Title,		// �^�C�g��
    cSceneName_Prologue,	// ���炷��
	cSceneName_Tutorial,	// �Q�[���������
	cSceneName_GameRefresh,	// �Q�[���i��������j
	cSceneName_GameNormal,	// �Q�[���i�m�[�}���j
	cSceneName_Ending,		// �G���f�B���O
	cSceneName_Ranking,		// �����L���O
	cSceneName_GameEnd,		// �I���
};

class SceneBase
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	SceneBase();

	/**
	 * @brief	�f�X�g���N�^
	 */
	virtual ~SceneBase();

	/**
	 * @brief	����������
	 */
	void				init(LPDIRECT3DDEVICE9 apDev);
	virtual void		impleInit();

	/**
	 * @brief	�X�V����
	 * @return	�V�[���I����
	 */
	virtual bool		update() = 0;

	/**
	 * @brief	�`�揈��
	 */
	virtual void		draw() = 0;

	/**
	 * @brief	�I������
	 */
	virtual void		end() = 0;

	/*-		���ʊ֐�	-*/

	/**
	 * @brief	���s����
	 */
	bool				runScene();

	/**
	 * @brief	�V�[���ύX���N�G�X�g���s��
	 * @param	nextID		���̃V�[���̔ԍ�
	 */
	void				requestChangeScene(DWORD next_id);

	//-���擾�֐�-

	/**
	 * @brief	�V�[���ԍ��̎擾
	 */
	DWORD				getSceneID();

protected:
    DWORD               mSceneID;		// �V�[���̔ԍ�
	LPDIRECT3DDEVICE9	mDevice;		// �f�o�C�X
	Texture*			mTexture;
	Vertex*				mVertex;

	int					mAlpha;			// �e�V�[����alpha�l		
	bool				mIsSceneChange;	// �V�[�����ς�鎞��m�点��
	MouseData			mMouseData;		// �}�E�X���
};
