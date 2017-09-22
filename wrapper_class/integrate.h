#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>
#include "Double.h"


/**
* Evaluate a function u given as linear combination of shape function
* values in a single quadrature point
*
* \param[in] u \fk^3$ values, coefficients for the linear combination
* \param[in] phi \f$k$ values of shape functions in \f$k$
* quadrature points.
*/


template<int nphi, int nquad>
Double __attribute__ ((noinline)) integrate(Double u[nphi][nphi][nphi],
					    Double phi[nquad][nphi],
					    Double omega[nquad])
{
    Double integral;


    for (int q3 = 0; q3<nquad; ++q3)
	for (int i3 = 0; i3<nquad; ++i3)
	    for (int q2 = 0; q2<nquad; ++q2)
		for (int i2 = 0; i2<nphi; ++i2)
		    for (int q1 = 0; q1<nphi; ++q1)
			for (int i1 = 0; i1<nphi; ++i1)
			{
			   integral.operator+=((((((u[i1][i2][i3].operator*(phi[q1][i1])).operator*(phi[q2][i2])).operator*(
						    phi[q3][i3])).operator*(omega[q1])).operator*(omega[q2])).operator*(omega[q3]));

			}

    return integral;
}



template<int nphi, int nquad>
Double __attribute__ ((noinline)) integrate_fact(Double u[nphi][nphi][nphi],
                                                 Double phi[nquad][nphi],
                                                 Double omega[nquad])
{
    Double* integral = new Double[nphi];
    Double f3;

    for (int q = 0; q<nquad; ++q)
    {
	for (int i = 0; i<nphi; ++i)
	{
	    integral[i].operator+=(phi[q][i].operator*(omega[q]));

		for (int i3 = 0; i3<nphi; ++i3)
		{
		     Double f2;

		     for (int i2 = 0; i2<nphi; ++i2)
		     {
			Double f1;

			for (int i1 = 0; i1<nphi; ++i1)
			{
			    f1.operator+=(u[i1][i2][i3].operator*(integral[i1]));
			}

			f2.operator+=(f1.operator*(integral[i2]));
		     }

		     f3.operator+=(f2.operator*(integral[i3]));
		}
	}
    }
    return f3;

}
