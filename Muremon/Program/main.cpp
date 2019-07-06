/******************************************************************
 *	@file	main.cpp
 *	@brief	���C��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include <crtdbg.h> //�������[���[�N�`�F�b�N
#include "main.h"
#include "System/GameMain.h"

/**
 * @brief	���C��(��������v���O�������X�^�[�g)
 * @param	hInstance   �C���X�^���X�n���h��(�v���O�����𓮂������߂̂���)
 * @param	hPrevInst	���̑O�̏�Ԃ�ۑ����Ă���	(1�ڂɏ�񂪓����ĂȂ��������p)
 * @param	lpCmdLine   Windows����̖��߂��i�[�����(�|�C���^�̐擪�A�h���X)
 * @param	nShowCmd	���̖��߂���������̂�
 * @return	���[�v
 * @note	WINAPI		�E�B���h�E�A�v���P�[�V�����ł���Ƃ킩�点�邽�߂̂���
 * @note	WinMain		���ꂪ�Ȃ���Windows�A�v���P�[�V�����̎n�܂肪�킩��Ȃ�
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	// �C���X�^���X����
	GameMain game_main;

	int l_return = game_main.WinMain(hInstance,hPrevInst,lpCmdLine,nShowCmd);

	// ���݂̃��������[�N��Ԃ��킩��
	_CrtDumpMemoryLeaks();

	return l_return;
}