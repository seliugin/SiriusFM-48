//GBM

#include <iostream>
#include "DiffusionGBM.h"
#include "IRProviderConst.h"
#include "MCEngine1D.hpp"


using namespace SiriusFM;
using namespace std;

int main(int argc, char* argv[]) //mu, sigma, s_0, T days, tau_min, P
{
	if (argc != 7)
	{
		cerr << "PARAMS : mu, sigma, s_0, T days, tau, P" <<endl;
		return 1;
	}

	double mu = atof(argv[1]); 
	double sigma = atof(argv[2]);
	double s0 = atof(argv[3]);
	double T_days = atof(argv[4]);
	double tau_min = atof(argv[5]);
	double P = atof(argv[6]);

	CcyE ccyA = CcyE::USD;
	CcyE ccyB = ccyA;

	IRProvider<IRModeE::Const> irp(nullptr);
	DiffusionGBM diff(mu, sigma);
	MCEngine1D <decltype(diff),
							decltype(irp),
							decltype(irp),
							decltype(ccyA), decltype(ccyB)>
							mce	(20'000, 20'000); //400 mln entities
	time_t t0 = time(nullptr);
	time_t T = t0+T_days*86400;
	double Ty = double(T_days) / 365.25;	

	mce.simulate <false> (t0, T, tau_min, s0, P, &diff, &irp, &irp, ccyA, ccyB);
	
	//analyze results
	auto res = mce.GetPath();
	long L1 = get<0>(res);
	long P1 = get<1>(res);
	double const * paths = get<2>(res);
	
	//compute EXPValue Log s_T and Variance
	double EST = 0.0;
	double EST2 = 0.0;
	
	int NVP = 0; //# of value paths
	for (int p = 0; p < P1; ++p)
	{
		double const* path_p = paths + p * L1;
		double sT = path_p[L1-1];
		if (sT <= 0.0)
			continue;
		++NVP;
		double RT = log(sT / s0);
		EST += RT; 
		EST += RT * RT;
	}//end p loop
	
	assert (NVP > 0);
	EST /= double (NVP); //(mu - sigma^2/2)
	
	double VarST = (EST2 - EST*EST*double(NVP)) / double (NVP - 1);	//sigma^2 T
	
	double sigma2E = VarST / Ty;
	double muE = (EST + VarST / 2.0) /Ty;
	
	cout << "mu = " <<mu<<", muE = "<<muE<<endl;
	cout << "sigma2 = "<<sigma*sigma<<", sigma2E = "<<sigma2E<<endl;
}


