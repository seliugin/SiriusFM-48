#pragma once
#include "MCEngine1D.h"
#include <cassert>
#include <random>
#include "Time.h"


namespace SiriusFM
{
	template <typename Diffusion1D,
						typename AProvider,
						typename BProvider,
						typename AssetClassA,
						typename AssetClassB>	
	
	template <bool Is_RN>
	inline void MCEngine1D <Diffusion1D, AProvider, BProvider, AssetClassA, AssetClassB>
	::simulate	
							(time_t a_t0,
							time_t a_T,
							int a_tau_min,
							long a_P,
							double a_s0,
							Diffusion1D const* a_diff,
							AProvider const* a_rateA,
							BProvider const* a_rateB,
							AssetClassA a_A,
							AssetClassB a_B)
							//bool a_isRN)
	{
		//checks
		assert (a_diff != nullptr &&
		a_rateA != nullptr &&
		a_rateB != nullptr &&
		a_A != AssetClassA::UNDEFINED &&
		a_B != AssetClassB::UNDEFINED &&
		a_t0 <= a_T &&
		a_tau_min > 0);
		
		time_t T_sec = a_T - a_t0;
		time_t tau_sec = a_tau_min*60;
		
		long L_ints = (T_sec % tau_sec == 0) ? T_sec / tau_sec : T_sec / tau_sec + 1; //# of the intervals
		
		double tau = YearFrac(tau_sec);
		double tlast = (T_sec % tau_sec == 0) ? tau : YearFrac(T_sec - (L_ints - 1)*tau_sec);
		assert (tlast>=0 && tlast <= tau);
		
		long L = L_ints + 1; //# of points
		assert (L>=2);
		
		double y0 = YearFrac(a_t0);
		//double yT = YearFrac(a_T);
		//double tau = double (a_tau_min) / (365.25*1440.0); //sec in 1 interval
		//long L = long(ceil((yT-y0) / tau))+1; //path lenght
		long P = 2*a_P; //antithetic variable
		
		if (L*P >m_maxL*m_maxP)
			throw std::invalid_argument("path length over");
		
		//generate normal distribution
		std::normal_distribution<> N01(0,1);
		std::mt19937_64 U;

		double stau = sqrt(tau);
		double slast = sqrt(tlast);
		assert (slast<= stau && slast>=0);
		


		for (long p = 0; p<a_P; ++p)
		{
			//create pathes #p
			double* path0 = m_path + 2*p*L;
			double* path1 = path0 + L;
			double y = y0;

			path0[0] = a_s0;
			path1[0] = a_s0;
			
			double sp0 = a_s0; //previous point
			double sp1 = a_s0;
			
			for (long l = 1; l < L; ++l)
			{
				//compute trend
				double mu0 = 0.0;
				double mu1=0.0;
				if (Is_RN) 
				{//risk-neutral case
					double delta_r = a_rateB -> r(a_B, y) - a_rateA -> r(a_A, y);
					mu0 = delta_r * sp0;
					mu1 = delta_r*sp1;
				}
				else
				{
					mu0 = a_diff->mu(sp0, y);
					mu1 = a_diff->mu(sp1, y);
				}

				//compute volatility
				double sigma0 = a_diff->sigma(sp0, y);
				double sigma1 = a_diff->sigma(sp1, y);
				
				//generate point related to distr
				double Z = N01(U);
				double sn0, sn1; //current point
				
				if (l == L-1) //check for last interval
				{
					sn0 = sp0 + mu0 * tlast + sigma0 * Z * stau;
					sn1 = sp1 + mu1 * tlast + sigma1 * Z * stau;
				}
				else //generic case
				{
					sn0 = sp0 + mu0 * tau + sigma0 * Z * stau;
			    sn1 = sp1 + mu1 * tau + sigma1 * Z * stau;                                                		
				}
				
				//add to pathes
				path0[l] = sn0;
				path1[l] = sn1;
				
				//renew prev point
				sp0 = sn0;
				sp1 = sn1;
			}
		}
		m_L = L;
		m_P = P;
	};
}







