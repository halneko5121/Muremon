//---------------------------------------------
//
//      �V�[���̊Ǘ����s��
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

//include
#include "SceneManage.h"

//////////////////////////////////////////////////////////
//
//      �����@�F�R���X�g���N�^
//
//////////////////////////////////////////////////////////
C_SceneManage::C_SceneManage()
{
    sceneID = LOGO;    //������
}

//////////////////////////////////////////////////////////
//
//      �����@�F�f�X�g���N�^(���z�֐��A�������Ȃ�)
//
//////////////////////////////////////////////////////////
C_SceneManage::~C_SceneManage()
{

}

//////////////////////////////////////////////////////////
//
//      �����@�F�V�[���̏���������(�����o������)
//      �����@�FLPDIRECT3DDEVICE9   pDev    �f�o�C�X
//              DInput              *pInput �C���v�b�g�N���X�ւ̃|�C���^
//              DFont               *pFont  �t�H���g�N���X�ւ̃|�C���^
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////

//void SceneManage::InitScene(LPDIRECT3DDEVICE9 apDev , DInput *apInput , DFont *apFont)
//{
//	pDevice = apDev;	//�f�o�C�X�Z�b�g
//	pInput	= apInput;	//�L�[���͂�n��
//    pFont   = apFont;   //�����\���\�ɂ���
//}

void C_SceneManage::InitScene(LPDIRECT3DDEVICE9 apDev , /*C_DInput *apInput ,*/ C_DFont *apFont, /*MapRead *apMapRead,*/ C_DSound *apSound,int score)
{
	pDevice = apDev;	//�f�o�C�X�Z�b�g
	//pInput	= apInput;	//�L�[���͂�n��
    pFont   = apFont;   //�����\���\�ɂ���
	//pSound	= apSound;
	/*pMapRead = apMapRead;*/
}

//////////////////////////////////////////////////////////
//
//      �����@�F�V�[���̕ύX���s��
//      �����@�FDWORD   nextID  ���̃V�[���̔ԍ�
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_SceneManage::ChangeScene(DWORD nextID)
{
    sceneID = nextID;   //���̃V�[���ԍ���n��
}

//////////////////////////////////////////////////////////
//
//      �����@�F�����蔻����s��
//      �����@�FD3DXVECTOR2 centerPos   ��������Ƃ镨�̂̒��S���W
//              D3DXVECTOR2 size        ��������Ƃ镨�̂̃T�C�Y
//              DInput      *pInput     �C���v�b�g�N���X�ւ̃|�C���^
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
bool C_SceneManage::HitCheck(D3DXVECTOR2 centerPos , D3DXVECTOR2 size)
{
    //if(pInput->GetMousePosition().x >= centerPos.x - size.x / 2.0f &&
    //    pInput->GetMousePosition().x <= centerPos.x + size.x / 2.0f)
    //{
    //    if(pInput->GetMousePosition().y >= centerPos.y - size.y / 2.0f &&
    //        pInput->GetMousePosition().y <= centerPos.y + size.y / 2.0f)
    //    {
    //        return true;    //�͈͓��ɓ����Ă���Γ������Ă���
    //    }
    //}
    return false;   //���i�͓������Ă��Ȃ��̂�false
}