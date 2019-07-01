//---------------------------------------------
//
//      デバイス操作
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
	LPDIRECTINPUT8			pDinput;			// DirectInputオブジェクト
	HWND                    hWind;				// ウィンドウハンドルへのポインタ

	LPDIRECTINPUTDEVICE8	pDKeyBordDevice;	// DirectInputDeviceオブジェクト(キーボード)
	BYTE					key_state[256];		// キー情報格納配列
	KEY_DATA				keybord_data;		// キーの状態を格納

public:
	/**
	 * @brief コンストラクタ
	 */
	C_DInput(void);

	/**
	 * @brief	初期化
	 * @param	hWnd		ウィンドウハンドル
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT InitDInput(HWND hWnd);

	/**
	 * @brief	デバイス全体の情報更新
	 */
	void RefreshInput(void);

	/**
	 * @brief	開放処理
	 */
	void ReleaseDInput(void);

	//-情報取得関数-

	/**
	 * @brief	キーボードデバイスの初期化
	 * @param	hWnd		ウィンドウハンドル
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT InitKeyBoard(HWND hWnd);

	/**
	 * @brief	キーボードの情報更新
	 */
	void KeyBordRefresh();

	/**
	 * @brief	キーボードのキーに制限をかける
	 */
	void LimitKeyBoard(void);

	/**
	 * @brief	キーボードチェック
	 * @param	a_KeyData	キーデータ
	 * @param	a_key_state	キーの状態
	 * @return	押されているか
	 */
	bool CheckKeyBord(unsigned short a_KeyData, KEY_STATE a_key_state);

	/**
	 * @brief	キーボードデータを更新
	 */
	void KeyBordDataRefresh();

	~C_DInput(void);
};

#endif	//_DIRECTINPUT_H_