CC=icpc
CFLAGS=-D msize=8192

all:
	number=1 ; while [[ $$number -le 32 ]] ; do \
        	echo $$number ; \
		export CILK_NWORKERS=$$number ; \
		$(CC) $(CFLAGS) -o a1 iter_mm_ikj_cilk_i.c ; \
		sbatch itermmscript1 ; \
		((number = number + 1)) ; \
	done	
clean:
	rm -rf a  core*
