//---------------------------------------------
//      サウンドの設定
//			作成者:平野
//---------------------------------------------

#ifndef _DIRECTSOUND_H_
#define _DIRECTSOUND_H_

#include <dsound.h>
#include <stdio.h>

#pragma comment (lib,"dsound.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib, "winmm.lib")

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[](p);		(p) = NULL;} }

#define CHANNELS		2		// チャンネル数
#define SAMPLESPERSEC	44100	// サンプリングレート
#define BITSPERSAMPLE	16		// １サンプルあたりのビット数
#define MAX_SOUND       20      // 読み込めるサウンドの最大数

class C_DSound
{
public:
	static C_DSound* GetInstance();
	static void Create();
	static void Destroy();
	
	C_DSound();

	/*===================================================
		DirectSoundの初期化
		引数	ウィンドウハンドル
		戻り値	true	初期化成功
				false	失敗
	=====================================================*/
	bool InitDSound(HWND hWnd);

	/*===================================================
		音楽データ読み込み
		引数１	ファイル名
		戻り値	true	読み込み成功
				false	失敗
	=====================================================*/
	bool LoadSoundData(LPTSTR FileName);

	/*===================================================
		音楽データ読み込み
		引数１	ファイル名
		引数２	登録するサウンドのID
		戻り値	S_OK	読み込み成功
				E_FAIL	失敗
	=====================================================*/
	HRESULT LoadSound(LPTSTR pFileName, short ID);

	/*===================================================
		音楽再生
		引数１	ループするか(true = ループする、false = １度だけ再生)
		引数２	サウンドのID
	=====================================================*/
	void SoundPlay(bool loop, short ID);

	/*===================================================
		音楽停止
		引数１	完全停止か(true = 完全停止、false = 一時停止)
		引数２	サウンドのID
	=====================================================*/
	void SoundStop(bool ResetFlg, short ID);

	/*===================================================
		音楽の再生状態の確認
		引数	サウンドのID
		戻り値	true	再生中
				false	停止中
	=====================================================*/
	bool SoundPlayCheck(short ID);

	/*===================================================
		ボリュームチェンジ
		引数１	変更したいボリュームの値（「０(最大ボリューム)」～「－１００００(最小ボリューム)」）
		引数２	サウンドのID
	=====================================================*/
	void VolumeChange(short volume, short ID);

	/*===================================================
		プライマリバッファの作成
		戻り値	true	作成成功
				false	失敗
	=====================================================*/
	bool CreatePriBuffer();

	/*===================================================
		セカンダリバッファの作成
		引数１	WAVEファイルのフォーマット
		引数２	バッファ
		引数３	バッファサイズ
		引数４	サウンドのID
		戻り値	S_OK	作成成功
				E_FAIL	失敗
	=====================================================*/
	HRESULT CreateSecBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const short ID);

	/*===================================================
		開放処理
	=====================================================*/
	void UnInitDSound();

private:
	static C_DSound*		mInstance;
	LPDIRECTSOUND8			mDirectSound;
	LPDIRECTSOUNDBUFFER		mPrimaryBuffer;					// プライマリーバッファ
	LPDIRECTSOUNDBUFFER		mSecondaryBuffer[MAX_SOUND];	// セカンダリバッファ
	int						mMaxSound;
};

static C_DSound* GetDirectSound() { return C_DSound::GetInstance(); }

#endif//_DIRECTSOUND_H_