#include <iostream>
#include <cmath>
#include "Double.h"

/**
* Evaluate a function u given as linear combination of shape function
* values in all quadrature points. This is the naive way not using the
* tensor structure at all.
*
* \param[in] u \fk^3$ values, coefficients for the linear combination
* \param[in] phi \f$k\cdot q$ values of shape functions quadrature points.
*/


template<int k, int q>
void __attribute__ ((noinline)) all_points(Double u[k][k][k],
                                           Double phi[k][q],
                                           Double return_value[q][q][q])
{
    for (int q1=0; q1<q; ++q1)
	for (int q2=0; q2<q; ++q2)
	    for (int q3=0; q3<q; ++q3)
	    {
		Double f;

		for (int i3 = 0; i3<k; ++i3)
		    for (int i2 = 0; i2<k; ++i2)
			for (int i1 = 0; i1<k; ++i1)
			    f.operator+=(((u[i1][i2][i3].operator*(phi[i1][q1])).operator*(phi[i2][q2])).operator*(phi[i3][q3]));
			    return_value[q1][q2][q3] = f;
	    }
}



/**
* Evaluate a function u given as linear combination of shape function
* values in all quadrature points. Here, we use the tensor structure to
* move invariants out of the loops.
*
* \param[in] u \fk^3$ values, coefficients for the linear combination
* \param[in] phi \f$k\cdot q$ values of shape functions quadrature points.
*/


template<int k, int q>
void __attribute__ ((noinline)) all_points_fact(Double u[k][k][k],
                                                Double phi[k][q],
                                                Double return_value[q][q][q])
{
    for (int q1=0; q1<q; ++q1)
	for (int q2=0; q2<q; ++q2)
	    for (int q3=0; q3<q; ++q3)
	    {
		Double f3;

		for (int i3 = 0; i3<k; ++i3)
		{
		    Double f2;

		    for (int i2 = 0; i2<k; ++i2)
		    {
			Double f1;

			for (int i1 = 0; i1<k; ++i1)
			    f1.operator+=(u[i1][i2][i3].operator*(phi[i1][q1]));
			    f2.operator+=(f1.operator*(phi[i2][q2]));
  		    }

		    f3.operator+=(f2.operator*(phi[i3][q3]));
		}

		return_value[q1][q2][q3] = f3;
	    }
}



/**
* Evaluate a function u given as linear combination of shape function
* values in all quadrature points. This is sum factorization.
*
* \param[in] u \fk^3$ values, coefficients for the linear combination
* \param[in] phi \f$k\cdot q$ values of shape functions quadrature points.
*/


template<int k, int q>
void __attribute__ ((noinline)) all_points_sum_fact(Double u[k][k][k],
                                                    Double phi[k][q],
                                                    Double return_value[q][q][q])
{
    Double temp1[k][k][q] {};
    for (int i1=0; i1<k; ++i1)
	for (int i2=0; i2<k; ++i2)
	    for (int q3=0; q3<q; ++q3)
		for (int i3=0; i3<k; ++i3)
		    temp1[i1][i2][q3].operator+=(u[i1][i2][i3].operator*(phi[i3][q3]));
		    Double temp2[k][q][q] {};

		    for (int i1=0; i1<k; ++i1)
			for (int q3=0; q3<q; ++q3)
			    for (int q2=0; q2<q; ++q2)
				for (int i2=0; i2<k; ++i2)
				    temp2[i1][q2][q3].operator+=(temp1[i1][i2][q3].operator*(phi[i2][q2]));

				    for (int q2=0; q2<q; ++q2)
					for (int q3=0; q3<q; ++q3)
					    for (int q1=0; q1<q; ++q1)
						for (int i1=0; i1<k; ++i1)
    return_value[q1][q2][q3].operator+=(temp2[i1][q2][q3].operator*(phi[i1][q1]));
}
