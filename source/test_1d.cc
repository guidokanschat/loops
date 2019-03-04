#include "../include/all_points.h"

#include <likwid.h>

int main()
{
  LIKWID_MARKER_INIT;

  const unsigned int k=10;
  const unsigned int q=10;
  double u[k];
  double phi[k][q];
  double eval_points[q];

  for (unsigned int j=0; j<q; ++j)
    {
      phi[0][j] = 1.;
      for (unsigned int i=1; i<k; ++i)
        phi[i][j] = phi[i-1][j]*j/k;
    }

  double value = 0.;
  LIKWID_MARKER_START("foo");
  all_points<k,q>(u, phi, eval_points);
  LIKWID_MARKER_STOP("foo");
  LIKWID_MARKER_CLOSE;
}

