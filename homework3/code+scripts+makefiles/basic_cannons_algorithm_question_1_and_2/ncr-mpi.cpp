#include <mpi.h>
extern "C++" int nCr_CPP( int n, int r );
int main( int argc, char *argv[ ] )
{
  MPI_Init( &argc, &argv );
  int rank,p;
  MPI_Comm_size( MPI_COMM_WORLD, &p );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  printf( "This is process %d out of %d!\n", p, rank );
  printf( "C( %d, %d ) = %d\n", 30, 15 + rank, nCr_CPP( 30, 15 + rank ) );
  MPI_Finalize( );
  return 0;
}
