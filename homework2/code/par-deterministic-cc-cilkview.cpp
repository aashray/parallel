#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cilk/cilk.h>
#include<functional>
#include<time.h>
#include<vector>
#include<cilktools/cilkview.h>
using namespace std;
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
		cilk_for (int i = 1; i <= n/2; i++) {
			y[i] = x[2*i-1]+x[2*i];
		}
		int* z = (int*) malloc(sizeof(int) * (n/2 + 1));
		z = par_prefix_sum(y, n/2);
		cilk_for (int i = 1; i <= n; i++ ) {
			if (i == 1) s[1] = x[1];
			else if (i % 2 == 0) s[i] = z[i/2];
			else s[i] = z[(i-1)/2] + x[i];
		}
	}
	return s;
}

int* find_roots(int n, int* P, int* S){
	cilk_for (int v = 1; v <= n; v++){
		S[v] = P[v];
	}
	bool flag = true;
	while (flag == true){
		flag = false;
		cilk_for (int v = 1; v <= n; v++){
			S[v] = S[S[v]];
			if (S[v] != S[S[v]]) flag = true;
		}
	}
	return S;
}

int* optimized_find_roots(int n, int* P, int* S){
	/*vector <int> set;
	cilk_for (int v = 1; v <= n; v++){
                S[v] = P[v];
		set.push_back(v);
        }
        while (!set.empty()) {
		int s = set.size();
                cilk_for (int v = 0; v < s; v++){
                        S[set[v]] = S[S[set[v]]];
                        if (S[d[v]] == S[S[d[v]]]){
			} 
			//else done[v] = 1;
		}
		//set = temp;
		//temp.clear();
        }
        return S;*/
	cilk_for(int v = 1; v <= n; v++){
		S[v] = P[v];
		while (S[v] != S[S[v]]){
			S[v] = S[S[v]];
		}
	}
	return S;
	
}

int par_sum(int* x, int len){
	int* s = (int*) malloc(sizeof(int) * (n+1));
        if (n == 1) {
                s[1] = x[1];
        }
        else {
                int* y = (int*) malloc(sizeof(int) * (n/2 + 1));
                cilk_for (int i = 1; i <= n/2; i++) {
                        y[i] = x[2*i-1]+x[2*i];
                }
                int* z = (int*) malloc(sizeof(int) * (n/2 + 1));
                z = par_prefix_sum(y, n/2);
                cilk_for (int i = 1; i <= n; i++ ) {
                        if (i == 1) s[1] = x[1];
                        else if (i % 2 == 0) s[i] = z[i/2];
                        else s[i] = z[(i-1)/2] + x[i];
                }
        }
        return s[n];
}


int* par_deterministic_cc(int n, E* e, int* L, int m){
	
	if (m == 0) return L;
	int* l2h = (int*) malloc(sizeof(int) * (n+1));
	int* h2l = (int*) malloc(sizeof(int) * (n+1));
	int * S = (int*) malloc(sizeof(int) * (m+1));
	cilk_for (int v = 1; v <= n; v++){
		l2h[v] = 0;
		h2l[v] = 0;
	}
	cilk_for (int i = 1; i <= m; i++){
		if (e[i].u < e[i].v) l2h[e[i].u] = 1;
		else h2l[e[i].u] = 1;
	}
	int n1 = par_sum(l2h, n);
	int n2 = par_sum(h2l, n);
	cilk_for (int i = 1; i <= m; i++){
		if (n1 >= n2 && e[i].u < e[i].v) L[e[i].u] = e[i].v;
		else if (n1 >= n2 && e[i].v < e[i].u) L[e[i].v] = e[i].u;
		else if (n1 < n2 && e[i].u > e[i].v) L[e[i].u] = e[i].v;
		else if (n1 < n2 && e[i].v > e[i].u) L[e[i].v] = e[i].u;
	}
	L = optimized_find_roots(n,L,L);
	cilk_for (int i = 1; i <= m; i++){
		S[i] = (L[e[i].u] != L[e[i].v]) ? 1 : 0;
	}
	S = par_prefix_sum(S, m);
	E* F = (E*) malloc(sizeof(E) * (S[m]+1));
	cilk_for (int i =1; i <= m; i++){
		if (L[e[i].u] != L[e[i].v]){
			F[S[i]].u = L[e[i].u];
			F[S[i]].v = L[e[i].v];
		}
	}
	L = par_deterministic_cc(n, F, L, S[m]);
	return L;
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
	sort(size + 1, size + (n+1), greater<int>());
	printf("%d\n", count);
	for (int i = 1; i <= n; i++){
		if(size[i]!=0) printf("%d\n", size[i]);
	}

}

void print_input(E e[]) {
	//printf("No.of vertices: %d\n", n);
	/*for (int i = 1; i <= m; i++) {
		printf("%d-%d\n", e[i].u, e[i].v);
	}*/
	int* L = (int*) malloc(sizeof(int) * (n+1));
	cilk_for (int v = 1; v <= n; v++) {
		L[v] = v;
	}
	clock_t start, end;
  	double cpu_time_used;
	start = clock();
	cilkview_data_t d;
    	__cilkview_query(d);
	L = par_deterministic_cc(n, e, L, m);
	__cilkview_report(&d, NULL, "det-cc-cilkviewapi-v2", CV_REPORT_WRITE_TO_RESULTS);
	end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("CPU time used is : %f\n", cpu_time_used);
	print_output(L, n);
}

void take_input() {
	scanf("%d", &n);
	scanf("%d", &m);
	//E e[m+1];
	E* e = (E*) malloc(sizeof(E) * (m+1));
	for (int i = 1; i <= m; i++) {
		scanf("%d",&e[i].u);
		scanf("%d",&e[i].v);
	}
	print_input(e);
}

int main() {
	take_input();
	
}
