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
	bool		isRunGroundAttack();
	bool		isRunSkyAttack();

	bool		isRunWeakGroundAttack();
	bool		isRunWeakSkyAttack();

	bool		isRunMediumGroundAttack();
	bool		isRunMediumSkyAttack();

	bool		isRunStrongGroundAttack();
	bool		isRunStrongSkyAttack();
}