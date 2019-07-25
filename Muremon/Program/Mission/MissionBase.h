#pragma once
/******************************************************************
 *	@file	MissionBase.h
 *	@brief	ミッション基底
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Texture;
class Vertex;
enum MissionId;

class MissionBase
{
public:
	explicit MissionBase(const MissionId& id, Texture* texture, Vertex* vertex);
	virtual ~MissionBase();

	void			run();
	void			update();

	// override 用
	virtual void	runImple() {};
	virtual void	updateImple() {};
	virtual void	draw() const = 0;
	virtual bool	isRunning() const = 0;	// 実行中か？
	virtual bool	isSuccess() const = 0;	// 成功したか？
	virtual bool	isFailure() const = 0;	// 失敗したか？

protected:
	void			drawTime() const;
	void			drawCombo() const;

protected:
	MissionId		mId;
	Texture*		mTexture;			// テクスチャ
	Vertex*			mVertex;			// バーテックス
	int				mKeyCount;			// キー入力数
	int				mTime;				// ミッション時間
};