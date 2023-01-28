#define _USE_MATH_DEFINES

#include "Distributions.h"
#include <cmath>

vDbl a({ 2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637 });
vDbl b({ -8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833 });
vDbl c({ 0.3374754822726147, 0.9761690190917186, 0.1607979714918209, 0.0276438810333863, 0.0038405729373609, 0.0003951896511919, 0.0000321767881768, 0.0000002888167364, 0.0000003960315187 });

double InvCdfNrm(const double& x)
{								
	double res(0.0);

	if (x > 0.5)
	{
		if (x < 0.92)
		{
			double den(1.0);
			for (Unt i = 0; i < b.size(); ++i)
			{
				den += b[i] * pow(x - 0.5, 2 * i);
			}
			for (Unt i = 0; i < a.size(); ++i)
			{
				res += a[i] * pow(x - 0.5, 2 * i + 1);
			}
			res /= den;

		}
		else
		{
			for (Unt i = 0; i < c.size(); ++i)
			{
				res += c[i] * pow(log(-(log(1 - x))), i);
			}
		}

	}
	else
	{
		res = -InvCdfNrm(1.0 - x);
	}
	return res;
}

double CdfNrm(const double& x)
{
	return 0.5 * (erf(x / sqrt(2.0)) + 1.0);
}

double PdfNrm(const double& x)
{
	return exp(-x * x / 2.0) / sqrt(2.0 * M_PI);
}