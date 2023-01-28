#include "RandomGenerator.h"


template <>
void RandomGenerator::GetGaussians<MARSAGLIA>(const vDbl& uniforms, vDbl& draws) const
{
	;
}

template <>
void RandomGenerator::GetGaussians<BOXMULLER>(const vDbl& uniforms, vDbl& draws) const
{
	;
}

template <>
void RandomGenerator::GetGaussians<INVERSE>(const vDbl& uniforms, vDbl& draws) const
{
	;
}

