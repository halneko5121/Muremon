#pragma once
/******************************************************************
 *	@file	UtilBattle.h
 *	@brief	バトル関連のUtil
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

namespace UtilBattle
{
	// 攻撃したか？
	bool		isRunGroundAttack();
	bool		isRunSkyAttack();

	bool		isRunWeakGroundAttack();
	bool		isRunWeakSkyAttack();

	bool		isRunMediumGroundAttack();
	bool		isRunMediumSkyAttack();

	bool		isRunStrongGroundAttack();
	bool		isRunStrongSkyAttack();

	// 攻撃回数
	void		resetAtkCount();

	void		setWeakAtkCount(int count);
	void		addWeakAtkCount();
	int			getWeakAtkCount();

	void		setMediumAtkCount(int count);
	void		addMediumAtkCount();
	int			getMediumAtkCount();

	void		setStrongAtkCount(int count);
	void		addStrongAtkCount();
	int			getStrongAtkCount();

	// 攻撃力低下
	void		addBadStatusAtkLv();
	void		resetBadStatusAtkLv();
	int			getBadStatusAtkLv();
	int			getMulAtkPower();

	// ボス関連
	void		setBossDead();
	float		getBossLifeRate();
}