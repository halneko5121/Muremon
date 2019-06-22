//---------------------------------------------
//
//      ウィンドウ作成
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

#ifndef _WINDOW_H_
#define _WINDOW_H_

//include
#include <windows.h>
#include <time.h>
#include <stdlib.h>
//#include "..\\resource.h"
//#include "DirectGraphics.h"

//define
#define WINDOW_MODE			(true)						//true:ウィンドウ	false:フルスクリーン
#define FULL_MODE			(false)
#define WINDOW_WIDTH		(800)						//ウィンドウサイズ(横)
#define WINDOW_HEIGHT		(600)						//ウィンドウサイズ(縦)
#define WINDOW_STYLE_W		(WS_OVERLAPPEDWINDOW)		//ウィンドウモード
#define WINDOW_STYLE_F		(WS_POPUP | WS_VISIBLE)		//フルスクリーンモード
#define CLASS_NAME			TEXT("My Class")			//クラスネーム
#define WINDOW_NAME			TEXT("むれもん")			//ウィンドウネーム

//class
class C_Window
{
private:
	HINSTANCE	hInstance;		//インスタンスハンドル
	HWND		hWnd;			//ウィンドウハンドル
	RECT		windowSize;		//ウィンドウサイズ
	bool		windowMode;		//ウィンドウモード
public:
	//////////////////////////////////////////////////////////
    //
    //      説明　：ウィンドウ初期化
    //      引数  ：HINSTANCE   hInst   インスタンスハンドル
    //      戻り値：HRESULT S_OK:成功   E_FAIL:失敗
    //
    //////////////////////////////////////////////////////////
	HRESULT InitWindow(HINSTANCE hInst);

	//////////////////////////////////////////////////////////
    //
    //      説明　：ウィンドウ生成
    //      引数  ：なし
    //      戻り値：bool    true:成功   false:失敗
    //
    //////////////////////////////////////////////////////////
	bool WindowCreate(void);

	//////////////////////////////////////////////////////////
    //
    //      説明　：ウィンドウクラス独自のウィンドウプロシージャ
    //      引数  ：HWND    hWnd    ウィンドウハンドル
    //              UINT    uMsg    メッセージ
    //              WPARAM  wParam  パラメータ
    //              LPARAM  lParam  パラメータ
    //      戻り値：LRESULT ウィンドウプロシージャに渡す
    //
    //////////////////////////////////////////////////////////
	static LRESULT CALLBACK WindowProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam);
	
    //////////////////////////////////////////////////////////
    //
    //      説明　：共通のウィンドウプロシージャ
    //      引数  ：HWND    hWnd    ウィンドウハンドル
    //              UINT    uMsg    メッセージ
    //              WPARAM  wParam  パラメータ
    //              LPARAM  lParam  パラメータ
    //      戻り値：LRESULT ウィンドウ初期化時に渡す
    //
    //////////////////////////////////////////////////////////
	LRESULT WndProc(HWND hWnd , UINT iMsg , WPARAM wParam , LPARAM lParam);

	//-情報取得関数-

	//////////////////////////////////////////////////////////
    //
    //      説明　：インスタンスハンドル取得
    //      引数  ：なし
    //      戻り値：HINSTANCE   インスタンスハンドル
    //
    //////////////////////////////////////////////////////////
	HINSTANCE GetHinst(void)	{return hInstance;}

	//////////////////////////////////////////////////////////
    //
    //      説明　：ウィンドウハンドル取得
    //      引数  ：なし
    //      戻り値：HWND   ウィンドウハンドル
    //
    //////////////////////////////////////////////////////////
	HWND GetHwnd(void)			{return hWnd;}

	//////////////////////////////////////////////////////////
    //
    //      説明　：ウィンドウサイズ取得
    //      引数  ：なし
    //      戻り値：RECT    ウィンドウのサイズ
    //
    //////////////////////////////////////////////////////////
	RECT GetWindowSize(void)	{return windowSize;}

	//////////////////////////////////////////////////////////
    //
    //      説明　：ウィンドウモード取得
    //      引数  ：なし
    //      戻り値：bool    true:ウィンドウモード   false:フルスクリーン
    //
    //////////////////////////////////////////////////////////
	bool GetWindowMode(void)	{return windowMode;}
};

#endif	//_WINDOW_H_