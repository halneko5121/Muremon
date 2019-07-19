#pragma once
/******************************************************************
 *	@file	stdafx.h
 *	@brief	プリコンパイル済みヘッダー
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <vector>
#include <list>
#include <string>
#include <d3dx9math.h>
#include "Library/Math/Vector.h"
#include "Library/Math/Rect.h"

#define PI								(D3DX_PI)
#define RAD								(D3DX_PI/180.0f)	// 角度からラジアンを求める
#define DEG								(180.0f/D3DX_PI)	// ラジアンから角度を求める

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
