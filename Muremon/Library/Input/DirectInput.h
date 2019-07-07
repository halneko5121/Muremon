#pragma once 
/******************************************************************
 *	@file	DirectInput.h
 *	@brief	デバイス操作
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/
#define DIRECTINPUT_VERSION	(0x800)		// DirectInputバージョンの宣言
#define KEY_REVISION		(0x03FFFFF)

#include <dinput.h>

#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )

enum MouseActionType
{
	cMouseActionType_NotAct,
	cMouseActionType_MoveX,
	cMouseActionType_MoveY,
	cMouseActionType_MoveZ,
	cMouseActionType_Button0,
	cMouseActionType_ActButton1,
	cMouseActionType_ActButton2,
	cMouseActionType_ActButton3,
};

// マウスの情報を扱う構造体
struct MouseData
{
	RECT    mImageRect;		// マウス用画像矩形
	bool    mIsDownLButton;	
	bool    mIsDownRButton;	
	bool    mIsDownCButton;	
	bool    mIsPushLButton;	
	bool    mIsPushRButton;	
	bool    mIsPushCButton;	
	bool    mIsReleaseLButton;	
	bool    mIsReleaseRButton;	
	bool    mIsReleaseCButton;	
};

class DirectInputKey
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	DirectInputKey();

	/**
	 * @brief	デストラクタ
	 */
	~DirectInputKey();

	/**
	 * @brief	インスタンスの取得
	 */
	static DirectInputKey*		getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void					create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void					destroy();

	/**
	 * @brief	初期化関数
	 * @param	window_handle    ウィンドウハンドル
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT						init(HWND window_handle);

	/**
	 * @brief	更新
	 */
	void						update();

	/**
	 * @brief	開放処理を行う
	 */
	void						releaseDirectInput();

	/**
	 * @brief	指定のキーの入力判定(押されているかどうか)
	 * @param	key		キーの状態
	 */
	bool						isKeyDown(USHORT key);

	/**
	 * @brief	指定のキーが瞬間的に押されたか
	 * @param	key		キーの状態
	 */
	bool						isKeyPushed(USHORT key);

	/**
	 * @brief	指定のキーが離されたかどうか
	 * @param	key		キーの状態
	 */
	bool						isKeyReleased(USHORT key);

	/**
	 * @brief	いずれかのキーが押されたか
	 */
	bool						isAnyKeyDown();
	bool						isAnyKeyPushed();


private:
	enum { MAX_KEYDATA = 256 };								// 一度に受け付けるキーの最大数

private:
	/**
	 * @brief	デバイス全体の情報更新
	 */
	void						KeyBordRefresh();

private:
	static DirectInputKey*		mInstance;						// インスタンス
	LPDIRECTINPUT8				mDirectInput;					// DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8		mKeyBordDevice;					// DirectInputDeviceオブジェクト(キーボード)

	HWND						mWindowHandle;					// ウィンドウハンドルへのポインタ
	BYTE						mKeyState[MAX_KEYDATA];			// キー情報格納配列
	BYTE						mKeyStatePrev[MAX_KEYDATA];		// キー情報格納配列（1f前）
};

static DirectInputKey* GetInputKey() { return DirectInputKey::getInstance(); }


// マウスからの入力を扱うクラス(仮作成)
class DirectInputMouse
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	DirectInputMouse(const SIZE& size, const POINT& pos, const SIZE& cursor_size);

	/**
	 * @brief	デストラクタ
	 */
	~DirectInputMouse();

	/**
	 * @brief	インスタンスの取得
	 */
	static DirectInputMouse*	getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void					create(const SIZE& size, const POINT& pos, const SIZE& cursor_size);

	/**
	 * @brief	インスタンスの破棄
	 */
	static void					destroy();

	/**
	 * @brief	初期化
	 * @param	window_handle    ウィンドウハンドル
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT						init(HWND window_handle);

	/**
	 * @brief	開放処理を行う
	 */
	void						releaseDirectMouse();

	/**
	 * @brief	マウスの情報更新(カーソル位置)
	 */
	void						update();

	/**
	 * @brief	マウスの動作をチェックする
	 * @return	0~7	各動作を判定し対応する値が返る
	 */
	USHORT						checkMouseAction();

	/**
	 * @brief	現在のマウス情報を取得する
	 */
	MouseData					getMouseData() const;

private:
	/**
	 * @brief	デバイス全体の情報更新(絶対値の場合)仮
	 */
	void						refresh();

	/**
	 * @brief	デバイスの設定(軸モードの設定)
	 * @return	成功 TRUE		失敗 FALSE
	 */
	bool						setProperty();

private:
	static DirectInputMouse*	mInstance;				// インスタンス

	LPDIRECTINPUT8				mDirectInput;				// DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8		mMouseDevice;				// 入力デバイス
	HWND						mWindowHandle;				// ウィンドウハンドルへのポインタ
	DIMOUSESTATE2				mMouseState;				// マウス情報格納
	DIMOUSESTATE2				mMouseStatePrev;			// マウス情報格納（1f前）
	SIZE						mCursorSize;				// マウスカーソルサイズ
	
	// 座標取得用
	LPPOINT						mPosCursorWindow;
	LPPOINT						mPosCursorGame;			
	RECT						mGameSize;
	MouseData					mMouseData;
};

static DirectInputMouse* GetInputMouse() { return DirectInputMouse::getInstance(); }
