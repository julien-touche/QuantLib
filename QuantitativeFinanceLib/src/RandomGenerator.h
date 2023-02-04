#pragma once
#include "typedef.h"
#include <random>
#include <armadillo>

class RandomGenerator
{
protected:
	typedef std::shared_ptr<RandomGenerator> RdGenPtr;
public:
	RandomGenerator(Unt dim = 1) : itsDim(dim)
	{}
	RandomGenerator(const RdGenPtr & rhs) : itsDim(rhs->itsDim)
	{}

	inline Unt		GetDim() const		{ return itsDim;	}
	inline void		SetDim (Unt dim)	{ itsDim = dim;		}

	virtual vDbl GetUniforms(Unt nbDraws) = 0;

	virtual void SetSeed(unsigned long _seed) = 0;
	virtual void Skip(unsigned long length)	  = 0;

	template <GEN_GAUSS GAUSS_TYPE>
	void GetGaussians(vDbl & draws);

	template <GEN_GAUSS GAUSS_TYPE>
	arma::colvec GetCorrGaussians(const arma::mat & corr, vDbl& draws);

protected:
	Unt itsDim;
};

/*** supposing corr is at-least semi-definite ***/
template <GEN_GAUSS GAUSS_TYPE>
arma::colvec RandomGenerator::GetCorrGaussians(const arma::mat & corr, vDbl& draws)
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
	arma::mat tmpMat(corr.n_rows, corr.n_cols);

	if (corr.is_sympd())
	{
		tmpMat = arma::chol(corr, "lower");
	}
	else
	{
		tmpMat = arma::sqrtmat(corr);
	}
	arma::colvec armaDraws(arma::conv_to<arma::colvec>::from(draws));
	armaDraws = tmpMat * armaDraws;
	return armaDraws;
}

class MersenneTwister : public RandomGenerator
{
protected	:
	typedef std::shared_ptr<MersenneTwister> MrsPtr	;
public	:
	MersenneTwister(const std::shared_ptr<std::mt19937> eng, unsigned long _seed, Unt dim = 1)	: RandomGenerator(dim)
																								, itsEngine(eng)
																								, itsSeed(_seed)
																								, itsMin(itsEngine->min())
																								, itsMax(itsEngine->max())
	{
		if (0 == _seed) { itsSeed = 1; }
		itsEngine->seed(itsSeed);
	}

	MersenneTwister(const MrsPtr & rhs) : RandomGenerator(rhs->itsDim)
										, itsSeed(rhs->itsSeed)
										, itsEngine(rhs->itsEngine)
										, itsMin(rhs->itsMin)
										, itsMax(rhs->itsMax)
	{}

	virtual vDbl GetUniforms(Unt nbDraws);
	inline virtual void SetSeed(unsigned long _seed)	{ 0 == _seed ? itsSeed = 1 : itsSeed = _seed; }
	inline virtual void Skip(unsigned long length)		{ itsEngine->discard(length); }

private :
	std::shared_ptr<std::mt19937> itsEngine;
	unsigned long itsSeed;
	const double itsMin;
	const double itsMax;
};

