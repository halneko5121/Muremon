//---------------------------------------------
//
//      メイン
//      作成開始日:2月16日
//      更新日:2月16日
//      作成者:西井
//
//---------------------------------------------

#include <crtdbg.h> // メモリーリークチェック
#include "main.h"
#include "Program/gManage/GameManage.h"

//////////////////////////////////////////////////////////
//
//      説明　：メイン(ここからプログラムがスタート)
//      引数  ：HINSTANCE   hInstance   インスタンスハンドル
//              HINSTANCE   hPrevInst   ゲームメインに渡す
//              LPSTR       lpCmdLine   ゲームメインに渡す
//              int         nShowCmd    ゲームメインに渡す
//      戻り値：int         ループ
//
//////////////////////////////////////////////////////////
int	WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd)
{
	int l_return = 0;
	C_GameMain gMain;	//インスタンス生成

	l_return = gMain.WinMain(hInstance,hPrevInst,lpCmdLine,nShowCmd);

	_CrtDumpMemoryLeaks();					// 現在のメモリリーク状態がわかる

	return l_return;
}