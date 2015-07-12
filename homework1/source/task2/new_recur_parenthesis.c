#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<limits.h>
#include<time.h>
#include<cilk/cilk.h>
#define M 13
#define N (1<<M)
int c[N+1][N+1];
clock_t start, end;
double cpu_time_used;
void set_rand() {
        for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                        if (i == j-1){
                                c[i][j] = 1;//rand() % 10;
                        }
                        else c[i][j] = 100;
                }
        }
}

void printMatrix() {
         for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                        printf("%d ", c[i][j]);
                }
                printf("\n");
        }
}
void Cpar(int xtopleftX, int xtopleftY, int utopleftX, int utopleftY, int vtopleftX, int vtopleftY, int size, int base) {
	if (size <= base){
		//c[xtopleftX][xtopleftY] = std::min(c[xtopleftX][xtopleftY], c[utopleftX][utopleftY]+c[vtopleftX][vtopleftY]); 
		for (int i = 1; i <= size - 1; i++){
			for (int j = i+2; j<= size; j++) {
				for (int k = i; k <= j; k++) {
					c[i][j] = std::min(c[i][j], c[i][k]+c[k][j]);
				}
			}
		}
	 } else {
		cilk_spawn Cpar(xtopleftX, xtopleftY, utopleftX, utopleftY, vtopleftX, vtopleftY, size/2, base);
                cilk_spawn Cpar(xtopleftX, xtopleftY+size/2, utopleftX, utopleftY, vtopleftX, vtopleftY+size/2, size/2, base);
                cilk_spawn Cpar(xtopleftX+size/2, xtopleftY, utopleftX+size/2, utopleftY, vtopleftX, vtopleftY, size/2, base);
                Cpar(xtopleftX+size/2, xtopleftY+size/2, utopleftX+size/2, utopleftY, vtopleftX, vtopleftY+size/2, size/2, base);
		cilk_sync;
                cilk_spawn Cpar(xtopleftX, xtopleftY, utopleftX, utopleftY+size/2, vtopleftX+size/2, vtopleftY, size/2, base);
                cilk_spawn Cpar(xtopleftX, xtopleftY+size/2, utopleftX, utopleftY+size/2, vtopleftX+size/2, vtopleftY+size/2, size/2, base);
                cilk_spawn Cpar(xtopleftX+size/2, xtopleftY, utopleftX+size/2, utopleftY+size/2, vtopleftX+size/2, vtopleftY, size/2, base);
                Cpar(xtopleftX+size/2, xtopleftY+size/2, utopleftX+size/2, utopleftY+size/2, vtopleftX+size/2, vtopleftY+size/2, size/2, base);	
		cilk_sync;
	}
}
void Bpar(int xtopleftX, int xtopleftY, int utopleftX, int utopleftY, int vtopleftX, int vtopleftY, int size, int base) {
	if (size <= base) {
		//c[xtopleftX][xtopleftY] = std::min(c[xtopleftX][xtopleftY], c[utopleftX][utopleftY]+c[vtopleftX][vtopleftY]); 
		for (int i = 1; i<= size - 1; i++){
			for (int j = i+2; j<= size; j++) {
				for (int k = i; k <= j; k++) {
					c[i][j] = std::min(c[i][j], c[i][k]+c[k][j]);
				}
			}
		}
	} else {
		Bpar(xtopleftX  + size/2, xtopleftY, utopleftX+size/2, utopleftY+size/2, vtopleftX, vtopleftY, size/2, base);

                cilk_spawn Cpar(xtopleftX, xtopleftY, utopleftX, utopleftY+size/2, xtopleftX  + size/2, xtopleftY, size/2, base);
                Cpar(xtopleftX+size/2, xtopleftY+size/2, xtopleftX  + size/2, xtopleftY, vtopleftX, vtopleftY+size/2, size/2, base);
		cilk_sync;
                cilk_spawn Bpar(xtopleftX, xtopleftY, utopleftX, utopleftY, vtopleftX, vtopleftY, size/2, base);
                Bpar(xtopleftX+size/2, xtopleftY+size/2, utopleftX+size/2, utopleftY+size/2, vtopleftX+size/2, vtopleftY+size/2, size/2, base);
		cilk_sync;
                Cpar(xtopleftX, xtopleftY+size/2, utopleftX, utopleftY+size/2, xtopleftX+size/2, xtopleftY+size/2, size/2, base);
                Cpar(xtopleftX, xtopleftY+size/2, xtopleftX, xtopleftY, vtopleftX, vtopleftY+size/2, size/2, base);

                Bpar(xtopleftX, xtopleftY+size/2, utopleftX, utopleftY, vtopleftX+size/2, vtopleftY+size/2, size/2, base);
	}
}
void Apar(int xtopleftX, int xtopleftY, int size, int base) {
	if (size > 1) {
                //printf("Apar - %d,%d,%d,%d\n", xtopleftX, xtopleftY, size, base);
                cilk_spawn Apar(xtopleftX, xtopleftY, size / 2, base);
                Apar(xtopleftX  + size / 2, xtopleftY  + size/2, size / 2, base);
                cilk_sync;
		Bpar(xtopleftX, xtopleftY+size/2, xtopleftX, xtopleftY, xtopleftX  + size/2, xtopleftY  + size/2, size/2, base);
        }
}
int main() {
        set_rand();
        //printMatrix();
	int base = 128;
	for (int n = 16; n <=8192; n=n*2) {
		//printf("\nN = %d", N);
		start = clock();
        	Apar(1, 1, n, base);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        	printf("CPU time used for size = %d with base_case = %d is : %f\n ", n, base, cpu_time_used);
	}

        //printMatrix();
        return 0;
}
