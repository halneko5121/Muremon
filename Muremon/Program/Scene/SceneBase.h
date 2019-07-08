#pragma once
/******************************************************************
 *	@file	SceneBase.h
 *	@brief	シーンベース
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Graphics/DirectGraphics.h"
#include "Library/Input/DirectInput.h"

class DirectInputKey;
class DirectInputMouse;
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
	void				init(LPDIRECT3DDEVICE9 apDev);
	virtual void		impleInit();

	/**
	 * @brief	更新処理
	 * @return	シーン終了か
	 */
	virtual bool		update() = 0;

	/**
	 * @brief	描画処理
	 */
	virtual void		draw() = 0;

	/**
	 * @brief	終了処理
	 */
	virtual void		end() = 0;

	/*-		共通関数	-*/

	/**
	 * @brief	実行処理
	 */
	bool				runScene();

	/**
	 * @brief	シーン変更リクエストを行う
	 * @param	nextID		次のシーンの番号
	 */
	void				requestChangeScene(DWORD next_id);

	//-情報取得関数-

	/**
	 * @brief	シーン番号の取得
	 */
	DWORD				getSceneID();

protected:
    DWORD               mSceneID;		// シーンの番号
	LPDIRECT3DDEVICE9	mDevice;		// デバイス
	Texture*			mTexture;
	Vertex*				mVertex;

	int					mAlpha;			// 各シーンのalpha値		
	bool				mIsSceneChange;	// シーンが変わる時を知らせる
	MouseData			mMouseData;		// マウス情報
};
