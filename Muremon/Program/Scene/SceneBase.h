#pragma once
/******************************************************************
 *	@file	SceneBase.h
 *	@brief	シーンベース
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

#include "Library/Input/DirectInput.h"

class Texture;
class Vertex;

enum SceneId
{
	cSceneId_Logo,			// ロゴ
    cSceneId_Title,			// タイトル
    cSceneId_Prologue,		// あらすじ
	cSceneId_Tutorial,		// ゲーム操作説明
	cSceneId_GameRefresh,	// ゲーム（すっきり）
	cSceneId_GameNormal,	// ゲーム（ノーマル）
	cSceneId_Ending,		// エンディング
	cSceneId_Ranking,		// ランキング
	cSceneId_GameEnd,		// 終わり
	cSceneId_Count
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
	Texture*			mTexture;			// テクスチャ
	Vertex*				mVertex;			// バーテックス
	bool				mIsSceneEnd;		// シーン終了か
	MouseData			mMouseData;			// マウス情報

private:
	DWORD               mChangeSceneID;		// 変更するシーン番号
};
