#pragma once
/******************************************************************
 *	@file	UtilBattle.h
 *	@brief	ogึAฬUtil
 *
 *	ป์าFOใ
 *	วาFOใ
 ******************************************************************/

namespace UtilBattle
{
	// UตฝฉH
	bool		isRunGroundAttack();
	bool		isRunSkyAttack();

	bool		isRunWeakGroundAttack();
	bool		isRunWeakSkyAttack();

	bool		isRunMediumGroundAttack();
	bool		isRunMediumSkyAttack();

	bool		isRunStrongGroundAttack();
	bool		isRunStrongSkyAttack();

	// U๑
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

	// Uอแบ
	void		addBadStatusAtkLv();
	void		resetBadStatusAtkLv();
	int			getBadStatusAtkLv();
}