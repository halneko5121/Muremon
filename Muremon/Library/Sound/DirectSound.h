#pragma once 
/******************************************************************
 *	@file	DirectSound.h
 *	@brief	サウンドの管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include <dsound.h>

#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")

class DirectSound
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	DirectSound();

	/**
	 * @brief	デストラクタ
	 */
	~DirectSound();

	/**
	 * @brief	インスタンスの取得
	 */
	static DirectSound* GetInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void Create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void Destroy();

	/**
	 * @brief	初期化
	 * @param	window_handle    ウィンドウハンドル
	 * @return	true:成功   false:失敗
	 */
	bool InitDSound(HWND window_handle);

	/**
	 * @brief	開放処理
	 */
	void UnInitDSound();

	/**
	 * @brief	音楽データ読み込み
	 * @param	file_name	ファイル名
	 * @return	true:成功   false:失敗
	 */
	bool LoadSoundData(LPTSTR file_name);

	/**
	 * @brief	音楽データ読み込み
	 * @param	file_name	ファイル名
	 * @param	id			登録するサウンドのID
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT LoadSound(LPTSTR file_name, short id);

	/**
	 * @brief	ワンス再生
	 * @param	id		サウンドのID
	 */
	void SoundPlayOnce(short id);

	/**
	 * @brief	ループ再生
	 * @param	id		サウンドのID
	 */
	void SoundPlayLoop(short id);

	/**
	 * @brief	一時停止
	 * @param	id			サウンドのID
	 */
	void SoundPouse(short id);

	/**
	 * @brief	停止
	 * @param	id			サウンドのID
	 */
	void SoundStop(short id);

	/**
	 * @brief	指定IDのサウンドが再生中か
	 */
	bool IsPlaySound(short id);

	/**
	 * @brief	ボリューム設定
	 * @param	volume		ボリュームの値（「０(最大ボリューム)」～「－１００００(最小ボリューム)」）
	 * @param	id			サウンドのID
	 */
	void SetVolume(short volume, short id);

private:
	/**
	 * @brief	プライマリバッファの作成
	 * @return	true:成功   false:失敗
	 */
	bool CreatePrimaryBuffer();

	/**
	 * @brief	セカンダリバッファの作成
	 * @param	wfex			WAVEファイルのフォーマット
	 * @param	lpBuffer		バッファ
	 * @param	dwBufferSize	バッファサイズ
	 * @param	id				サウンドID
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT CreateSecondaryBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const short id);

	/**
	 * @brief	再生
	 * @param	loop	ループするか
	 * @param	id		サウンドのID
	 */
	void SoundPlayImple(bool loop, short id);

	/**
	 * @brief	停止
	 * @param	is_pouse	一時停止か
	 * @param	id			サウンドのID
	 */
	void SoundStopImple(bool is_pouse, short id);

private:
	enum { MAX_SOUND = 20 };								// 読み込めるサウンドの最大数

private:
	static DirectSound*		mInstance;
	LPDIRECTSOUND8			mDirectSound;
	LPDIRECTSOUNDBUFFER		mPrimaryBuffer;					// プライマリーバッファ
	LPDIRECTSOUNDBUFFER		mSecondaryBuffer[MAX_SOUND];	// セカンダリバッファ
	int						mMaxSound;
};

static DirectSound* GetDirectSound() { return DirectSound::GetInstance(); }