/******************************************************************
 *	@file	DirectInput.cpp
 *	@brief	デバイス操作
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "DirectInput.h"
#include <strsafe.h>
#include <crtdbg.h>

#define KEY_REVISION		(0x03FFFFF)

DirectInputKey* DirectInputKey::mInstance = nullptr;

namespace
{
	const int cDipDeviceBufferSize = 100;
	const int cBarX = 5;
	const int cBarY = 30;
}

/**
 * @brief	コンストラクタ
 */
DirectInputKey::DirectInputKey(void)
	: mDirectInput(nullptr)
	, mKeyBordDevice(nullptr)
	, mWindowHandle(nullptr)
{
	ZeroMemory(&mKeyStatePrev,	MAX_KEYDATA);
	ZeroMemory(&mKeyState,		MAX_KEYDATA);
}

/**
 * @brief	デストラクタ
 */
DirectInputKey::~DirectInputKey()
{
}

/**
 * @brief	インスタンスの取得
 */
DirectInputKey*
DirectInputKey::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
DirectInputKey::create()
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new DirectInputKey();
}

/**
 * @brief	インスタンスの破棄
 */
void
DirectInputKey::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	初期化関数
 * @param	window_handle    ウィンドウハンドル
 * @return	S_OK:成功   E_FAIL:失敗
 */
