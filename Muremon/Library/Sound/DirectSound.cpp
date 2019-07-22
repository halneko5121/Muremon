/******************************************************************
 *	@file	DirectSound.cpp
 *	@brief	サウンドの管理
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "DirectSound.h"

#define CHANNELS		2		// チャンネル数
#define SAMPLESPERSEC	44100	// サンプリングレート
#define BITSPERSAMPLE	16		// １サンプルあたりのビット数

DirectSound* DirectSound::mInstance = nullptr;

/**
 * @brief インスンタンスの取得
 */
DirectSound*
DirectSound::getInstance()
{
	return mInstance;
}

/**
 * @brief	インスタンスの生成
 */
void
DirectSound::create()
{
	mInstance = new DirectSound();
}

/**
 * @brief	インスタンスの破棄
 */
void
DirectSound::destroy()
{
	APP_SAFE_DELETE(mInstance);
}

/**
 * @brief	初期化
 * @param	window_handle    ウィンドウハンドル
 * @return	true:成功   false:失敗
 */
bool
DirectSound::init(HWND window_handle)
{
	// IDirectSound8インターフェイスの取得
	if(FAILED(DirectSoundCreate8(NULL,&mDirectSound, NULL)))
	{
		return false;
	}
	// 協調レベルの設定
	if(FAILED(mDirectSound->SetCooperativeLevel(window_handle,DSSCL_PRIORITY)))
	{
		return false;
	}
	// プライマリバッファの作成
	if(!createPrimaryBuffer())
	{
		return false;
	}

	return true;
}

/**
 * @brief	開放処理
 */
void
DirectSound::release()
{
	for(int i = 0 ; i < (int)mMaxSound ; i++)
	{
		stop(i);
		SAFE_RELEASE(mSecondaryBuffer[i]);
	}
	SAFE_RELEASE(mPrimaryBuffer);
	SAFE_RELEASE(mDirectSound);
}

/**
 * @brief	音楽データ読み込み
 * @param	file_name	ファイル名
 * @return	true:成功   false:失敗
 */
bool
DirectSound::load(LPTSTR file_name)
{
	FILE *fp;						// ファイルポインタ
	char countFile[128];			// カウント+読み込み用
	fopen_s(&fp, file_name, "r");	// ファイルオープン

	// エラー処理
	if(fp == NULL)
	{
		MessageBox(NULL,TEXT("ファイルオープンに失敗しました"),NULL,MB_OK);
		return false;
	}

	// ファイルの中身をカウント
	while(fscanf_s(fp,"%s\n",countFile,sizeof(countFile)) != EOF)
	{
		// ファイル名をカウント
		mMaxSound++;
	}

	// 読み込んでいるファイルを最初の位置に戻す
	fseek(fp, 0, SEEK_SET);

	// 読み込み処理
	for(int i = 0;i < mMaxSound;i++)
	{
		fscanf_s(fp,"%s\n", countFile, sizeof(countFile));
		loadAndRegist(countFile, i);
	}

	// エラー処理
	if(fclose(fp))
	{
		MessageBox(NULL,TEXT("ファイルクローズに失敗しました"),NULL,MB_OK);
		return false;
	}

	return true;
}

/**
 * @brief	再生
 * @param	id		サウンドのID
 */
void
DirectSound::playOnce(int id)
{
	playImple(false, id);
}

/**
 * @brief	ループ再生
 * @param	id		サウンドのID
 */
void
DirectSound::playLoop(int id)
{
	playImple(true, id);
}

/**
 * @brief	一時停止
 * @param	id		サウンドのID
 */
void
DirectSound::pause(int id)
{
	stopImple(true, id);
}

/**
 * @brief	停止
 * @param	id		サウンドのID
 */
void
DirectSound::stop(int id)
{
	stopImple(false, id);
}

/**
 * @brief	指定IDのサウンドが再生中か
 */
bool
DirectSound::isPlaying(int id) const
{
	if(id >= MAX_SOUND)
	{
		MessageBox(NULL, TEXT("IDが大きすぎます"), NULL, MB_OK);
		return false;
	}
	if(!mSecondaryBuffer[id])
	{
		return false;
	}

	DWORD state;
	mSecondaryBuffer[id]->GetStatus(&state);

	return (state & DSBSTATUS_PLAYING);
}

