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
//Run: Perform Backward
//returns (Px, Delta, Gamma)

GridNOP1D_S3_RKC1::RunBI (
	Option <AssertClassA, AssertClassV> const* a_option, //option spec
	time_t a_t0, 					//pricing time
	//Grid Params:
	double a_S0, 					//S(t0) may differ from Diffusion
	long a_N, 						//# of S points
	int a_tauMins,				//Time step in minutes
	double a_UBSDF
):




};
}
