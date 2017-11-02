#include <iostream>
#include <cmath>
#include "point.h"
#include "integrate.h"
#include "Double.h"


int main()
{
    const unsigned int k = 2;

    Double u[k][k][k];
    Double phi[k][k];
    Double omega[k];

    for (unsigned int j=0; j<k; ++j)
    {
	double x = 1.*j/(k-1);
	omega[j].value = 1./k;
	phi[0][j].value = 1.;
	for (unsigned int i=1; i<k; ++i)
	    phi[j][i].value = phi[i-1][j].value*j/k;
    }

    Double point_val;
    Double integral;


    for (unsigned int i=0; i<1000; ++i)
    {
	#ifndef FACTOR
	point_val.operator+=(point<k>(u, phi[1]));
	integral.operator+=(integrate<k,k>(u, phi, omega));
	#else
	point_val.operator+=(point_fact<k>(u, phi[1]));
	integral.operator+=(integrate_fact<k,k>(u, phi, omega));
	#endif
    }

    std::cout << "Evaluate " << point_val.value << ' ' << integral.value << std::endl;

}
