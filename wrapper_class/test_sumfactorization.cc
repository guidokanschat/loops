#include <iostream>
#include <cmath>
#include "all_points.h"
#include "Double.h"

int main()
{
    const unsigned int k=10;
    const unsigned int q=11;
    Double u[k][k][k];
    Double phi[k][q];
    Double eval_points[q][q][q];

    for (unsigned int j=0; j<q; ++j)
    {
	phi[0][j].value = 1.;
	for (unsigned int i=1; i<k; ++i)
	    phi[i][j].value = phi[i-1][j].value*j/k;
    }

    Double value_hilf;

    for (unsigned int i=0; i<1000; ++i)
    {
	#if FACTOR==0
	all_points<k,q>(u, phi, eval_points);
	#elif FACTOR==1
	all_points_fact<k,q>(u, phi, eval_points);
	#elif FACTOR==2
	all_points_sum_fact<k,q>(u, phi, eval_points);
	#else
	abort();
	#endif
	for (unsigned int q1=0; q1<q; ++q1)
	    for (unsigned int q2=0; q2<q; ++q2)
		for (unsigned int q3=0; q3<q; ++q3)
		    value_hilf.operator+=(eval_points[q1][q2][q3]);
     }

     std::cout << "Evaluate " << value_hilf.value << std::endl;
}
