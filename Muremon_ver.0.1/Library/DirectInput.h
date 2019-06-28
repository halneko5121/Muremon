//---------------------------------------------
//
//      デバイス操作
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

#ifndef _DIRECTINPUT_H_
#define _DIRECTINPUT_H_

//define
#define DIRECTINPUT_VERSION	(0x800)		//ヴァージョン宣言
#define KEY_REVISION		(0x03FFFFF)

//include
#include <dinput.h>
#include "Library/DirectGraphics.h"
#include "Program/gManage/Window.h"
#include "Program/Define.h"

//lib
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

//#define SAFE_RELEASE(p) {if(p) { (p)->Release(); (p) = NULL; } }

//共通の設定
enum KEY_STATE	//キーの状態
{
	KEY_PUSH,
	KEY_HOLD,
	KEY_RELEASE,
	KEY_FREE,
};

//struct
typedef struct	//キーのデータ構造体
{
	short on;		//今回のデータ
	short press;	//押された瞬間のデータ
	short release;	//離された瞬間のデータ
	short old;
}KEY_DATA;

class C_DInput
{
private:
	LPDIRECTINPUT8			pDinput;					//DirectInputオブジェクト
	HWND                    hWind;						//ウィンドウハンドルへのポインタ

	LPDIRECTINPUTDEVICE8	pDKeyBordDevice;	//DirectInputDeviceオブジェクト(キーボード)
	BYTE					key_state[256];		//キー情報格納配列
	KEY_DATA				keybord_data;		//キーの状態を格納
public:
	//////////////////////////////////////////////////////////
    //
    //      説明　：コンストラクタ
    //
    //////////////////////////////////////////////////////////
	C_DInput(void);

	//////////////////////////////////////////////////////////
    //
    //      説明　：初期化関数
    //      引数  ：HWND    hWnd    ウィンドウハンドル
    //      戻り値：HRESULT S_OK:成功   E_FAIL:失敗
    //
    //////////////////////////////////////////////////////////
	HRESULT InitDInput(HWND hWnd);

	//////////////////////////////////////////////////////////
    //
    //      説明　：デバイス全体の情報更新
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void RefreshInput(void);

	//////////////////////////////////////////////////////////
    //
    //      説明　：開放処理を行う
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void ReleaseDInput(void);

	//-情報取得関数-

	//////////////////////////////////////////////////////////
    //
    //      説明　：キーボードデバイスの初期化
    //      引数  ：HWND    hWnd    ウィンドウハンドル
    //      戻り値：HRESULT S_OK:成功   E_FAIL:失敗
    //
    //////////////////////////////////////////////////////////

	HRESULT InitKeyBoard(HWND hWnd);

	//////////////////////////////////////////////////////////
    //
    //      説明　：キーボードの情報更新
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void KeyBordRefresh();

	//////////////////////////////////////////////////////////
    //
    //      説明　：キーボードのキーの制限をかける
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void LimitKeyBoard(void);

	//////////////////////////////////////////////////////////
    //
    //      説明　：キーボードデータチェック
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	bool GetKeyBoardData(unsigned short a_key);

	//////////////////////////////////////////////////////////
    //
    //      説明　：キーボードチェック
    //      引数  ：キーデータ、キーの状態
    //      戻り値：押されているか
    //
    //////////////////////////////////////////////////////////
	bool CheckKeyBord(unsigned short a_KeyData, KEY_STATE a_key_state);

	//////////////////////////////////////////////////////////
    //
    //      説明　：キーボードデータを更新
    //      引数  ：なし
    //      戻り値：なし
    //
    //////////////////////////////////////////////////////////
	void KeyBordDataRefresh();

	~C_DInput(void);
};

#endif	//_DIRECTINPUT_H_