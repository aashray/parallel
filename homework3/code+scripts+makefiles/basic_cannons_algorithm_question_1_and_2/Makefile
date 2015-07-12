CC=icpc -m64 -fPIC -shared -o libncr.so ncr.cpp
CFLAGS=-D

all:
	#mpicxx mpi_matrix_replace.cpp -D M=10 -o mpi_matrix_size_2_10.out
	#mpicxx mpi_matrix_replace.cpp -D M=11 -o mpi_matrix_size_2_11.out
	#mpicxx mpi_matrix_replace.cpp -D M=12 -o mpi_matrix_size_2_12.out
	#mpicxx mpi_matrix_replace.cpp -D M=13 -o mpi_matrix_size_2_13.out
	#mpicxx mpi_matrix_replace.cpp -D M=14 -o mpi_matrix_size_2_14.out
	mpicxx mpi_matrix_replace_cilk.cpp -D M=10 -o mpi_matrix_size_cilk_2_10.out
	mpicxx mpi_matrix_replace_cilk.cpp -D M=11 -o mpi_matrix_size_cilk_2_11.out
	mpicxx mpi_matrix_replace_cilk.cpp -D M=12 -o mpi_matrix_size_cilk_2_12.out
	mpicxx mpi_matrix_replace_cilk.cpp -D M=13 -o mpi_matrix_size_cilk_2_13.out
	mpicxx mpi_matrix_replace_cilk.cpp -D M=14 -o mpi_matrix_size_cilk_2_14.out
clean:
	rm -rf a  core*
