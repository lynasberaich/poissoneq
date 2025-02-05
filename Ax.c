#include "Ax.h"

void Ax(double *l_v, double *l_u, long l_n, long l_N, long N,
        int id, int idleft, int idright, int np, MPI_Comm comm,
        double *gl, double *gr) {

  long i, l_j;
  double tmp;
  MPI_Status status;


  for(l_j = 1; l_j < l_N-1; l_j++) { //Block A                                                                                                                                                                                
    for (i = 0; i < N; i++) {
      tmp  = 4.0 * l_u[i   + N*  l_j   ];
      if (l_j >     0) tmp -= l_u[i   + N* (l_j-1)];
      if (i   >     0) tmp -= l_u[i-1 + N*  l_j   ];
      if (i   <   N-1) tmp -= l_u[i+1 + N*  l_j   ];
      if (l_j < l_N-1) tmp -= l_u[i   + N* (l_j+1)];
      l_v[i+N*l_j] = tmp;
    }
  }


  if (id%2 == 0) { //Block D                                                                                                                                                                                                  
    MPI_Recv(gl,                N, MPI_DOUBLE, idleft,  1, comm, &status);
    MPI_Recv(gr,                N, MPI_DOUBLE, idright, 2, comm, &status);
    MPI_Send(&(l_u[N*l_N - N]), N, MPI_DOUBLE, idright, 1, comm         );
    MPI_Send(&(l_u[    0    ]), N, MPI_DOUBLE, idleft,  2, comm         );
  } else {
    MPI_Send(&(l_u[N*l_N - N]), N, MPI_DOUBLE, idright, 1, comm         );
    MPI_Send(&(l_u[    0    ]), N, MPI_DOUBLE, idleft,  2, comm         );
    MPI_Recv(gl,                N, MPI_DOUBLE, idleft,  1, comm, &status);
    MPI_Recv(gr,                N, MPI_DOUBLE, idright, 2, comm, &status);
  }


  l_j = 0;
  for (i = 0; i < N; i++) { //Block B                                                                                                                                                                                         
    tmp = 4.0 * l_u[i     + N*  l_j     ];
    if (id  >     0)  tmp -=   gl[i];
    if (i   >     0)  tmp -=  l_u[i-1   + N*  l_j     ];
    if (i   <   N-1)  tmp -=  l_u[i+1   + N*  l_j     ];
    if (l_j < l_N-1)  tmp -=  l_u[i     + N* (l_j + 1)];
    l_v[i + N * l_j] = tmp;
  }




  l_j = l_N -1;
  for (i = 0; i < N; i++) { //Block C                                                                                                                                                                                         
    tmp = 4.0 * l_u[i   + N*  l_j   ];
    if (l_j >     0 )  tmp -= l_u[i   + N* (l_j-1)];
    if (i   >     0 )  tmp -= l_u[i-1 + N*  l_j   ];
    if (i   <   N-1 )  tmp -= l_u[i+1 + N*  l_j   ];
    if (id  <   np-1)  tmp -= gr[i];
    l_v[i + N* l_j] = tmp;
  }


}

