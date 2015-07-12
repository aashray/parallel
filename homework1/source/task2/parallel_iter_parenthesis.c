#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define msize 4096
#include<time.h>
#include<algorithm>
#include<cilk/cilk.h>
void printMatrix(int c[][msize+1], int size){
        for (int i = 1; i <= size; i++) {
                for (int j = 1; j <= size; j++) {
                        printf("%d ", c[i][j]);
                }
                printf("\n");
        }
}
int main() {
        int c[msize+1][msize+1];
        for (int i = 1; i <= msize; i++) {
                for (int j = 1; j <= msize; j++) {
                        if (i == (j - 1)){
                                c[i][j] = 1;//rand() % 10;
                        }
                        else c[i][j] = 100;;
                }
        }
        //printMatrix(c, msize);
        //printf("\n-----result--\n");
        // algorithm

        /*for (int i = 1; i <= msize - 1; i++) {
                for (int j = i + 2; j <= msize; j++) {
                        for (int k = i; k <= j; k++) {
                                c[i][j] = std::min(c[i][j], c[i][k] + c[k][j]);
                        }
                }
        }*/
	clock_t start, end;
        double cpu_time_used;
	start = clock();
        for (int d = 2; d <= msize-1; d++){
                cilk_for (int i = 1; i <= msize-d; i++){
                        int j = d + i;
                        for (int k = i; k <= j; k++){
                                c[i][j] = std::min(c[i][j], c[i][k] + c[k][j]);
                        }
                }
        }
	end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("CPU time used : %f\n", cpu_time_used);
        //printMatrix(c, msize);
        return 0;
}
