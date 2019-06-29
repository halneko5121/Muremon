#include "OrbitCalculation.h"

C_OrbitCalculation::C_OrbitCalculation(void)
{
	pParadora	= new C_OrbitParadora();
	pRebound	= new C_OrbitRebound();
	pWave		= new C_OrbitWave();
}

C_OrbitCalculation::~C_OrbitCalculation(void)
{
}
