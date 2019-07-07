#include "OrbitCalculation.h"

C_OrbitCalculation::C_OrbitCalculation(void)
{
	mParabora	= new C_OrbitParadora();
	mRebound	= new C_OrbitRebound();
	mWave		= new C_OrbitWave();
}

C_OrbitCalculation::~C_OrbitCalculation(void)
{
}
