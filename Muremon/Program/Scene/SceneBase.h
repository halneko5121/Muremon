#pragma once
/******************************************************************
 *	@file	SceneManage.h
 *	@brief	シーンの管理を行う
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"
#include "Library/Input/DirectInput.h"

class C_DInputKey;
class C_DInputMouse;
class C_DWaveSound;
class Texture;
class Vertex;
class C_Sprite;
class C_Animetion;
namespace Dix
{
	class C_PCMPlayer;
}

enum SceneName
{
	cSceneName_Logo,		// ロゴ
    cSceneName_Title,		// タイトル
    cSceneName_Prologue,	// あらすじ
	cSceneName_Tutorial,	// ゲーム操作説明
	cSceneName_GameRefresh,	// ゲーム（すっきり）
	cSceneName_GameNormal,	// ゲーム（ノーマル）
	cSceneName_Ending,		// エンディング
	cSceneName_Ranking,		// ランキング
	cSceneName_GameEnd,		// 終わり
};

class SceneBase
{
public:
	/**
	 * @brief	コンストラクタ
	 */
	SceneBase();

	/**
	 * @brief	デストラクタ
	 */
	virtual ~SceneBase();

	/**
	 * @brief	初期化処理
	 */
	virtual void Init() = 0;

	/**
	 * @brief	更新処理
	 * @return	シーン終了か
	 */
	virtual bool Update() = 0;

	/**
	 * @brief	描画処理
	 */
	virtual void Draw() = 0;

	/**
	 * @brief	終了処理
	 */
	virtual int End() = 0;

	/*-		共通関数	-*/

	/**
	 * @brief	実行処理
	 */
	bool RunScene();

	/**
	 * @brief	設定処理
	 * @param	apDev		デバイス
	 */
	void SetScene(LPDIRECT3DDEVICE9 apDev);

	/**
	 * @brief	シーンの変更を行う
	 * @param	nextID		次のシーンの番号
	 */
	void ChangeScene(DWORD next_id);

	//-情報取得関数-

	/**
	 * @brief	シーン番号の取得
	 */
	DWORD GetSceneID();

protected:
    DWORD               mSceneID;		// シーンの番号
	LPDIRECT3DDEVICE9	mDevice;		// デバイス
	Texture*			mTexture;
	Vertex*			mVertex;

	int					mAlpha;			// 各シーンのalpha値		
	bool				mIsSceneChange;	// シーンが変わる時を知らせる
	MouseData			mMouseData;		// マウス情報
};
