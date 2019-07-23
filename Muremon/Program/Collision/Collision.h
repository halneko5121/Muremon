#pragma once
/******************************************************************
 *	@file	Collision.h
 *	@brief	コリジョン
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class Rect;

class Collision
{
public:
	template<class OWNER>
	Collision(OWNER* owner, void(OWNER::*registFunc)())
		: mRect(&owner->getRect())
		, mRegistFunc(nullptr)
	{
		typedef Delegate<OWNER> DelegateImple;
		mRegistFunc = new DelegateImple(owner, registFunc);
	}
	virtual ~Collision();

	bool		isHit(const Collision& target) const;
	const Rect&	getCollision() const;
	void		registFuncRun();

private:
	class IDelegate
	{
	public:
		virtual void exe() = 0;
	};

	template<class OWNER>
	class Delegate : public IDelegate
	{
	public:
		typedef void(OWNER::*ExeFunc)();

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
		exe() override
		{
			if (mRegistFunc != nullptr) (mOwner->*mRegistFunc)();
		}

	private:
		OWNER*		mOwner;
		ExeFunc		mRegistFunc;
	};

private:
	const Rect*		mRect;
	IDelegate*		mRegistFunc;
};