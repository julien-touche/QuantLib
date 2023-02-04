#pragma once

/*** Implements the Beaslery - Springer - Moro algorithm to compute
approximation of inverse of the cumulative standard gaussian distribution ***/  
double InvCdfNrm(const double& x);

/*** Computes standard gaussian cumulatve distribution function with erf ***/
double CdfNrm	(const double& x);

/*** Computes density probability of standard gaussian distribution ***/
double PdfNrm	(const double& x);

