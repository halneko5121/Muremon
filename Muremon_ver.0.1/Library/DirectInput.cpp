//---------------------------------------------
//
//      デバイス操作
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

//include
#include "DirectInput.h"

//////////////////////////////////////////////////////////
//
//      説明　：コンストラクタ
//
//////////////////////////////////////////////////////////
C_DInput::C_DInput(void)
{
	pDKeyBordDevice = NULL;	//DirectInputDeviceオブジェクト(キーボード)
	ZeroMemory(&keybord_data, sizeof(keybord_data));
	ZeroMemory(&key_state, sizeof(key_state));
}

//////////////////////////////////////////////////////////
//
//      説明　：初期化関数
//      引数  ：HWND    hWnd    ウィンドウハンドル
//      戻り値：HRESULT S_OK:成功   E_FAIL:失敗
//
//////////////////////////////////////////////////////////
HRESULT C_DInput::InitDInput(HWND hWnd)
{
	//DirectInputオブジェクトの作成
	if(FAILED(DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&pDinput,NULL)))
	{
		MessageBox(NULL,TEXT("DirectInputオブジェクトの作成に失敗"),NULL,MB_OK);
		return E_FAIL;
	}

	//キーボード初期化
	if(FAILED(InitKeyBoard(hWnd)))
	{
		MessageBox(NULL,TEXT("キーボードの初期化に失敗"),NULL,MB_OK);
		return E_FAIL;
	}

    hWind = hWnd;

	return S_OK;
}

//////////////////////////////////////////////////////////
//
//      説明　：デバイス全体の情報更新
//      引数  ：なし
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_DInput::RefreshInput(void)
{
	this->KeyBordDataRefresh();
}

//////////////////////////////////////////////////////////
//
//      説明　：開放処理を行う
//      引数  ：なし
//      戻り値：なし
//
//////////////////////////////////////////////////////////
void C_DInput::ReleaseDInput(void)
{
	if(pDKeyBordDevice)
	{
		//デバイスへのアクセス権を解放する
		pDKeyBordDevice->Unacquire();
		//Inputデバイス開放
		//SAFE_RELEASE(pDKeyBordDevice);
	}

    /*delete point;*/
	//開放
	pDKeyBordDevice->Release();
}




HRESULT C_DInput::InitKeyBoard(HWND hWnd)
{
	//KeyBordDevice取得
	if(FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pDKeyBordDevice, NULL)))
	{
		MessageBox(NULL, TEXT("KeyBordDeviceの取得失敗"), TEXT("keyBordDevice"), MB_OK);
		return E_FAIL;
	}

	//KeyBordDevice設定
	if(FAILED(pDKeyBordDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(NULL, TEXT("KeyBordDeviceの設定失敗"), TEXT("keyBordDevice"), MB_OK);
		return E_FAIL;
	}

	//デバイス（キーボード）の協調処理
	if(FAILED(pDKeyBordDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MessageBox(NULL, TEXT("KeyBordモードの変換失敗"), TEXT("keyBordDevice"), MB_OK);
		return E_FAIL;
	}

	//アクセス権取得
	pDKeyBordDevice->Acquire();

	//取得成功したら
	return S_OK;
}

void C_DInput::KeyBordRefresh()
{
	HRESULT hr;

	if(pDKeyBordDevice)
	{
		//入力したデバイスへのアクセス権を取得
		hr = pDKeyBordDevice->Acquire();

		//データあれば
		if((hr == DI_OK) || (hr == S_FALSE))
		{
			//デバイスの状態を取得
			pDKeyBordDevice->GetDeviceState(sizeof(key_state), key_state);
		}
		//データがなければ
		if(FAILED(hr))
		{
			//デバイスへのアクセス権を取得
			pDKeyBordDevice->Acquire();
			//キー状態を初期化
			ZeroMemory(key_state, 256);
		}
	}
}

bool C_DInput::CheckKeyBord(unsigned short a_KeyData, KEY_STATE a_key_state)
{
	unsigned short KeyState = 0;	//キー状態格納

	switch(a_key_state)
	{
	case KEY_PUSH:
		KeyState = keybord_data.on;
		break;
	case KEY_HOLD:
		KeyState = keybord_data.press;
		break;
	case KEY_RELEASE:
		KeyState = keybord_data.release;
		break;
	case KEY_FREE:
		KeyState = keybord_data.old;
		break;
	}
	return ((KeyState & KEY_REVISION) & a_KeyData) != 0;
}

bool C_DInput::GetKeyBoardData(unsigned short a_key)
{
	if(key_state[a_key] & 0x80)
	{
		return true;
	}
	return false;
}

void C_DInput::LimitKeyBoard()
{
	unsigned short key = 0;	//今のキーの状態

	static unsigned short oldKeyState;	//1つ前のキーの状態

	//for(int i = KEY_1;i <= KEY_SEMICOLON;i++){
	//	if(GetKeyBoardData(DIK_0 + i))	{ key = KEY_1 + i; }	//押されたキー情報をいれる
	//}

	//if(GetKeyBoardData(DIK_UP))		{ key |= KEY_UP;	}				//上キー
	//if(GetKeyBoardData(DIK_DOWN))	{ key |= KEY_DOWN;	}				//下キー
	//if(GetKeyBoardData(DIK_LEFT))	{ key |= KEY_LEFT;	}				//左キー
	//if(GetKeyBoardData(DIK_RIGHT))	{ key |= KEY_RIGHT;	}				//右キー
	//if(GetKeyBoardData(DIK_Z))		{ key |= KEY_Z;		}				//Zキー
	//if(GetKeyBoardData(DIK_X))		{ key |= KEY_X;		}				//Xキー
	//if(GetKeyBoardData(DIK_C))		{ key |= KEY_C;		}				//Cキー
	//if(GetKeyBoardData(DIK_V))		{ key |= KEY_V;		}				//Vキー
	//if(GetKeyBoardData(DIK_A))		{ key |= KEY_A;		}				//Aキー
	//if(GetKeyBoardData(DIK_S))		{ key |= KEY_S;		}				//Sキー
	//if(GetKeyBoardData(DIK_R))		{ key |= KEY_R;		}				//Rキー
	//if(GetKeyBoardData(DIK_T))		{ key |= KEY_T;		}				//Tキー

	//キーが押された時
	keybord_data.on	= key & (~oldKeyState);

	//キーが押され続けている時
	keybord_data.press	= (key & oldKeyState) | keybord_data.on;

	//キーが離された時
	keybord_data.release = (oldKeyState & (~key));

	//キーが離され続けている時
	keybord_data.old	= ~keybord_data.press;

	//今のキーの状態を渡す
	oldKeyState = key;
}

void C_DInput::KeyBordDataRefresh()
{
	KeyBordRefresh();	//キーボードの情報更新
	LimitKeyBoard();	//キーボードの制御
}

C_DInput::~C_DInput(void)
{
}
