#pragma once
/******************************************************************
 *	@file	OrbitWave.h
 *	@brief	正弦波軌道
 *
 *	製作者：三上
 *	管理者：三上
 ******************************************************************/

class OrbitWave
{
public:
	OrbitWave(int amplitude, int cycle_frame, float speed_x);
	~OrbitWave();

	void	setAmplitude(int amplitude);

	void	setCycleFrame(int cycle_frame);
	
	void	setSpeed(float speed_x);
	
	void	update(Vector2f* dst_pos);

private:
	int		mAmplitude;		// 振幅
	int		mCycleFrame;	// 周期フレーム
	float	mSpeedX;		// 移動スピード
	int		mTime;			// 経過時間
};