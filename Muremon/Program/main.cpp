/******************************************************************
 *	@file	main.cpp
 *	@brief	メイン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "main.h"
#include "System/GameMain.h"

/**
 * @brief	メイン(ここからプログラムがスタート)
 * @param	hInstance   インスタンスハンドル(プログラムを動かすためのもの)
 * @param	hPrevInst	↑の前の状態を保存しておく	(1つ目に情報が入ってなかった時用)
 * @param	lpCmdLine   Windowsからの命令が格納される(ポインタの先頭アドレス)
 * @param	nShowCmd	その命令がいくつあるのか
 * @return	ループ
 * @note	WINAPI		ウィンドウアプリケーションですよとわからせるためのもの
 * @note	WinMain		これがないとWindowsアプリケーションの始まりがわからない
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	// インスタンス生成
	GameMain game_main;

	int l_return = game_main.winMain(hInstance,hPrevInst,lpCmdLine,nShowCmd);

	// 現在のメモリリーク状態がわかる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return l_return;
}