#pragma once
/******************************************************************
 *	@file	Collision.h
 *	@brief	�R���W����
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

class Rect;
class ActorBase;

class Collision
{
public:
	template<ActorBase*>
	Collision(ActorBase* owner, void(ActorBase::*registFunc)());
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
		exe() override
		{
			if (mRegistFunc != nullptr) (mOwner->*mRegistFunc)();
		}

	private:
		OWNER*		mOwner;
		ExeFunc		mRegistFunc;
	};

private:
	Rect*		mRect;
	IDelegate*	mRegistFunc;
};