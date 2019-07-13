#pragma once

/**********************************
	役割：正弦波処理の設定															
	説明：																			
	作成日：2009年 3月 20日															
	更新日：	年	月	 日															
 **********************************/

enum WAVE_MODE
{
	WAVE_MODE_NORMAL,										//通常の正弦波処理
	WAVE_MODE_GAME,											//だんだんと波が収まる(ゲーム仕様)
};

class OrbitWave
{
public:
	OrbitWave();
	~OrbitWave();

	/********************************************************************************************
	*	役割	：初期化																		*
	*	関数名	：POS_CC OrbitSinWave(int amplitude, int cycle, float limit_x, POS_CC draw_cc)	*
	*	引数	：int set_amplitude			振幅の量(上下の幅)									*
	*			：int set_cycle				周期の速さ(大きい程周期は短く)						*
	*			：float set_speed_x			移動の早さ											*
	*			：int set_mode				1:通常の正弦波処理	2:ゲームの使用に沿った処理		*
	*	作成日	：2009年 3月 22日																*
	*	更新日	：	年	月	 日							by	三上　亘							*
	********************************************************************************************/
	void init(int set_amplitude, int set_cycle,	float set_speed_x, int set_mode);

	/********************************************************************************************
	*	役割	：振幅の変更(上下に動く幅)														*
	*	作成日	：2009年 3月 22日																*
	*	更新日	：	年	月	 日							by	三上　亘							*
	********************************************************************************************/
	void setAmplitude(int set_amplitude) { mAmplitude = set_amplitude; }

	/********************************************************************************************
	*	役割	：周期の変更(多きければ大きい程周期が短く)										*
	*	作成日	：2009年 3月 22日																*
	*	更新日	：	年	月	 日							by	三上　亘							*
	********************************************************************************************/
	void setCycle(int set_cycle)		 { mCycle	 = set_cycle; }
	
	/********************************************************************************************
	*	役割	：進む速さ																		*
	*	作成日	：2009年 3月 22日																*
	*	更新日	：	年	月	 日							by	三上　亘							*
	********************************************************************************************/
	void setSpeed(float set_speed_x)		 { mSpeedX	 = set_speed_x; }
	
	/********************************************************************************************
	*	役割	：モード変更																	*
	*	作成日	：2009年 3月 22日																*
	*	更新日	：	年	月	 日							by	三上　亘							*
	********************************************************************************************/
	void setMode(int set_mode)			 { mMode	 = set_mode; }

	/********************************************************************************************
	*	役割	：正弦波処理																	*
	*	関数名	：POS_CC OrbitSinWave(int amplitude, int cycle, float limit_x, POS_CC draw_cc)	*
	*	引数	：int limit_x			xの限界値を設けて初期化									*
	*			：POS_CC drae_cc		中心座標												*
	*			：int mode				1:通常の正弦波処理	2:ゲーム仕様の正弦波処理 			*
	*	戻り値	：中心座標																		*
	*	作成日	：2009年 3月 22日																*
	*	更新日	：	年	月	 日							by	三上　亘							*
	********************************************************************************************/
	Vector2f orbitSinWave(float limit_x, Vector2f draw_cc);

private:
	int		mAmplitude;
	int		mCycle;
	float	mSpeedX;
	int		mMode;
	int		mTime1;
	int		mTime2;
	int		mSettle;
	float	mDeg;
};