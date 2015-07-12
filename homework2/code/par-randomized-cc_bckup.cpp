#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<time.h>
int n; // # of vertices
int m; // # of edges

//edge struct
typedef struct{ 

	int u;
	int v;

}E;

int* par_prefix_sum(int* x, int n){

	int* s = (int*) malloc(sizeof(int) * (n+1)); 
	if (n == 1) {
		s[1] = x[1];
	}
	else {
		int* y = (int*) malloc(sizeof(int) * (n/2 + 1));
		for (int i = 1; i <= n/2; i++) {
			y[i] = x[2*i-1]+x[2*i];
		}
		int* z = (int*) malloc(sizeof(int) * (n/2 + 1));
		z = par_prefix_sum(y, n/2);
		for (int i = 1; i <= n; i++ ) {
			if (i == 1) s[1] = x[1];
			else if (i % 2 == 0) s[i] = z[i/2];
			else s[i] = z[(i-1)/2] + x[i];
		}
	}
	return s;
}


int* par_randomized_cc(int n, E* e, int* L, int m){
	if (m == 0) return L;
	int C[n+1];
	int* M = (int*) malloc(sizeof(int) * (n+1));
	//printf("malloced M\n");
	int* S = (int*) malloc(sizeof(int) * (m+1));
	//printf("malloced S\n");
	//srand(time(NULL));
	for (int v = 1; v <= n; v++) {
		C[v] = rand() % 2;
	}
	// 0 => head, 1=> tail
	for(int i = 1; i <= m; i++) {
		if(C[e[i].u] == 1 && C[e[i].v] == 0) {
			L[e[i].u] = L[e[i].v];
		}
	}
	for (int i = 1; i <= m; i++) {
		if (L[e[i].u] != L[e[i].v]) {
			S[i] = 1;
		} else {
			S[i] = 0;
		}
	}
	S = par_prefix_sum(S, m);
	E F[S[m]+1];
	for (int i =1; i <= m; i++){
		if (L[e[i].u] != L[e[i].v]){
			F[S[i]].u = L[e[i].u];
			F[S[i]].v = L[e[i].v];
		}
	}
	M = par_randomized_cc(n, F, L, S[m]);
	for (int i = 1; i <= m; i++) {
		if (e[i].v == L[e[i].u]){
			M[e[i].u] = M[e[i].v];
		}
	}
	free(S);
	return M;
}

void print_output(int L[], int n) {
	//printf("OUTPUT\n");
	/*for (int i = 1; i <= n; i++){
		printf("L[%d]=%d\n", i, L[i]);
	}*/
	//printf("\n\n\n");
	int count = 0, size[n+1];
	for (int i = 1; i <= n; i++){
		size[i]=0;
	}
	for (int i = 1; i <= n; i++){
		if(size[L[i]]==0) count++;
		size[L[i]]++;
	}
	std::sort(size + 1, size + (n+1));
	printf("%d\n", count);
	for (int i = 1; i <= n; i++){
		if(size[i]!=0) printf("%d\n", size[i]);
	}

}


void print_input(E e[]) {
	//printf("No.of vertices: %d\n", n);
	for (int i = 1; i <= m; i++) {
		printf("%d-%d\n", e[i].u, e[i].v);
	}
	int* L = (int*) malloc(sizeof(int) * (n+1));
	for (int v = 1; v <= n; v++) {
		L[v] = v;
	}
	//printf("L malloced\n");
	L = par_randomized_cc(n, e, L, m);
	print_output(L, n);
}

void take_input() {
	scanf("%d", &n);
	scanf("%d", &m);
	E e[m+1];
	for (int i = 1; i <= m; i++) {
		scanf("%d",&e[i].u);
		scanf("%d",&e[i].v);
	}
	print_input(e);
}

int main() {
	take_input();
	
}
