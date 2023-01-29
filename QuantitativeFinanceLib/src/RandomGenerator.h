#pragma once
#include "typedef.h"
#include <armadillo>

using namespace arma;
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

	template <GEN_GAUSS GAUSS_TYPE>
	colvec GetCorrGaussians(const mat & corr, vDbl& draws) const;

private:
	unsigned long itsDim;
};

/*** supposing corr is at-least semi-definite ***/
template <GEN_GAUSS GAUSS_TYPE>
colvec RandomGenerator::GetCorrGaussians(const mat & corr, vDbl& draws) const
{
	const Unt size = draws.size();

	if (itsDim != size)
	{
		throw std::invalid_argument("size of gaussian vector does not match dimensionality of the generator");
	}
	if (size != corr.n_cols)
	{
		throw std::invalid_argument("correlation matrix does not have the correct size");
	}

	GetGaussians<GAUSS_TYPE>(draws);
	mat tmpMat(corr.n_rows, corr.n_cols);

	if (corr.is_sympd())
	{
		tmpMat = chol(mat, "lower");
	}
	else
	{
		tmpMat = sqrtmat(mat);
	}
	colvec armaDraws(conv_to<colvec>::from(draws));
	armaDraws = tmpMat * armaDraws;
	return armaDraws;
}

