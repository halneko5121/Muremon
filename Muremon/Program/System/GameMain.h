#pragma once
/******************************************************************
 *	@file	GameMain.h
  *	@brief	ゲームメイン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Window/Window.h"
#include "Library/StateMachine.h"

class Window;
class SceneBase;
class DirectGraphics;

class GameMain
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	explicit GameMain();

	/**
	 * @brief	デストラクタ
	 */
	virtual ~GameMain();

	/**
	 * @brief	ゲームで使うメンバの初期化
	 */
    void		init();

	/**
     * @brief	メイン関数												
	 * @param	hInstance   インスタンスハンドル(プログラムを動かすためのもの)		
	 * @param	hPrevInst   ↑の前の状態を保存しておく(1つ目に情報が入ってなかった時用)
	 * @param	lpCmdLine	Windowsからの命令が格納される(ポインタの先頭アドレス)
	 * @param	nShowCmd    その命令がいくつあるのか
     * @return  int         メッセージループを返す						
	 */
	int WINAPI	winMain(HINSTANCE hInstance , HINSTANCE hPrevInst , LPSTR lpCmdLine , int nShowCmd);

	/**
	 * @brief	ゲーム内ループ関数
     * @return  メッセージパラメータ
	 */
	int			msgLoop();

	/**
     * @brief ゲームで使うメンバの開放処理
	 */
    void		release();

	/**
	 * @brief シーンの生成
	 */
	SceneBase*	createScene(int scene_id);

private:
	// ステート関数
	DECLAR_STATE_FUNC2(Idle);
	DECLAR_STATE_FUNC2(Init);
	DECLAR_STATE_FUNC2(Run);
	DECLAR_STATE_FUNC2(End);

private:
	StateMachine			mState;			// ステート
	Window*					mWindow;		// ウィンドウクラスへのポインタ
	SceneBase*				mScene;			// シーンクラスへのポインタ
	DirectGraphics*			mGraphics;		// グラフィッククラスへのポインタ
	DWORD					mBackground;
};