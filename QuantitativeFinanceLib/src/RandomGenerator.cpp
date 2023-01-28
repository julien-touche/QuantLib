#define _USE_MATH_DEFINES

#include "RandomGenerator.h"
#include "Distributions.h"
#include <stdexcept>


template <>
void RandomGenerator::GetGaussians<MARSAGLIA>(vDbl& draws) const
{
	const Unt size = draws.size();
	if (size != itsDim)
	{
		throw std::invalid_argument("size of gaussian vector does not match dimensionality of the generator");
	}

	bool isRejected	= true;
	vDbl tmpUnif(2);
	double u1(0.0), u2(0.0), u(0.0);
	for (Unt i = 0; i < draws.size() - 1; ++i)
	{
		while (isRejected)
		{
			tmpUnif = GetUniforms(2);
			u1 = tmpUnif[0];
			u2 = tmpUnif[1];
			u = u1 * u1 + u2 * u2;
			isRejected = (u >= 1.0) || (0 == u) ? true : false;
		}
		draws[i] = u1 * sqrt(-2.0 * log(u) / u);
		draws[i+1] = u2 * sqrt(-2.0 * log(u) / u);
	}
	
}

template <>
void RandomGenerator::GetGaussians<BOXMULLER>(vDbl& draws) const
{
	const Unt size = draws.size();
	if (size != itsDim)
	{
		throw std::invalid_argument("size of gaussian vector does not match dimensionality of the generator");
	}

	Unt aimedSize = size;
	if (size % 2 != 0) { aimedSize += 1; }

	const vDbl uniforms = GetUniforms(aimedSize);
	for (Unt i = 1; i < uniforms.size() - 1; ++i)
	{
		draws[i - 1] = sqrt(-2.0 * log(uniforms[i - 1])) * cos(2 * M_PI * uniforms[i]);
		draws[i]	 = sqrt(-2.0 * log(uniforms[i - 1])) * sin(2 * M_PI * uniforms[i]);
	}
	if (size == aimedSize) { draws.back() = sqrt(-2.0 * log(uniforms[size - 2])) * cos(2.0 * M_PI * uniforms[size - 1]);  }
}

template <>
void RandomGenerator::GetGaussians<INVERSE>(vDbl& draws) const
{
	const Unt size			 = draws.size();
	if (size != itsDim)
	{
		throw std::invalid_argument("size of gaussian vector does not match dimensionality of the generator");
	}
	const vDbl uniforms		 = GetUniforms(size);

	vDbl::const_iterator uIt = uniforms.begin();
	vDbl::iterator		 dIt = draws.begin();
	for (; uIt != uniforms.end(); ++uIt, ++dIt)
	{
		*dIt = InvCdfNrm(*uIt);
	}
}

