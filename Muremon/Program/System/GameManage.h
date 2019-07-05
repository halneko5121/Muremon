#pragma once
/******************************************************************
 *	@file	GameManage.h
 *	@brief	ゲーム全体の管理を行う	
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Window/Window.h"

class C_Window;
class SceneBase;
class DirectInputKey;
class DirectInputMouse;
class DirectGraphics;
class C_Sprite;
class DirectFont;
class C_DWaveSound;
class C_DOggSound;
namespace Dix {
	class C_PCMPlayer;
}

class C_GameMain
{
public:
	/**
	 * @brief	ゲームで使うメンバの初期化
	 */
    void InitGameMain();

	/**
     * @brief	メイン関数												
	 * @param	hInstance   インスタンスハンドル(プログラムを動かすためのもの)		
	 * @param	hPrevInst   ↑の前の状態を保存しておく(1つ目に情報が入ってなかった時用)
	 * @param	lpCmdLine	Windowsからの命令が格納される(ポインタの先頭アドレス)
	 * @param	nShowCmd    その命令がいくつあるのか
     * @return  int         メッセージループを返す						
	 */
	int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd);

	/**
	 * @brief	ゲーム内ループ関数
     * @return  メッセージパラメータ
	 */
	int MsgLoop();

	/**
     * @brief ゲームで使うメンバの開放処理
	 */
    void ReleaseGameMain();

	/**
     * @brief シーケンスの管理を行う
	 */
	void ControlSequence();

private:
	C_Window*			mWindow;		// ウィンドウクラスへのポインタ
	SceneBase*		mScene;			// シーンクラスへのポインタ
	DirectGraphics*		mGraphics;		// グラフィッククラスへのポインタ
	char**				mSoundText;
	DWORD				mBackground;
	int					mScore;
};