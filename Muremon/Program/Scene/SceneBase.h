#pragma once
/******************************************************************
 *	@file	SceneManage.h
 *	@brief	�V�[���̊Ǘ����s��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"
#include "Library/Input/DirectInput.h"

class C_DInputKey;
class C_DInputMouse;
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
	virtual void Init() = 0;

	/**
	 * @brief	�X�V����
	 * @return	�V�[���I����
	 */
	virtual bool Update() = 0;

	/**
	 * @brief	�`�揈��
	 */
	virtual void Draw() = 0;

	/**
	 * @brief	�I������
	 */
	virtual int End() = 0;

	/*-		���ʊ֐�	-*/

	/**
	 * @brief	���s����
	 */
	bool RunScene();

	/**
	 * @brief	�ݒ菈��
	 * @param	apDev		�f�o�C�X
	 */
	void SetScene(LPDIRECT3DDEVICE9 apDev);

	/**
	 * @brief	�V�[���̕ύX���s��
	 * @param	nextID		���̃V�[���̔ԍ�
	 */
	void ChangeScene(DWORD next_id);

	//-���擾�֐�-

	/**
	 * @brief	�V�[���ԍ��̎擾
	 */
	DWORD GetSceneID();

protected:
    DWORD               mSceneID;		// �V�[���̔ԍ�
	LPDIRECT3DDEVICE9	mDevice;		// �f�o�C�X
	Texture*			mTexture;
	Vertex*			mVertex;

	int					mAlpha;			// �e�V�[����alpha�l		
	bool				mIsSceneChange;	// �V�[�����ς�鎞��m�点��
	MouseData			mMouseData;		// �}�E�X���
};
