//===========================================================================//
// 						Grid Pricer for Non IR Options for 1D Diffusion, 							 //
// using 3 point Stencils and 1st-order Runge-Kutta_Chebyshev Time Marshallig//
//===========================================================================//

//Non IR mean that
// (1) Low S bound is 0
// (2) RateA, RateB do not depend on S
// (3) Not suitable for very long TTE
namespace SiriusFM
{
template
<
	typename Diffusion1D, typename AProvider, typename BProvider, 
	typename AssetClassA, typename AssetClassB
>
class GridNOP1d_S3_RKC1
{
	private:
		long m_maxM; //max # of t points
		long m_maxN; //max # of S points
		double* const m_grid; //2D grid as 1D array
		double* const m_ts; //timeline

	public:
		//Non def C-or
		GridNOP1D_S3_RKC1 (long a_maxM,long a_maxN)
		: m_maxM(a_maxM),
			m_maxN(a_maxN),
			m_grid(new double [m_maxN * m_maxN])(,
			m_ts (new double [m_maxM])
		{}
		~	GridNOP1D_S3_RKC1()
		{
			delete[] (m_grid);
			delete[] (m_ts);
			m_grid = nullptr;
			m_ts = nullptr;
		}
		//Run: Perform Backward
		//returns (Px, Delta, Gamma)

		void RunBI (
			Option <AssertClassA, AssertClassV> const* a_option, //option spec
			time_t a_t0, 					//pricing time
			//Grid Params:
			double a_S0, 					//S(t0) may differ from Diffusion
			long a_N, 						//# of S points
			double a_UVSDF,				//StDevs for upper boundary
			int a_tauMins = 15  	//Time step in minutes
		):




};
}
