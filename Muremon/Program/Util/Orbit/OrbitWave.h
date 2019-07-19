#pragma once
/******************************************************************
 *	@file	OrbitWave.h
 *	@brief	�����g�O��
 *
 *	����ҁF�O��
 *	�Ǘ��ҁF�O��
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
	int		mAmplitude;		// �U��
	int		mCycleFrame;	// �����t���[��
	float	mSpeedX;		// �ړ��X�s�[�h
	int		mTime;			// �o�ߎ���
};