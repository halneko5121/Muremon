//---------------------------------------------
//
//      ���C��
//      �쐬�J�n��:2��16��
//      �X�V��:2��16��
//      �쐬��:����
//
//---------------------------------------------

#include <crtdbg.h> // �������[���[�N�`�F�b�N
#include "main.h"
#include "Program/gManage/GameManage.h"

//////////////////////////////////////////////////////////
//
//      �����@�F���C��(��������v���O�������X�^�[�g)
//      ����  �FHINSTANCE   hInstance   �C���X�^���X�n���h��
//              HINSTANCE   hPrevInst   �Q�[�����C���ɓn��
//              LPSTR       lpCmdLine   �Q�[�����C���ɓn��
//              int         nShowCmd    �Q�[�����C���ɓn��
//      �߂�l�Fint         ���[�v
//
//////////////////////////////////////////////////////////
int	WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd)
{
	int l_return = 0;
	C_GameMain gMain;	//�C���X�^���X����

	l_return = gMain.WinMain(hInstance,hPrevInst,lpCmdLine,nShowCmd);

	_CrtDumpMemoryLeaks();					// ���݂̃��������[�N��Ԃ��킩��

	return l_return;
}