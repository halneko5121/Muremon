#pragma once
/******************************************************************
 *	@file	Collision.h
 *	@brief	�R���W����
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class ActorBase;

struct HitParam
{
	HitParam(const int& id, const Vector2f& pos)
		: mActorId(id)
		, mHitPos(pos)
	{
	}

	const int&		mActorId;
	const Vector2f&	mHitPos;
};

class Collision
{
public:
	template<class OWNER>
	Collision(OWNER* owner, void(OWNER::*registFunc)(const HitParam&))
		: mOwner(owner)
		, mRegistFunc(nullptr)
	{
		typedef Delegate<OWNER> DelegateImple;
		mRegistFunc = new DelegateImple(owner, registFunc);
	}
	virtual ~Collision();

	bool			isHit(const Collision& target) const;
	const int&		getOwnerId() const;
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

		// �R���X�g���N�^
		Delegate()
			: mOwner(nullptr)
			, mRegistFunc(nullptr)
		{
		}

		// �R���X�g���N�^
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
};