#pragma once
/******************************************************************
 *	@file	UtilSound.h
 *	@brief	�T�E���h�֘A��Util
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

enum SOUND_DATA
{
	S_BGM_TITLE,		//�^�C�g��BGM
	S_SE_CURSOR_MOVE,	//�J�[�\���ړ���
	S_SE_OK,			//���艹
	S_CANCEL,			//�L�����Z��
	S_BGM_BATTLE,		//�o�g��BGM
	S_GAME_START,		//�Q�[���X�^�[�g
	S_SAIREN,			//�댯
	S_OSIRASE,			//�~�b�V�����J�n
	S_NAMI,				//���`
	S_M_CLEAR,			//�~�b�V�����N���A
	S_DEAD,				//��������@���񂾎�
	S_NIKUMAN,			//���܂�@�U��������������
	S_YOSHI_HIP,		//�g���Y�@�n��U��������������
	S_YOSHI_HUSEN,		//�g���Y�@�󒆍U��������������
	S_NOPPO_KOKE,		//�̂��ہ@��������
	S_NOPPO_PETI,		//�̂��ہ@���̒����̂�����������
	S_NOPPO_GANMEN,		//�̂��ہ@�󒆍U��������������
	S_OVER,				//�Q�[���I�[�o�[
	S_G_CLEAR,			//�Q�[���N���A
	S_M_OVER,			//�Q�[���I�[�o�[

	MAX_SOUND_DATA,
};

namespace UtilSound
{
	void playOnce(short id);
	void playLoop(short id);
	void pause(short id);
	void stop(short id);
	bool isPlaying(short id);
	void setVolume(short volume, short id);
}