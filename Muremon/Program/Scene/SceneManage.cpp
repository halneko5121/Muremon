//---------------------------------------------
//
//      シーンの管理を行う
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

#include "SceneManage.h"
#include "Library/Sound/DirectSound.h"

//////////////////////////////////////////////////////////
//
//      説明　：コンストラクタ
//
//////////////////////////////////////////////////////////
C_SceneManage::C_SceneManage()
{
    sceneID = LOGO;    //初期化
}

//////////////////////////////////////////////////////////
//
//      説明　：デストラクタ(仮想関数、何もしない)
//
//////////////////////////////////////////////////////////
C_SceneManage::~C_SceneManage()
{

}

//////////////////////////////////////////////////////////
//
//      説明　：シーンの初期化処理(メンバ初期化)
//      引数　：LPDIRECT3DDEVICE9   pDev    デバイス
//              DInput              *pInput インプットクラスへのポインタ
//              DFont               *pFont  フォントクラスへのポインタ
//　　　戻り値：なし
//
//////////////////////////////////////////////////////////

void C_SceneManage::InitScene(LPDIRECT3DDEVICE9 apDev , C_DFont* apFont, int score)
{
	pDevice = apDev;	//デバイスセット
    pFont   = apFont;   //文字表示可能にする
}

//////////////////////////////////////////////////////////
//
//      説明　：シーンの変更を行う
//      引数　：DWORD   nextID  次のシーンの番号
//　　　戻り値：なし
//
//////////////////////////////////////////////////////////
void C_SceneManage::ChangeScene(DWORD nextID)
{
    sceneID = nextID;   //次のシーン番号を渡す
}

//////////////////////////////////////////////////////////
//
//      説明　：当たり判定を行う
//      引数　：D3DXVECTOR2 centerPos   当たりをとる物体の中心座標
//              D3DXVECTOR2 size        当たりをとる物体のサイズ
//              DInput      *pInput     インプットクラスへのポインタ
//　　　戻り値：なし
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
    //        return true;    //範囲内に入っていれば当たっている
    //    }
    //}
    return false;   //普段は当たっていないのでfalse
}