CC=icpc
CFLAGS=-D 

all: 
	$(CC) $(CFLAGS) msize=16 -o a16 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript16
	$(CC) $(CFLAGS) msize=32 -o a32 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript32
	$(CC) $(CFLAGS)msize=64 -o a64 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript64
	$(CC) $(CFLAGS)msize=128 -o a128 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript128
	$(CC) $(CFLAGS)msize=256 -o a256 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript256
	$(CC) $(CFLAGS)msize=512 -o a512 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript512
	$(CC) $(CFLAGS)msize=1024 -o a1024 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript1024
	$(CC) $(CFLAGS)msize=2048 -o a2048 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript2048
	$(CC) $(CFLAGS)msize=4096 -o a4096 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript4096
	$(CC) $(CFLAGS)msize=8192 -o a8192 iter_mm_ikj_cilk_ijk.c
	sbatch itermmscript8192
		
clean:
	rm -rf a  core*
