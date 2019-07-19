#include "OrbitCalculation.h"

OrbitCalculation::OrbitCalculation(void)
{
	mParabora	= new OrbitParabora();
	mRebound	= new OrbitRebound();
}

OrbitCalculation::~OrbitCalculation(void)
{
}
