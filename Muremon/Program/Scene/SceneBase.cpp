//---------------------------------------------
//
//      �V�[���̊Ǘ����s��
//      �쐬�J�n��:3��17��
//			�X�V��:3��17��
//			�쐬��:����
//
//---------------------------------------------

#include "SceneBase.h"
#include "Library/Sound/DirectSound.h"

//////////////////////////////////////////////////////////
//
//      �����@�F�R���X�g���N�^
//
//////////////////////////////////////////////////////////
C_SceneBase::C_SceneBase()
{
    sceneID = LOGO;    //������
}

//////////////////////////////////////////////////////////
//
//      �����@�F�f�X�g���N�^(���z�֐��A�������Ȃ�)
//
//////////////////////////////////////////////////////////
C_SceneBase::~C_SceneBase()
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

void C_SceneBase::InitScene(LPDIRECT3DDEVICE9 apDev , C_DFont* apFont, int score)
{
	pDevice = apDev;	//�f�o�C�X�Z�b�g
    pFont   = apFont;   //�����\���\�ɂ���
}

//////////////////////////////////////////////////////////
//
//      �����@�F�V�[���̕ύX���s��
//      �����@�FDWORD   nextID  ���̃V�[���̔ԍ�
//�@�@�@�߂�l�F�Ȃ�
//
//////////////////////////////////////////////////////////
void C_SceneBase::ChangeScene(DWORD nextID)
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
bool C_SceneBase::HitCheck(D3DXVECTOR2 centerPos , D3DXVECTOR2 size)
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