#pragma once
/******************************************************************
 *	@file	UtilSound.h
 *	@brief	�T�E���h�֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

enum SoundId
{
	cSoundId_BgmTitle,			// �^�C�g��BGM
	cSoundId_SeCursorMove,		// �J�[�\���ړ���
	cSoundId_SeOk,				// ���艹
	cSoundId_SeCancel,			// �L�����Z��
	cSoundId_BgmBattle,			// �o�g��BGM
	cSoundId_SeGameStart,		// �Q�[���X�^�[�g
	cSoundId_SeAlert,			// �댯
	cSoundId_SeMissionStart,	// �~�b�V�����J�n
	cSoundId_SeOugiEffect,		// ���`
	cSoundId_SeMissionClear,	// �~�b�V�����N���A
	cSoundId_SeBossDead,		// ����������񂾎�
	cSoundId_SeHitNikuman,		// ���܂�@�U��������������
	cSoundId_SeHitYoshiGround,	// �g���Y�@�n��U��������������
	cSoundId_SeHitYoshiSky,		// �g���Y�@�󒆍U��������������
	cSoundId_SeHitNoppo,		// �̂��ہ@��������
	cSoundId_SeHitNoppoDead,	// �̂��ہ@���̒����̂�����������
	cSoundId_SeHitNoppoSky,		// �̂��ہ@�󒆍U��������������
	cSoundId_SeGameOver,		// �Q�[���I�[�o�[
	cSoundId_SeGameClear,		// �Q�[���N���A
	cSoundId_SeMissionEnd,		// �~�b�V�����I��
	cSoundId_Count,
};

namespace UtilSound
{
	void playOnce(const SoundId& id);
	void playLoop(const SoundId&id);
	void pause(const SoundId& id);
	void stop(const SoundId& id);
	bool isPlaying(const SoundId& id);
	void setVolume(const SoundId& id, short volume);
}