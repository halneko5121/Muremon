#pragma once
/******************************************************************
 *	@file	UtilBattle.h
 *	@brief	�o�g���֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

namespace UtilBattle
{
	// �U���������H
	bool		isRunGroundAttack();
	bool		isRunSkyAttack();

	bool		isRunWeakGroundAttack();
	bool		isRunWeakSkyAttack();

	bool		isRunMediumGroundAttack();
	bool		isRunMediumSkyAttack();

	bool		isRunStrongGroundAttack();
	bool		isRunStrongSkyAttack();

	// �U����
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



}