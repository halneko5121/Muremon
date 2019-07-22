#pragma once
/******************************************************************
 *	@file	Vertex.h
 *	@brief	�o�[�e�b�N�X�̊Ǘ����s��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include "Texture.h"

class Vertex
{
public:
	/**
	 * @brief	�R���X�g���N�^
	 */
	Vertex();

	/**
	 * @brief	�f�X�g���N�^
	 */
	~Vertex();

	/**
	 * @brief	�e�N�X�`���̃f�[�^���Z�b�g����
	 * @param	pTexture	�e�N�X�`���f�[�^
	 * @param	pD3dDevice  �f�o�C�X
	 */
	void	setTextureData(LPDIRECT3DTEXTURE9* texture, LPDIRECT3DDEVICE9 d3d_device);

	/**
	 * @brief	�e�N�X�`���̊g��E�k�������w��
	 * @param	scale_x    �����̊g�嗦:
	 * @param	scale_y    �c���̊g�嗦
	 */
	void	setScale(float scale_x, float scale_y);

	/**
	 * @brief	�e�N�X�`���̉�]�p�x���w��
	 * @param	angle		��]������p�x
	 */
	void	setAngle(float degree);

	/**
	 * @brief	�e�N�X�`���̐F�w��
	 * @param	alpha   �A���t�@�l
	 * @param	red		�Ԃ̒l
	 * @param	green	�΂̒l
	 * @param	blue	�̒l
	 */
	void	setColor(D3DCOLOR alpha, D3DCOLOR red, D3DCOLOR green, D3DCOLOR blue);

	/**
	 * @brief	�e�N�X�`���̕`����s��
	 * @param	x			X���W
	 * @param	y			Y���W
	 * @param	rect_num	�o�^����Ă����`��No
	 */
	void	drawLT(const Vector2f& pos, int rect_num) const; // �}�E�X�J�[�\���p���쐬
	void	drawCB(const Vector2f& pos, int rect_num) const; // ���S�̉�����
	void	drawF(const Vector2f& pos, int rect_num) const;

	/**
	 * @brief	��`��txt�f�[�^����ǂݍ���
	 * @param	file_name		txt�t�@�C����
	 * @return	���[�h���������������s������
	 */
	bool	load(const char* file_name);

private:
	int					mTextureWidth;		// ����
	int					mTextureHeight;		// �c��
	float				mTextureU;			// �e�N�X�`��UV�l
	float				mTextureV;			// �e�N�X�`��UV�l
	float				mScaleX;			// X�����̊g�嗦
	float				mScaleY;			// Y�����̊g�嗦
	float				mDegree;			// �p�x
	int					mLoadedRectCount;	// �ǂݍ��܂�Ă����`�̑���
	D3DCOLOR			mColor;				// �F
	RECT*				mRectPosition;		// ��`
	LPDIRECT3DDEVICE9	mDevice;			// �f�o�C�X
	LPDIRECT3DTEXTURE9*	mTexture;			// �e�N�X�`��
};