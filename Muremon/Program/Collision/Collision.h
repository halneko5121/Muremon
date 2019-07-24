#pragma once
/******************************************************************
 *	@file	Collision.h
 *	@brief	コリジョン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class ActorBase;

struct HitParam
{
	HitParam(const int& id, int actor_uniq_id, const Vector2f& pos)
		: mActorId(id)
		, mActorUniqId(actor_uniq_id)
		, mHitPos(pos)
	{
	}

	const int&		mActorId;
	const int&		mActorUniqId;
	const Vector2f&	mHitPos;
};

class Collision
{
public:
	template<class OWNER>
	Collision(OWNER* owner, void(OWNER::*registFunc)(const HitParam&))
		: mOwner(owner)
		, mRegistFunc(nullptr)
		, mIsEnable(true)
	{
		typedef Delegate<OWNER> DelegateImple;
		mRegistFunc = new DelegateImple(owner, registFunc);
	}
	virtual ~Collision();

	void			setEnable(bool is_enable);
	bool			isEnable() const;

	bool			isHit(const Collision& target) const;
	const int&		getOwnerId() const;
	const int&		getOwnerUniqId() const;
	const Rect&		getCollision() const;
	const Vector2f&	getPos() const;
	void			registFuncRun(const HitParam& param);

private:
	class IDelegate
	{
	public:
		virtual void exe(const HitParam& param) = 0;
	};

	template<class OWNER>
	class Delegate : public IDelegate
	{
	public:
		typedef void(OWNER::*ExeFunc)(const HitParam&);

		// コンストラクタ
		Delegate()
			: mOwner(nullptr)
			, mRegistFunc(nullptr)
		{
		}

		// コンストラクタ
		Delegate(OWNER* owner, ExeFunc exe_func)
			: mOwner(owner)
			, mRegistFunc(exe_func)
		{
		}

		virtual void
		exe(const HitParam& param) override
		{
			if (mRegistFunc != nullptr) (mOwner->*mRegistFunc)(param);
		}

	private:
		OWNER*		mOwner;
		ExeFunc		mRegistFunc;
	};

private:
	ActorBase*		mOwner;
	IDelegate*		mRegistFunc;
	bool			mIsEnable;
};