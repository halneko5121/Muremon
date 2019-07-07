#include "OrbitCalculation.h"

OrbitCalculation::OrbitCalculation(void)
{
	mParabora	= new OrbitParabora();
	mRebound	= new OrbitRebound();
	mWave		= new OrbitWave();
}

OrbitCalculation::~OrbitCalculation(void)
{
}
