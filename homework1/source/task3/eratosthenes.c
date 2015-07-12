#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define N 100
#include<time.h>
#include<cilk/cilk.h>
#include<math.h>
int main() {
	int pr[N];
	int urootN = (int)sqrt((double)N);
	pr[1] = 0;
	pr[2] = 1;
	cilk_for (int i = 3; i <= N; i++) {
		pr[i] = 1;
	}
	cilk_for (int i = 2; i <= urootN; i++) {
		if (pr[i]==1){
			cilk_for (int j = 2*i; j <= N; j += i) {
				pr[j] = 0;
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		printf("%d = %d\n", i, pr[i]);
	}
        return 0;
}
