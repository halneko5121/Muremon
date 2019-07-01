//---------------------------------------------
//
//      サウンドの設定
//      作成開始日:3月17日
//			更新日:3月17日
//			作成者:平野
//
//---------------------------------------------

#include "DirectSound.h"

#define CHANNELS		2		// チャンネル数
#define SAMPLESPERSEC	44100	// サンプリングレート
#define BITSPERSAMPLE	16		// １サンプルあたりのビット数


// 唯一のインスタンスを nullptr で初期化
C_DSound* C_DSound::mInstance = nullptr;

/**
 * @brief インスンタンスの取得
 */
C_DSound*
C_DSound::GetInstance()
{
	return mInstance;
}

void
C_DSound::Create()
{
	mInstance = new C_DSound();
}

void
C_DSound::Destroy()
{
	delete mInstance;
	mInstance = nullptr;
}

C_DSound::C_DSound()
{
	mMaxSound = 0;
}

//DirectSoundの初期化
bool C_DSound::InitDSound(HWND hWnd)
{
	//IDirectSound8インターフェイスの取得
	if(FAILED(DirectSoundCreate8(NULL,&mDirectSound, NULL)))
	{
		return false;
	}
	//協調レベルの設定
	if(FAILED(mDirectSound->SetCooperativeLevel(hWnd,DSSCL_PRIORITY)))
	{
		return false;
	}
	//プライマリバッファの作成
	if(!CreatePriBuffer())
	{
		return false;
	}

	return true;
}

//開放処理
void C_DSound::UnInitDSound()
{
	for(short i = 0 ; i < (short)mMaxSound ; i++)
	{
		SoundStop(true, i);
		SAFE_RELEASE(mSecondaryBuffer[i]);
	}
	SAFE_RELEASE(mPrimaryBuffer);
	SAFE_RELEASE(mDirectSound);
}

//音楽データ読み込み
bool C_DSound::LoadSoundData(LPTSTR FileName)
{
	FILE *fp;					//ファイルポインタ
	char countFile[128];		//カウント+読み込み用
	fopen_s(&fp, FileName,"r");	//ファイルオープン

	//エラー処理
	if(fp == NULL){
		MessageBox(NULL,TEXT("ファイルオープンに失敗しました"),NULL,MB_OK);
		return false;
	}

	//ファイルの中身をカウント
	while(fscanf_s(fp,"%s\n",countFile,sizeof(countFile)) != EOF)
	{
		mMaxSound++;	//ファイル名をカウント
	}

	//読み込んでいるファイルを最初の位置に戻す
	fseek(fp,0,SEEK_SET);

	//読み込み処理
	for(int i = 0;i < mMaxSound;i++){
		fscanf_s(fp,"%s\n",countFile,sizeof(countFile));
		LoadSound(countFile,i);
	}

	//エラー処理
	if(fclose(fp)){
		MessageBox(NULL,TEXT("ファイルクローズに失敗しました"),NULL,MB_OK);
		return false;
	}
	return true;
}

