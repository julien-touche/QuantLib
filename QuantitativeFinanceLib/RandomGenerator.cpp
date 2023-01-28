#include "RandomGenerator.h"
#include "Distributions.h"


template <>
void RandomGenerator::GetGaussians<MARSAGLIA>(vDbl& draws) const
{
	const Unt size = draws.size();
	
}

template <>
void RandomGenerator::GetGaussians<BOXMULLER>(vDbl& draws) const
{
	const Unt size = draws.size();

}

template <>
void RandomGenerator::GetGaussians<INVERSE>(vDbl& draws) const
{
	const Unt size			 = draws.size();
	const vDbl uniforms		 = GetUniforms(size);

	vDbl::const_iterator uIt = uniforms.begin();
	vDbl::iterator		 dIt = draws.begin();
	for (; uIt != uniforms.end(); ++uIt, ++dIt)
	{
		*dIt = InvCdfNrm(*uIt);
	}
}

