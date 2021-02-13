#pragma once
#include "IRP.h"
#include <iostream>
#include "Time.h"
#include <cmath>

namespace SiriusFM
{
	template <>
	class IRProvider<IRMode::Const>:
	{
		private:
			double m_IRs[CcyE::N];
		public:
			IRProvider(char const* a_file);
			
			//instanteneous continiously compounded interest rate
			double r(CcyE a_ccy, double a_t) const
			{
				return m_IRs[int(a_ccy)];
			};

			//Discount factor
			double DF(CcyE a_ccy, time_t a_t0, time_t a_t1)
			{
				return exp(-m_IRs[int(a_ccy)] * YearFracInt(a_t1-a_t0))
			}
	};

	//Alias
	using IRPConst = IRProvider<IRModeE::Const>;

}

