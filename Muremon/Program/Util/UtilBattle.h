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

	void		addWeakAtkCount();
	int			getWeakAtkCount();

	void		addMediumAtkCount();
	int			getMediumAtkCount();

	void		addStrongAtkCount();
	int			getStrongAtkCount();



}