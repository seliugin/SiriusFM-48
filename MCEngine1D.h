#pragma once

#include <cmath>
#include <utility>
#include <tuple>
#include <new>

namespace SiriusFM{
	template <typename Diffusion1D,
						typename AProvider,
						typename BProvider,
						typename AssetClassA,
						typename AssetClassB>	
	class MCEngine1D
	{
		private:
			long const m_maxL;//path length
			long const m_maxP;//path #
			double* const m_path;
			long m_L;
			long m_P;
		
		public:
			MCEngine1D(long a_maxL, long a_maxP):
				m_maxL(a_maxL),
				m_maxP(a_maxP),
				m_path(new double[m_maxL*m_maxP]),
				m_L(0),
				m_P(0)
			{
				if (m_maxL<=0 || m_maxP<=0)
					throw std::invalid_argument("maxL_P");
			}

		~MCEngine1D()
		{
			delete[] m_path;
		}

	
		MCEngine1D(MCEngine1D const&) = delete; //no copy constructor
		MCEngine1D& operator=(MCEngine1D const&) = delete; //no = 
		
		template <bool Is_RN>
		void simulate (time_t a_t0, //curr (pricing) time
								time_t a_T, //Exp time
								int a_tau_min, //time step in minutes
								long a_P,
								double a_s0,
								Diffusion1D const* a_diff,
								AProvider const* a_rateA,
								BProvider const* a_rateB,
								AssetClassA a_A,
								AssetClassB a_B
								//bool a_isRN //Risk-neutral
								);

		std::tuple<long, long, double const*>
		GetPath() const
		{
			return (m_L <= 0 || m_P <= 0)
			? std::make_tuple(0,0, nullptr)
			: std::make_tuple(m_L, m_P, m_path);
		}
};
}