HRESULT
DirectInputKey::init(HWND window_handle)
{
	// DirectInputオブジェクトの作成
	if (FAILED(DirectInput8Create(
		GetModuleHandle(NULL),			// アプリのインスタンスハンドル
		DIRECTINPUT_VERSION,			// 使用するDirectInputのversion番号。通常はDIRECTINPUT_VERSION
		IID_IDirectInput8,				// 目的のインターフェースの識別子『IID_IDirectInput8』を渡す
		(void**)&mDirectInput,			// インターフェースポインタを受け取る変数のポインタ
		NULL)))							// 通常『NULL』を渡す
	{
		MessageBox(NULL, TEXT("DirectInputオブジェクトの作成に失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// キーボード初期化
	// KeyBordDeviceの取得
	if (FAILED(mDirectInput->CreateDevice(
		GUID_SysKeyboard,				// 入力デバイスを指定するDUID デフォルトのシステムキーボード
		&mKeyBordDevice,				// Inputデバイスを受け取る変数のポインタ
		NULL)))							// 通常『NULL』を渡す
	{
		MessageBox(NULL, TEXT("KeyBordDeviceの取得失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// データフォーマットの設定(設定は一度でおｋ)
	if (FAILED(mKeyBordDevice->SetDataFormat(
		&c_dfDIKeyboard))) // キーボード用データフォーマット
	{
		MessageBox(NULL, TEXT("KeyBordDeviceの設定失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// デバイスの協調モードの設定(デバイスとシステム間の関係を設定)
	if (FAILED(mKeyBordDevice->SetCooperativeLevel(
		window_handle,										// ウィンドウハンドル
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))	// 『強調レベル』を表すフラグ
	{
		MessageBox(NULL, TEXT("KeyBordモードの変換失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// アクセス権取得(アクセス権を取得して初めて入力できる)
	mKeyBordDevice->Acquire();

	mWindowHandle = window_handle;

	return S_OK;
}

void
DirectInputKey::update()
{
	keyBordRefresh();
}

/**
 * @brief	開放処理
 */
void
DirectInputKey::release()
{
	// デバイスへのアクセス権を解放する
	if(mKeyBordDevice)
	{
		mKeyBordDevice->Unacquire();
	}

	// 開放
	APP_SAFE_RELEASE(mDirectInput);
	APP_SAFE_RELEASE(mKeyBordDevice);
}

/**
 * @brief	指定のキーの入力判定(押されているかどうか)
 * @param	key		キーの状態
 * @return	true	押されている   false:　押されていない
 */
bool
DirectInputKey::isKeyDown(USHORT key) const
{
	if(!mKeyBordDevice) return FALSE;

	// 最上位１ビットに「押されているか」どうかのデータが格納されている
	if (mKeyState[key] & 0x80)
	{
		return TRUE;
	}

	return FALSE;
}

/**
 * @brief	指定のキーが瞬間的に押されたか
 * @param	key		キーの状態
 * @return	true	押された   false:　押されていない
 */
bool
DirectInputKey::isKeyPushed(USHORT key) const
{
	// 現在押されていて かつ 直前に押されていない時TRUE
	if( isKeyDown(key) && !(mKeyStatePrev[key] & 0x80) ) return TRUE;

	return FALSE;
}

/**
 * @brief	指定のキーが離されたかどうか
 * @param	key		キーの状態
 * @return	true	離された   false:　離されていない
 */
bool
DirectInputKey::isKeyReleased(USHORT key) const
{
	// 現在押されておらず かつ 直前に押されている時TRUE
	if( !(isKeyDown(key)) && (mKeyStatePrev[key] & 0x80) ) return TRUE;

	return FALSE;
}

/**
 * @brief	いずれかのキーが押されたか
 * @return	true　押された   false:　押されていない
 */
bool
DirectInputKey::isAnyKeyDown() const
{
	for(int i = 0;i < MAX_KEYDATA;i++){
		if(isKeyDown(i)) return TRUE;
	}

	return FALSE;
}

/**
 * @brief	いずれかのキーが瞬間的に押されたか
 * @return	true　押された   false:　押されていない
 */
bool
DirectInputKey::isAnyKeyPushed() const
{
	for (int i = 0;i < MAX_KEYDATA;i++) {
		if (isKeyPushed(i)) return TRUE;
	}

	return FALSE;
}

/**
 * @brief	デバイス全体の情報更新
 */
void
DirectInputKey::keyBordRefresh()
{
	static HRESULT h_result;

	if(mKeyBordDevice)
	{
		// 入力したデバイスへのアクセス権を取得
		h_result = mKeyBordDevice->Acquire();
		
		// データを保存
		memcpy(mKeyStatePrev, mKeyState, MAX_KEYDATA);

		ZeroMemory(&mKeyState, MAX_KEYDATA);

		// データあれば
		if ((h_result == DI_OK) || (h_result == S_FALSE))
		{
			// デバイスの状態を取得
			mKeyBordDevice->GetDeviceState(
				sizeof(mKeyState),		// 指定したキーボードのサイズ
				(LPVOID)&mKeyState);	// 現在の状態を受け取る構造体・変数のアドレス
		}
	}

	// データがなければ
	if(FAILED(h_result))
	{
		// デバイスへのアクセス権を取得
		mKeyBordDevice->Acquire();
		// キー状態を初期化
		ZeroMemory(mKeyState, MAX_KEYDATA);
	}
}


//////////////////////////////////////////////////////////////////////////////////////
//		↓マウスの処理
//////////////////////////////////////////////////////////////////////////////////////

DirectInputMouse*	DirectInputMouse::mInstance = nullptr;

/**
 * @brief	コンストラクタ
 */
DirectInputMouse::DirectInputMouse(const SIZE& size, const POINT& pos, const SIZE& cursor_size)
{
	// DirectInputDeviceオブジェクト(マウス)
	mDirectInput		= nullptr;
	mMouseDevice		= nullptr;
	mPosCursorWindow	= new POINT();
	mPosCursorGame		= new POINT();
	mCursorSize			= cursor_size;

	ZeroMemory(&mMouseState, sizeof(DIMOUSESTATE2));
	ZeroMemory(&mMouseStatePrev, sizeof(DIMOUSESTATE2));

	SetRect(&mGameSize, 0, 0, size.cx, size.cy);
	SetCursorPos( (pos.x + cBarX),(pos.y + cBarY) );

	mMouseData.mIsDownCButton = mMouseData.mIsPushCButton = mMouseData.mIsReleaseCButton = false;
	mMouseData.mIsDownLButton = mMouseData.mIsPushLButton = mMouseData.mIsReleaseLButton = false;
	mMouseData.mIsDownRButton = mMouseData.mIsPushRButton = mMouseData.mIsReleaseRButton = false;
}

/**
 * @brief	デストラクタ
 */
DirectInputMouse::~DirectInputMouse()
{
}

/**
 * @brief	インスタンスの取得
 */
DirectInputMouse*
DirectInputMouse::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
DirectInputMouse::create(const SIZE& size, const POINT& pos, const SIZE& cursor_size)
{
	APP_ASSERT_MESSAGE(mInstance == nullptr, "既に生成済みです");
	mInstance = new DirectInputMouse(size, pos, cursor_size);
}

/**
 * @brief	インスタンスの破棄
 */
void
DirectInputMouse::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	初期化
 * @param	window_handle    ウィンドウハンドル
 * @return	S_OK:成功   E_FAIL:失敗
 */
HRESULT
DirectInputMouse::init(HWND window_handle)
{
	// DirectInputオブジェクトの作成
	if (FAILED(DirectInput8Create(
		GetModuleHandle(NULL),					// アプリのインスタンスハンドル
		DIRECTINPUT_VERSION,					// 使用するDirectInputのversion番号。通常はDIRECTINPUT_VERSION
		IID_IDirectInput8,						// 目的のインターフェースの識別子『IID_IDirectInput8』を渡す
		(void**)&mDirectInput,					// インターフェースポインタを受け取る変数のポインタ
		NULL)))									// 通常『NULL』を渡す
	{
		MessageBox(NULL, TEXT("DirectInputオブジェクトの作成に失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// MouseDeviceの取得
	if (FAILED(mDirectInput->CreateDevice(
		GUID_SysMouse,							// 入力デバイスを指定するDUID デフォルトのシステムマウス
		&mMouseDevice,							// Inputデバイスを受け取る変数のポインタ
		NULL)))									// 通常『NULL』を渡す
	{
		MessageBox(NULL, TEXT("MouseDeviceの取得失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// データフォーマットの設定(設定は一度でおｋ)
	if (FAILED(mMouseDevice->SetDataFormat(
		&c_dfDIMouse2)))		// マウス用データフォーマット
	{
		MessageBox(NULL, TEXT("MouseDeviceの設定失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// デバイスの協調モードの設定(デバイスとシステム間の関係を設定)
	if (FAILED(mMouseDevice->SetCooperativeLevel(
		window_handle,								// ウィンドウハンドル
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))	// 『強調レベル』を表すフラグ
	{
		MessageBox(NULL, TEXT("Mouseモードの変換失敗"), NULL, MB_OK);
		return E_FAIL;
	}

	// 軸モードを設定
	if (!setProperty()) {
		E_FAIL;
	}

	// アクセス権取得(アクセス権を取得して初めて入力できる)
	mMouseDevice->Acquire();

	mWindowHandle = window_handle;

	return S_OK;
}

/**
 * @brief	開放処理を行う
 */
void
DirectInputMouse::release()
{
	// デバイスへのアクセス権を解放する
	if(mMouseDevice)
	{
		mMouseDevice->Unacquire();
	}

	// 開放
	APP_SAFE_DELETE(mPosCursorGame);
	APP_SAFE_DELETE(mPosCursorWindow);
	APP_SAFE_RELEASE(mDirectInput);
	APP_SAFE_RELEASE(mMouseDevice);
}

/**
 * @brief	デバイス全体の情報更新(絶対値の場合)仮
 */
void
DirectInputMouse::refresh()
{
	if(mMouseDevice == NULL){ return; }					// マウスがない場合は何もせず終わる
			
	mMouseDevice->Acquire();							// 入力の受付開始

	mMouseStatePrev = mMouseState;						// 前回のデータを保持

	ZeroMemory(&mMouseState, sizeof(DIMOUSESTATE2));	// キーバッファの初期化

	// データを取得
	mMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mMouseState);

	update();										// 情報更新(カーソル位置)
}

/**
 * @brief	マウスの情報更新(カーソル位置)
 */
void
DirectInputMouse::update()
{
	GetCursorPos(mPosCursorWindow);					// 取得(スクリーン座標)
	mPosCursorGame = mPosCursorWindow;				// ゲーム用に渡す
	ScreenToClient(mWindowHandle,mPosCursorGame);	// スクリーン座標をクライアント座標に変換

	SetRect(&mMouseData.mImageRect, mPosCursorWindow->x, mPosCursorWindow->y,
		(mPosCursorWindow->x + mCursorSize.cx), (mPosCursorWindow->y + mCursorSize.cy));

#ifdef _WINDOW_MODE_
	// ゲーム画面外へ行かせない(Game用カーソルなどある場合に有効か？)
	if (mMouseData.mImageRect.left		< mGameSize.left)	mMouseData.mImageRect.left		= mGameSize.left;
	if (mMouseData.mImageRect.top		< mGameSize.top)	mMouseData.mImageRect.top		= mGameSize.top;
	if (mMouseData.mImageRect.right		> mGameSize.right)	mMouseData.mImageRect.right		= mGameSize.right;
	if (mMouseData.mImageRect.bottom	> mGameSize.bottom)	mMouseData.mImageRect.bottom	= mGameSize.bottom; 
#else
	//フルスクリーンなら気にしなくてよい
#endif

	// マウスの各ボタンが押されているか調べる
	mMouseData.mIsDownLButton = (mMouseState.rgbButtons[0] & 0x80) ? true : false;
    mMouseData.mIsDownRButton = (mMouseState.rgbButtons[1] & 0x80) ? true : false;
    mMouseData.mIsDownCButton = (mMouseState.rgbButtons[2] & 0x80) ? true : false;
    
	// マウスの各ボタンが瞬間に押されたか調べる
	mMouseData.mIsPushLButton = ( (mMouseState.rgbButtons[0] & 0x80) &&  !(mMouseStatePrev.rgbButtons[0] & 0x80) ) ? true : false;
	mMouseData.mIsPushRButton = ( (mMouseState.rgbButtons[1] & 0x80) &&  !(mMouseStatePrev.rgbButtons[1] & 0x80) ) ? true : false;
    mMouseData.mIsPushCButton = ( (mMouseState.rgbButtons[2] & 0x80) &&  !(mMouseStatePrev.rgbButtons[2] & 0x80) ) ? true : false;

	// マウスの各ボタンが離されたか調べる
	mMouseData.mIsReleaseLButton = ( !(mMouseState.rgbButtons[0] & 0x80) &&  (mMouseStatePrev.rgbButtons[0] & 0x80) ) ? true : false;
	mMouseData.mIsReleaseRButton = ( !(mMouseState.rgbButtons[1] & 0x80) &&  (mMouseStatePrev.rgbButtons[1] & 0x80) ) ? true : false;
	mMouseData.mIsReleaseCButton = ( !(mMouseState.rgbButtons[2] & 0x80) &&  (mMouseStatePrev.rgbButtons[2] & 0x80) ) ? true : false;
}

/**
 * @brief	マウスの動作をチェックする
 * @return	0~7	各動作を判定し対応する値が返る
 */
USHORT
DirectInputMouse::checkMouseAction()
{
	HRESULT h_result;

	// バッファリング・データを取得する
	while (true)
	{
		DIDEVICEOBJECTDATA	od;
		DWORD				dwItems = 1;

		// デバイスの取得
		h_result = mMouseDevice->GetDeviceData(
			sizeof(DIDEVICEOBJECTDATA), &od, &dwItems, 0);

		if (h_result == DIERR_INPUTLOST)
		{
			mMouseDevice->Acquire();
		}
		// データが読めないか、存在しない
		else if (FAILED(h_result) || (dwItems == NULL))
		{
			break;
		}
		else
		{
			switch (od.dwOfs) {
			case DIMOFS_X:
				return cMouseActionType_MoveX;		// マウスの水平動作
			case DIMOFS_Y:
				return cMouseActionType_MoveY;		// マウスの垂直動作
			case DIMOFS_Z:
				return cMouseActionType_MoveZ;		// マウスのz(ホイール)動作
			case DIMOFS_BUTTON0:
				return cMouseActionType_Button0;	// 右ボタンが押された、または離された
			case DIMOFS_BUTTON1:
				return cMouseActionType_ActButton1;	// 左ボタンが押された、または離された
			case DIMOFS_BUTTON2:
				return cMouseActionType_ActButton2;	// 中ボタンが押された、または離された
			case DIMOFS_BUTTON3:
				return cMouseActionType_ActButton3;	// ４ボタンが押された、または離された。
			default:
				break;
			}
		}
	}

	return cMouseActionType_NotAct;
}

/**
 * @brief	現在のマウス情報を取得する
 */
MouseData
DirectInputMouse::getMouseData() const
{
	return mMouseData; 
}

/**
 * @brief	デバイスの設定(軸モードの設定)
 * @return	成功 TRUE		失敗 FALSE
 */
bool
DirectInputMouse::setProperty()
{
	DIPROPDWORD diprop;

	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	//	diprop.dwData			 = DIPROPAXISMODE_REL;	// 相対値モード
	diprop.dwData = DIPROPAXISMODE_ABS;	// 絶対値モード

	if (FAILED(mMouseDevice->SetProperty(
		DIPROP_AXISMODE,							// 設定するプロパティを識別するGUID『軸モード』に設定
		&diprop.diph)))								// 構造体のアドレス
	{
		MessageBox(NULL, TEXT("軸モードの設定に失敗しました"), NULL, MB_OK);
		return FALSE;
	}

	// 相対値モードが指定されていたらバッファリング・データを取得するため、バッファ・サイズを設定
	if (diprop.dwData)
	{
		diprop.dwData = cDipDeviceBufferSize;
		if (FAILED(mMouseDevice->SetProperty(
			DIPROP_BUFFERSIZE,
			&diprop.diph)))
		{
			MessageBox(NULL, TEXT("バッファ・サイズの設定に失敗"), NULL, MB_OK);
			return FALSE;
		}
	}

	return TRUE;
}