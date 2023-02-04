#include "RandomGenerator.h"
#include <iostream>

int main()
{
	unsigned long initSeed = 1;
	Unt dim = 2;
	std::shared_ptr<std::mt19937> eng(new std::mt19937);
	MersenneTwister mtEng(eng, initSeed, dim);
	vDbl gaussians(dim);
	mtEng.GetGaussians<INVERSE>(gaussians);
	std::cout << gaussians[0] << ", " << gaussians[1] << std::endl;
};