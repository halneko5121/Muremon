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
	void				init();
	virtual void		impleInit();

	/**
	 * @brief	更新処理
	 */
	virtual void		update();

	/**
	 * @brief	描画処理
	 */
	virtual void		draw() const {};

	/**
	 * @brief	終了処理
	 */
	virtual void		end() {};

	/**
	 * @brief	シーン変更リクエストを行う
	 * @param	nextID		次のシーンの番号
	 */
	void				requestChangeScene(DWORD next_id);

	/**
	 * @brief	変更するシーン番号の取得
	 */
	DWORD				getChangeSceneID();

	/**
	 * @brief	シーン終了か
	 */
	bool				isSceneEnd() const;

protected:
    DWORD               mChangeSceneID;		// 変更するシーン番号
	Texture*			mTexture;			// テクスチャ
	Vertex*				mVertex;			// バーテックス
	bool				mIsSceneEnd;		// シーン終了か
	MouseData			mMouseData;			// マウス情報
};
