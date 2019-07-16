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
	MissionBase(MissionId id, Texture* texture, Vertex* vertex);
	virtual ~MissionBase();

	void			run();

	virtual void	runImple() = 0;
	virtual void	update() = 0;
	virtual void	draw() = 0;
	virtual bool	isSuccess() const = 0;
	virtual bool	isFailure() const = 0;

protected:
	void			drawTime();
	void			drawCombo();

protected:
	MissionId		mId;
	Texture*		mTexture;		// テクスチャ
	Vertex*			mVertex;		// バーテックス
	int				mTime;
	int				mKeyCount;
};