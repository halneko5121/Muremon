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
	static DirectSound*		getInstance();

	/**
	 * @brief	インスタンスの生成
	 */
	static void				create();

	/**
	 * @brief	インスタンスの破棄
	 */
	static void				destroy();

	/**
	 * @brief	初期化
	 * @param	window_handle    ウィンドウハンドル
	 * @return	true:成功   false:失敗
	 */
	bool					init(HWND window_handle);

	/**
	 * @brief	開放処理
	 */
	void					release();

	/**
	 * @brief	音楽データ読み込み
	 * @param	file_name	ファイル名
	 * @return	true:成功   false:失敗
	 */
	bool					load(LPTSTR file_name);

	/**
	 * @brief	ワンス再生
	 * @param	id		サウンドのID
	 */
	void					playOnce(short id);

	/**
	 * @brief	ループ再生
	 * @param	id		サウンドのID
	 */
	void					playLoop(short id);

	/**
	 * @brief	一時停止
	 * @param	id			サウンドのID
	 */
	void					pause(short id);

	/**
	 * @brief	停止
	 * @param	id			サウンドのID
	 */
	void					stop(short id);

	/**
	 * @brief	指定IDのサウンドが再生中か
	 */
	bool					isPlaying(short id) const;

	/**
	 * @brief	ボリューム設定
	 * @param	volume		ボリュームの値（「０(最大ボリューム)」〜「−１００００(最小ボリューム)」）
	 * @param	id			サウンドのID
	 */
	void					setVolume(short volume, short id);

private:
	/**
	 * @brief	音楽データ読み込み＆登録
	 * @param	file_name	ファイル名
	 * @param	id			登録するサウンドのID
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT					loadAndRegist(LPTSTR file_name, short id);

	/**
	 * @brief	プライマリバッファの作成
	 * @return	true:成功   false:失敗
	 */
	bool					createPrimaryBuffer();

	/**
	 * @brief	セカンダリバッファの作成
	 * @param	wfex			WAVEファイルのフォーマット
	 * @param	lpBuffer		バッファ
	 * @param	dwBufferSize	バッファサイズ
	 * @param	id				サウンドID
	 * @return	S_OK:成功   E_FAIL:失敗
	 */
	HRESULT					createSecondaryBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const short id);

	/**
	 * @brief	再生
	 * @param	loop	ループするか
	 * @param	id		サウンドのID
	 */
	void					playImple(bool loop, short id);

	/**
	 * @brief	停止
	 * @param	is_pouse	一時停止か
	 * @param	id			サウンドのID
	 */
	void					stopImple(bool is_pouse, short id);

private:
	enum { MAX_SOUND = 20 };								// 読み込めるサウンドの最大数

private:
	static DirectSound*		mInstance;
	LPDIRECTSOUND8			mDirectSound;
	LPDIRECTSOUNDBUFFER		mPrimaryBuffer;					// プライマリーバッファ
	LPDIRECTSOUNDBUFFER		mSecondaryBuffer[MAX_SOUND];	// セカンダリバッファ
	int						mMaxSound;
};

static DirectSound* GetDirectSound() { return DirectSound::getInstance(); }
