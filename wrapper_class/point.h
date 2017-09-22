#include <iostream>
#include <cmath>
#include "Double.h"

/**
* Evaluate a function u given as linear combination of shape function
* values in a single quadrature point
*
* \param[in] u \fk^3$ values, coefficients for the linear combination
* \param[in] phi \f$k$ values of shape functions in a single
* quadrature point.
*/


template<int k>
Double __attribute__ ((noinline)) point(Double u[k][k][k], Double phi[k])
{
    Double f;

    for (int i3 = 0; i3<k; ++i3)
	for (int i2 = 0; i2<k; ++i2)
	    for (int i1 = 0; i1<k; ++i1)
	    {
		f.operator+=(((u[i1][i2][i3].operator*(phi[i1])).operator*(phi[i2])).operator*(phi[i3]));	
	    }
		
    return f;
}



template<int k>
Double __attribute__ ((noinline)) point_fact(Double u[k][k][k], Double phi[k])
{
    Double f3;

    for (int i3 = 0; i3<k; ++i3)
    { 
	Double f2;

	for (int i2 = 0; i2<k; ++i2)
	{

	  do 
	  {	
	    Double f1;

	    for (int i1 = 0; i1<k; ++i1)
	    {
		f1.operator+=(u[i1][i2][i3].operator*(phi[i1]));
	    }

	    f2.operator+=(f1.operator*(phi[i2]));
	  }
	  while(NULL);
	}

	f3.operator+=(f2.operator*(phi[i3]));
    }

    return f3;
}
