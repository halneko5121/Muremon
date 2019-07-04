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
	bool		IsRunGroundAttack();
	bool		IsRunSkyAttack();

	bool		IsRunWeakGroundAttack();
	bool		IsRunWeakSkyAttack();

	bool		IsRunMediumGroundAttack();
	bool		IsRunMediumSkyAttack();

	bool		IsRunStrongGroundAttack();
	bool		IsRunStrongSkyAttack();
}