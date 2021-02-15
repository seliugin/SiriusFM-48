#pragma once

#include "Time.h"
#include <cmath>
#include <stdexcept>
#include <tuple>
#include <new>

namespace SiriusFM{
	template <typename Diffusion1D,
						typename AProvider,
						typename BProvider,
						typename AssetClassA,
						typename AssetClassB
						typename PathEvaluator>

	class MCEngine1D
	{
		private:
			long const m_maxL;//path length
			long const m_maxPM;//max path #
			double* const m_path;//stored path
			double* const m_ts; //TimeLine
		
		public:
			MCEngine1D(long a_maxL, long a_maxP):
				m_maxL(a_maxL),
				m_maxP(a_maxP),
				m_path(new double[m_maxL*m_maxP]),
				m_ts(new double[m_maxL])
			{
				if (m_maxL<=0 || m_maxPM<=0)
					throw std::invalid_argument("Bad maxL/PM");
				
				for (long l = 0; l < m_maxL, ++l)
				{
					m_ts[l] = 0;
					long lp = l * m_maxPM;
					for (long p = 0; p < m_maxPM; ++p)
						m_path[lp + p] = 0;
				}

			};


		~MCEngine1D()
		{
			delete[] m_path;
			delete[] m_ts;
		};

	
		MCEngine1D(MCEngine1D const&) = delete; //no copy constructor
		MCEngine1D& operator=(MCEngine1D const&) = delete; //no = 
		
		template <bool Is_RN>
		void simulate (time_t a_t0, //curr (pricing) time
								time_t a_T, //Exp time
								int a_tau_min, //time step in minutes
								long a_P,
								bool a_useTimerSeed,,
								Diffusion1D const* a_diff,
								AProvider const* a_rateA,
								BProvider const* a_rateB,
								AssetClassA a_A,
								AssetClassB a_B,
								PathEvaluator* a_pathEval
								//bool a_isRN //Risk-neutral
								);

		/*std::tuple<long, long, double const*>
		GetPath() const
		{
			return (m_L <= 0 || m_P <= 0)
			? std::make_tuple(0,0, nullptr)
			: std::make_tuple(m_L, m_P, m_path);
		}*/
};
}




