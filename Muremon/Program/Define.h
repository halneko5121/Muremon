#pragma once
/******************************************************************
 *	@file	Define.h
 *	@brief	�e���`
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
 ******************************************************************/

#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <tchar.h>
#include "DefineGame.h"

#define APP_SAFE_RELEASE(p)				{if(p){(p)->Release();	(p) = nullptr;} }
#define APP_SAFE_DELETE_ARRAY(p)		{if(p){delete[](p);		(p) = nullptr;} }
#define APP_SAFE_DELETE(p)				{if(p){delete(p);		(p) = nullptr;} }

#ifdef _DEBUG
#define	APP_PRINT(format, ...)							\
		{												\
			char temp[256];								\
			sprintf_s(temp, 256, format, __VA_ARGS__);	\
			OutputDebugString(temp);					\
		}										
#define APP_PRINT_NL(format, ...)		{ APP_PRINT(format, __VA_ARGS__); OutputDebugString("\n"); }
#else
#define APP_PRINT(...)					{ }
#define APP_PRINT_NL(...)				{ }
#endif

#define APP_ASSERT(p)					{ assert(p); }
#define APP_ASSERT_FALSE()				{ assert(false); }
#define APP_ASSERT_MESSAGE(p, str)		{ if(!(p)) { APP_PRINT_NL(str); } assert(p); }
#define APP_ASSERT_FALSE_MESSAGE(str)	{ APP_ASSERT_MESSAGE(false, str); }
#define APP_POINTER_ASSERT(p)			{ if(p == nullptr){ APP_ASSERT_FALSE(); } }

#define SAFE_RELEASE(p) 				{if(p){(p)->Release(); 	(p) = nullptr;} }
#define SAFE_DELETE_ARRAY(p)			{if(p){delete[](p);		(p) = nullptr;} }
#define SAFE_DELETE(p)					{if(p){delete(p);		(p) = nullptr;} }
#define MAX_ALPHA			(255)
#define MAX_RGB				(255)
#define MAX_STRING			(256)
#define GAMESIZE_HEGHT		(600)
#define GAMESIZE_WIDE		(800)

#define G_ALPHA_INCREASE	(15)
#define GAME_GROUND			(500.f)	//�Q�[�����̒n�ʂɓ����鏊
#define MAX_VALLUE_PLAYER	(80)	//�L������C�ɂ��̑���

template <class T>
struct POS_CC{
	T x;
	T y;
};
//�ǉ����O��3/26

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

enum CHARA_ID
{
	ID_YOSHI,
	ID_NIKUMAN,
	ID_NOPPO,
};