#include "utilities.h"

double serial_dot (double *x, double *y, long n)
{
  double dp;

  /* code needed here */

  //#ifndef BLAS                                                                                                                                                                                                                                                                                            
  long i;
  //#endif                                                                                                                                                                                                                                                                                                  

    //#ifdef BLAS                                                                                                                                                                                                                                                                                           
    //dp = cblas_ddot(n, x, l, y, 1);                                                                                                                                                                                                                                                                       
  //#else                                                                                                                                                                                                                                                                                                   
  dp = 0.0;
  for (i = 0; i < n; i++) {
    dp += x[i] * y[i];
  }
    //#endif                                                                                                                                                                                                                                                                                                

  return dp;
}

double parallel_dot(double *l_x, double *l_y, long l_n, MPI_Comm comm) {

  double l_dot=0.0;
  double dot=0.0;

  /* code needed here */

  l_dot = serial_dot(l_x, l_y, l_n);

#ifdef PARALLEL

  MPI_Allreduce(&l_dot, &dot, 1, MPI_DOUBLE, MPI_SUM, comm);
#else
  dot = l_dot
#endif
  return dot;

}

double parallel_norm2 (double *l_x, long l_n, MPI_Comm comm) {

  /* code needed here */
  double norm = 0.0;
  norm = sqrt(parallel_dot(l_x, l_x, l_n, comm));

  return norm;
}