//音楽データ読み込み
HRESULT C_DSound::LoadSound(LPTSTR pFileName, short ID)
{
	if(ID >= MAX_SOUND)
	{
		MessageBox(NULL, TEXT("登録しようとしているＩＤが大きすぎます"), NULL, MB_OK);
		return E_FAIL;
	}

	HMMIO			hmmio = NULL;
	MMCKINFO		ckInfo;
	WAVEFORMATEX	wfex;

	//WAVEファイル内のヘッダ情報の確認と読み込み
	hmmio = mmioOpen(pFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);

	//RIFFファイルのチャンクの先頭に進入
	if(mmioDescend(hmmio, &ckInfo, NULL, 0) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("チャンクへの進入失敗[RIFF]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}

	//チャンクの検索
	if(ckInfo.ckid != FOURCC_RIFF || ckInfo.fccType != mmioFOURCC('W','A','V','E'))
	{
		MessageBox(NULL,TEXT("発見できませんでした[RIFF][WAVE]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}

	//フォーマットチャンクの検索
	ckInfo.ckid = mmioFOURCC('f','m','t',' ');
	if(mmioDescend(hmmio, &ckInfo, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("発見できませんでした[fmt ]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}
	//フォーマットの読み込み
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	if(mmioRead(hmmio, (HPSTR)&wfex, sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX))
	{
		MessageBox(NULL,TEXT("読み込み失敗[fmt ]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}
	//チャンクから退出
	if(mmioAscend(hmmio, &ckInfo, NULL) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("チャンクからの退出に失敗しました[fmt ]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}

	//データチャンクの検索
	ckInfo.ckid = mmioFOURCC('d','a','t','a');
	if(mmioDescend(hmmio, &ckInfo, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("発見できませんでした[data]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		return E_FAIL;
	}
	//データの読み込み
	char	*lpBuffer = new char[ckInfo.cksize];
	if(mmioRead(hmmio, lpBuffer, ckInfo.cksize) != (LONG)ckInfo.cksize)
	{
		MessageBox(NULL,TEXT("読み込み失敗[data]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		SAFE_DELETE_ARRAY(lpBuffer);		//念のため
		return E_FAIL;
	}
	//チャンクから退出
	if(mmioAscend(hmmio, &ckInfo, NULL) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL,TEXT("チャンクからの退出に失敗しました[data]"),TEXT("DSound"),MB_OK);
		mmioClose(hmmio,0);
		SAFE_DELETE_ARRAY(lpBuffer);		//念のため
		return E_FAIL;
	}
	if(FAILED(CreateSecBuffer(wfex, lpBuffer, ckInfo.cksize, ID)))
	{
		MessageBox(NULL,TEXT("セカンダリバッファ作成失敗"),TEXT("DSound"),MB_OK);
		return E_FAIL;
	}
	//WAVEファイルを閉じる
	mmioClose(hmmio, 0);

	return S_OK;
}

//音楽再生
void C_DSound::SoundPlay(bool loop, short ID)
{
	if(ID >= MAX_SOUND)
	{
		return;
	}
	if(SoundPlayCheck(ID))
	{
		return;
	}

	if(mSecondaryBuffer[ID])
	{
		mSecondaryBuffer[ID]->Play(0, 0, DSBPLAY_LOOPING & loop);
	}
}

//音楽停止
void C_DSound::SoundStop(bool ResetFlg, short ID)
{
	if(ID >= MAX_SOUND)
	{
		return;
	}

	if(mSecondaryBuffer[ID])
	{
		mSecondaryBuffer[ID]->Stop();
		if(ResetFlg)
		{
			//最初に戻る
			mSecondaryBuffer[ID]->SetCurrentPosition(0);
		}
	}
}

//音楽の再生状態の確認
bool C_DSound::SoundPlayCheck(short ID)
{
	if(ID >= MAX_SOUND)
	{
		MessageBox(NULL, TEXT("ＩＤが大きすぎます"), NULL, MB_OK);
		return false;
	}
	if(!mSecondaryBuffer[ID])
	{
		return false;
	}

	DWORD state;
	mSecondaryBuffer[ID]->GetStatus(&state);

	return (state & DSBSTATUS_PLAYING);
}

//ボリュームチェンジ
void C_DSound::VolumeChange(short volume, short ID)
{
	if(ID >= MAX_SOUND)
	{
		return;
	}
	if(!mSecondaryBuffer[ID])
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
	mSecondaryBuffer[ID]->SetVolume(volume);
}

//プライマリバッファ作成
bool C_DSound::CreatePriBuffer()
{
	//DSBUFFERDESC構造体を設定
	DSBUFFERDESC	dsbd;
	ZeroMemory(&dsbd,sizeof(DSBUFFERDESC));
	//プライマリバッファを指定
	dsbd.dwSize			= sizeof(DSBUFFERDESC);
	dsbd.dwFlags		= DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes	= 0;
	dsbd.lpwfxFormat	= NULL;
	//バッファの作成
	if(FAILED(mDirectSound->CreateSoundBuffer(&dsbd, &mPrimaryBuffer, NULL)))
	{
		MessageBox(NULL,TEXT("バッファ作成に失敗"),TEXT("DSound"),MB_OK);
		return false;
	}
	//プライマリバッファのWaveフォーマットを設定
	WAVEFORMATEX	wfex;
	ZeroMemory(&wfex, sizeof(WAVEFORMATEX));
	wfex.wFormatTag		= WAVE_FORMAT_PCM;		//WAVEフォーマットの種類
	wfex.nChannels		= CHANNELS;				//チャンネル数			ステレオ
	wfex.nSamplesPerSec	= SAMPLESPERSEC;		//サンプリングレート	44.1kHz
	wfex.wBitsPerSample	= BITSPERSAMPLE;		//16ビット
	wfex.nBlockAlign	= (wfex.nChannels * wfex.wBitsPerSample) / 8;		//ブロック・アライメント(バイトあたりのビット数)
	wfex.nAvgBytesPerSec= wfex.nSamplesPerSec * wfex.nBlockAlign;			//１秒間に転送するバイト数
	
	if(FAILED(mPrimaryBuffer->SetFormat(&wfex)))
	{
		MessageBox(NULL,TEXT("フォーマット設定失敗"),TEXT("DSound"),MB_OK);
		return false;
	}
	return true;
}

//セカンダリバッファ作成
HRESULT C_DSound::CreateSecBuffer(WAVEFORMATEX &wfex, char *lpBuffer, DWORD dwBufferSize, const short ID)
{
	HRESULT				hr;
	DSBUFFERDESC		dsbd;
	LPDIRECTSOUNDBUFFER	pDSBuf;

	//DSBUFFERDESC構造体の設定
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize			= sizeof(dsbd);
	dsbd.dwFlags		= DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLFX;
	dsbd.dwBufferBytes	= dwBufferSize;
	dsbd.guid3DAlgorithm= DS3DALG_DEFAULT;
	dsbd.lpwfxFormat	= &wfex;

	//セカンダリバッファ作成
	if(SUCCEEDED(hr = mDirectSound->CreateSoundBuffer(&dsbd, &pDSBuf, NULL)))
	{
		hr = pDSBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&mSecondaryBuffer[ID]);
		pDSBuf->Release();

		void* lpData;
		DWORD dwSize;
		mSecondaryBuffer[ID]->Lock(0, dwBufferSize, &lpData, &dwSize, NULL, NULL, 0);
		memcpy(lpData, lpBuffer, dwSize);
		mSecondaryBuffer[ID]->Unlock(lpData, dwSize, NULL, 0);
	}
	SAFE_DELETE_ARRAY(lpBuffer);

	return hr;
}