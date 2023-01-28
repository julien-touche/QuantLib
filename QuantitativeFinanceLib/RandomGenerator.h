#pragma once
#include "typedef.h"

class RandomGenerator
{
public:
	RandomGenerator(unsigned long dim = 1) : itsDim(dim)
	{}

	inline unsigned long	GetDim() const				{ return itsDim;	}
	inline void				SetDim (unsigned long & dim){ itsDim = dim;		}

	virtual void GetUniforms(vDbl & draws) const = 0;

	template <GEN_GAUSS GAUSS_TYPE>
	void GetGaussians(const vDbl & uniforms, vDbl & draws) const;

private:
	unsigned long itsDim;
};

