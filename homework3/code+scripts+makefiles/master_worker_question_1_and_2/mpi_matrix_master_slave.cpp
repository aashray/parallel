#include<mpi.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
//#define M 13 // Define M at complie time, see makefile for details
#define N (1<<M)

using namespace std;

void printMatrix(int **a, int rows, int cols);

/* simple iterative matrix multiplication function */
void matrixMultiply (int size, int (*a), int (*b), int (*c)){
	for (int i = 0; i < size; i++){
		for (int k = 0; k < size; k++){
			for (int j = 0; j < size; j++){
				c[i*size+j] = c[i*size+j] + ( a[i*size+k] * b[k*size+j] );
			}
		}
	}
}

int main(int argc, char *argv[]) {
        
	MPI_Init( &argc, &argv );
        int rank,p;
        int n = N;
        int max = 10;
        int min = -10;
        //srand(time(NULL)); // Seed the time
        MPI_Comm_size(MPI_COMM_WORLD, &p);
        MPI_Comm_rank( MPI_COMM_WORLD, &rank );
       	int size = (int) (n / (sqrt(p)));
	int a[size][size], b[size][size], c[size][size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
				c[i][j] = 0;
	int aglob[n][n], bglob[n][n];
	int cglob[n][n];
	MPI_Status status;
	MPI_Request arequest = MPI_REQUEST_NULL;
	MPI_Request brequest = MPI_REQUEST_NULL;
	int tag=1234;
	
	// initial alignment
	int row = rank / sqrt (p);
	int rowsize = sqrt(p);
	int colsize = sqrt(p);
	int col = rank % colsize;

	clock_t begin, end;
	double time_spent;
	begin = clock();
	if (rank == 0) {
		// This is the master, need to generate the entire matrix here, then send appropriate parts to each processor. Send
		// Then need to collect the results back in the master with recv.
		//
		// Step 1. Generate complete matrix
		
			
			for (int i=0; i < n; i++){
                		for (int j=0; j < n; j++){
                        		aglob[i][j] = rand()%(max-min)+min;
                        		bglob[i][j] = rand()%(max-min)+min;
                        		//cglob[i][j] = 0;
					//printf("aglob[i][j] = %d\n",aglob[i][j]);
					//printf("bglob[i][j] = %d\n",bglob[i][j]);
                		}
        		}
			//MPI_Sendrecv_replace( &a, size*size, MPI_INT, ((proc + (rowsize-row)) % (rowsize)) + (row*rowsize), tag, ((proc+row) % rowsize) + (row*rowsize), tag, MPI_COMM_WORLD, &status);
			//MPI_Sendrecv_replace( &b, size*size, MPI_INT, (proc-(col*colsize) + p) % p, tag, ( proc + (col * colsize)) % p, tag, MPI_COMM_WORLD, &status);
		// Step 2.
	}
	        
	//printf("Size = %d, I am processor %d\n Matrix A: \n%d %d\n%d %d\nMatrix B:\n%d %d\n%d %d\n", size, rank, a[0][0], a[0][1], a[1][0], a[1][1], b[0][0], b[0][1], b[1][0], b[1][1]);
        MPI_Scatter(aglob, size*size, MPI_INT, a, size*size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(bglob, size*size, MPI_INT, b, size*size, MPI_INT, 0, MPI_COMM_WORLD);
	//printf("Size = %d, I am processor %d\n Matrix A: \n%d %d\n%d %d\nMatrix B:\n%d %d\n%d %d\n", size, rank, a[0][0], a[0][1], a[1][0], a[1][1], b[0][0], b[0][1], b[1][0], b[1][1]);
	MPI_Sendrecv_replace( &a, size*size, MPI_INT, ((rank + (rowsize-row)) % (rowsize)) + (row*rowsize), tag, ((rank+row) % rowsize) + (row*rowsize), tag, MPI_COMM_WORLD, &status);
	MPI_Sendrecv_replace( &b, size*size, MPI_INT, (rank-(col*colsize) + p) % p, tag, ( rank + (col * colsize)) % p, tag, MPI_COMM_WORLD, &status);

	//printf("After initial, Size = %d, I am processor %d\n Matrix A: \n%d %d\n%d %d\nMatrix B:\n%d %d\n%d %d\n", size, rank, a[0][0], a[0][1], a[1][0], a[1][1], b[0][0], b[0][1], b[1][0], b[1][1    ]);

	// initial alignment done, now mulptiply the matrices.
	matrixMultiply(size, (int*) a, (int*) b, (int *) c);
	
	//printf("After multiply, Size = %d, I am processor %d\n Matrix C: \n%d %d\n%d %d\n", size, rank, c[0][0], c[0][1], c[1][0], c[1][1]);
	
	for (int i = 0; i < (sqrt(p) - 1); i++) {
		
		//MPI_Isend(&a,size*size,MPI_INT,((rank + (rowsize-1)) % (rowsize)) + (row*rowsize),tag,MPI_COMM_WORLD, &arequest);
		//MPI_Irecv(&a,size*size,MPI_INT,(( rank+ 1) % rowsize) + (row*rowsize),tag,MPI_COMM_WORLD, &arequest);
		//MPI_Wait(&arequest, MPI_STATUS_IGNORE);
		MPI_Sendrecv_replace( &a, size*size, MPI_INT, ((rank + (rowsize-1)) % (rowsize)) + (row*rowsize), tag, (( rank+ 1) % rowsize) + (row*rowsize), tag, MPI_COMM_WORLD, &status);
		//MPI_Isend(&b,size*size,MPI_INT,(rank-(colsize) + p) % p, tag, MPI_COMM_WORLD, &brequest);
		//MPI_Irecv(&b,size*size,MPI_INT, ( rank + (colsize)) % p, tag, MPI_COMM_WORLD, &brequest);
		//MPI_Wait(&brequest, MPI_STATUS_IGNORE);
		MPI_Sendrecv_replace( &b, size*size, MPI_INT, (rank-(colsize) + p) % p, tag, ( rank + (colsize)) % p, tag, MPI_COMM_WORLD, &status);
		matrixMultiply(size, (int*) a, (int*) b, (int *) c);
	}
	//int *finalc = NULL;
	//if (rank ==0) finalc = &(cglob[0][0]);
	MPI_Gather(&c, size*size, MPI_INT, rank==0 ? &cglob : NULL, size*size, MPI_INT, 0, MPI_COMM_WORLD);
	
	//printf("After everything, Size = %d, I am processor %d\n Matrix C: \n%d %d\n%d %d\n", size, rank, c[0][0], c[0][1], c[1][0], c[1][1]);
	//if (rank ==0) printf("After everything, Size = %d, I am processor %d\n Matrix C: \n%d %d\n%d %d\n", size, rank, cglob[0][0], cglob[0][1], cglob[1][0], cglob[1][1]);	

	end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Elapsed: %f seconds\n", time_spent);
	
	MPI_Finalize();
        return 0;	
}
void printMatrix (int *a, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                        printf("%d ", a[i*cols + j]);
                }
                printf("\n");
        }
}