/**
 * @brief	ボリューム設定
 * @param	volume		ボリュームの値（「０(最大ボリューム)」～「－１００００(最小ボリューム)」）
 * @param	id			サウンドのID
 */
void
DirectSound::setVolume(int volume, int id)
{
	if(id >= MAX_SOUND)
	{
		return;
	}
	if(!mSecondaryBuffer[id])
	{
		return;
	}

	if(volume > 0)
	{
		volume = DSBVOLUME_MAX;
	}
	else if(volume < -10000)
	{
		volume = DSBVOLUME_MIN;
	}
	mSecondaryBuffer[id]->SetVolume(volume);
}

/**
 * @brief	コンストラクタ
 */
DirectSound::DirectSound()
	: mDirectSound(nullptr)
	, mPrimaryBuffer(nullptr)
	, mMaxSound()
{
	for (int i = 0; i < MAX_SOUND; i++)
	{
		mSecondaryBuffer[i] = nullptr;
	}
}

/**
 * @brief	デストラクタ
 */
DirectSound::~DirectSound()
{
}


/**
 * @brief	音楽データ読み込み
 * @param	file_name	ファイル名
 * @param	id			登録するサウンドのID
 * @return	S_OK:成功   E_FAIL:失敗
 */
HRESULT
DirectSound::loadAndRegist(LPTSTR file_name, int id)
{
	if (id >= MAX_SOUND)
	{
		MessageBox(NULL, TEXT("登録しようとしているIDが大きすぎます"), NULL, MB_OK);
		return E_FAIL;
	}

	HMMIO			hmmio = NULL;
	MMCKINFO		ckInfo;
	WAVEFORMATEX	wfex;

	// WAVEファイル内のヘッダ情報の確認と読み込み
	hmmio = mmioOpen(file_name, NULL, MMIO_ALLOCBUF | MMIO_READ);

	// RIFFファイルのチャンクの先頭に進入
	if (mmioDescend(hmmio, &ckInfo, NULL, 0) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("チャンクへの進入失敗[RIFF]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// チャンクの検索
	if (ckInfo.ckid != FOURCC_RIFF || ckInfo.fccType != mmioFOURCC('W', 'A', 'V', 'E'))
	{
		MessageBox(NULL, TEXT("発見できませんでした[RIFF][WAVE]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// フォーマットチャンクの検索
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hmmio, &ckInfo, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("発見できませんでした[fmt ]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// フォーマットの読み込み
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	if (mmioRead(hmmio, (HPSTR)&wfex, sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX))
	{
		MessageBox(NULL, TEXT("読み込み失敗[fmt ]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// チャンクから退出
	if (mmioAscend(hmmio, &ckInfo, NULL) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("チャンクからの退出に失敗しました[fmt ]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// データチャンクの検索
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmio, &ckInfo, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("発見できませんでした[data]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		return E_FAIL;
	}

	// データの読み込み
	char	*lpBuffer = new char[ckInfo.cksize];
	if (mmioRead(hmmio, lpBuffer, ckInfo.cksize) != (LONG)ckInfo.cksize)
	{
		MessageBox(NULL, TEXT("読み込み失敗[data]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		SAFE_DELETE_ARRAY(lpBuffer);		//念のため
		return E_FAIL;
	}

	// チャンクから退出
	if (mmioAscend(hmmio, &ckInfo, NULL) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, TEXT("チャンクからの退出に失敗しました[data]"), TEXT("DSound"), MB_OK);
		mmioClose(hmmio, 0);
		SAFE_DELETE_ARRAY(lpBuffer);		//念のため
		return E_FAIL;
	}
	if (FAILED(createSecondaryBuffer(wfex, lpBuffer, ckInfo.cksize, id)))
	{
		MessageBox(NULL, TEXT("セカンダリバッファ作成失敗"), TEXT("DSound"), MB_OK);
		return E_FAIL;
	}

	// WAVEファイルを閉じる
	mmioClose(hmmio, 0);

	return S_OK;
}

/**
 * @brief	プライマリバッファの作成
 * @return	true:成功   false:失敗
 */
bool
DirectSound::createPrimaryBuffer()
{
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC	dsbd;
	ZeroMemory(&dsbd,sizeof(DSBUFFERDESC));
	// プライマリバッファを指定
	dsbd.dwSize			= sizeof(DSBUFFERDESC);
	dsbd.dwFlags		= DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes	= 0;
	dsbd.lpwfxFormat	= NULL;
	// バッファの作成
	if(FAILED(mDirectSound->CreateSoundBuffer(&dsbd, &mPrimaryBuffer, NULL)))
	{
		MessageBox(NULL,TEXT("バッファ作成に失敗"),TEXT("DSound"),MB_OK);
		return false;
	}
	// プライマリバッファのWaveフォーマットを設定
	WAVEFORMATEX	wfex;
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	wfex.wFormatTag		= WAVE_FORMAT_PCM;								// WAVEフォーマットの種類
	wfex.nChannels		= CHANNELS;										// チャンネル数			ステレオ
	wfex.nSamplesPerSec	= SAMPLESPERSEC;								// サンプリングレート	44.1kHz
	wfex.wBitsPerSample	= BITSPERSAMPLE;								// 16ビット
	wfex.nBlockAlign	= (wfex.nChannels * wfex.wBitsPerSample) / 8;	// ブロック・アライメント(バイトあたりのビット数)
	wfex.nAvgBytesPerSec= wfex.nSamplesPerSec * wfex.nBlockAlign;		// １秒間に転送するバイト数
	
	if(FAILED(mPrimaryBuffer->SetFormat(&wfex)))
	{
		MessageBox(NULL,TEXT("フォーマット設定失敗"),TEXT("DSound"),MB_OK);
		return false;
	}
	return true;
}

/**
 * @brief	セカンダリバッファの作成
 * @param	wfex			WAVEファイルのフォーマット
 * @param	lpBuffer		バッファ
 * @param	dwBufferSize	バッファサイズ
 * @param	id				サウンドID
 * @return	S_OK:成功   E_FAIL:失敗
 */
HRESULT
DirectSound::createSecondaryBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const int id)
{
	HRESULT				hr;
	DSBUFFERDESC		dsbd;
	LPDIRECTSOUNDBUFFER	pDSBuf;

	// DSBUFFERDESC構造体の設定
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize			= sizeof(dsbd);
	dsbd.dwFlags		= DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLFX;
	dsbd.dwBufferBytes	= dwBufferSize;
	dsbd.guid3DAlgorithm= DS3DALG_DEFAULT;
	dsbd.lpwfxFormat	= &wfex;

	// セカンダリバッファ作成
	if(SUCCEEDED(hr = mDirectSound->CreateSoundBuffer(&dsbd, &pDSBuf, NULL)))
	{
		hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&mSecondaryBuffer[id]);
		pDSBuf->Release();

		void* lpData;
		DWORD dwSize;
		mSecondaryBuffer[id]->Lock(0, dwBufferSize, &lpData, &dwSize, NULL, NULL, 0);
		memcpy(lpData, lpBuffer, dwSize);
		mSecondaryBuffer[id]->Unlock(lpData, dwSize, NULL, 0);
	}
	SAFE_DELETE_ARRAY(lpBuffer);

	return hr;
}

/**
 * @brief	再生
 * @param	loop	ループするか
 * @param	id		サウンドのID
 */
void
DirectSound::playImple(bool loop, int id)
{
	if (id >= MAX_SOUND)
	{
		return;
	}
	if (isPlaying(id))
	{
		return;
	}

	if (mSecondaryBuffer[id])
	{
		mSecondaryBuffer[id]->Play(0, 0, DSBPLAY_LOOPING& loop);
	}
}

/**
 * @brief	停止
 * @param	is_pouse	一時停止か
 * @param	id			サウンドのID
 */
void
DirectSound::stopImple(bool is_pouse, int id)
{
	if (id >= MAX_SOUND)
	{
		return;
	}

	if (mSecondaryBuffer[id])
	{
		mSecondaryBuffer[id]->Stop();
		if (!is_pouse)
		{
			// 最初に戻る
			mSecondaryBuffer[id]->SetCurrentPosition(0);
		}
	}
}