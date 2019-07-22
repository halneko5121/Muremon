#pragma once
/******************************************************************
 *	@file	SceneBase.h
 *	@brief	�V�[���x�[�X
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Library/Input/DirectInput.h"

class Texture;
class Vertex;

enum SceneId
{
	cSceneId_Logo,			// ���S
    cSceneId_Title,			// �^�C�g��
    cSceneId_Prologue,		// ���炷��
	cSceneId_Tutorial,		// �Q�[���������
	cSceneId_GameRefresh,	// �Q�[���i��������j
	cSceneId_GameNormal,	// �Q�[���i�m�[�}���j
	cSceneId_Ending,		// �G���f�B���O
	cSceneId_Ranking,		// �����L���O
	cSceneId_GameEnd,		// �I���
	cSceneId_Count
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
	void				init();
	virtual void		impleInit();

	/**
	 * @brief	�X�V����
	 */
	virtual void		update();

	/**
	 * @brief	�`�揈��
	 */
	virtual void		draw() const {};

	/**
	 * @brief	�I������
	 */
	virtual void		end() {};

	/**
	 * @brief	�V�[���ύX���N�G�X�g���s��
	 * @param	nextID		���̃V�[���̔ԍ�
	 */
	void				requestChangeScene(DWORD next_id);

	/**
	 * @brief	�ύX����V�[���ԍ��̎擾
	 */
	DWORD				getChangeSceneID();

	/**
	 * @brief	�V�[���I����
	 */
	bool				isSceneEnd() const;

protected:
	Texture*			mTexture;			// �e�N�X�`��
	Vertex*				mVertex;			// �o�[�e�b�N�X
	bool				mIsSceneEnd;		// �V�[���I����
	MouseData			mMouseData;			// �}�E�X���

private:
	DWORD               mChangeSceneID;		// �ύX����V�[���ԍ�
};
