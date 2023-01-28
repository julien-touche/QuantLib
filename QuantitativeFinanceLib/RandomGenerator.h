#pragma once
#include "typedef.h"

class RandomGenerator
{
public:
	RandomGenerator(unsigned long dim = 1) : itsDim(dim)
	{}

	inline unsigned long	GetDim() const				{ return itsDim;	}
	inline void				SetDim (unsigned long & dim){ itsDim = dim;		}

	virtual vDbl GetUniforms(Unt nbDraws) const = 0;

	template <GEN_GAUSS GAUSS_TYPE>
	void GetGaussians(vDbl & draws) const;

private:
	unsigned long itsDim;
};

