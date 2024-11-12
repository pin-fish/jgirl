#include<stdio.h>
#include<stdlib.h>

#define int long long
signed main(){
    int N, org_sum = 0;
    scanf("%lld", &N);
    int A[N], A_t[N];
    for(int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
        org_sum += A[i];
        A_t[i] = A[i];
    }

    int *total = (int*)calloc(32, sizeof(int));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < 32; j++) {
            total[j] += A_t[i] & 1;
            A_t[i] >>= 1;
        }
    }

    int X[N];
    for(int i = 0; i < N-2; i++) {
        X[i] = A[i] ^ A[i+1] ^ A[i+2];
    }

    int max_sum = org_sum;
    for(int i = 0; i < N-2; i++) {
        int sum = org_sum;
        for(int j = 0; j < 32; j++) {
            if (X[i] & 1) {
                sum -= total[j] << j;
                sum += (N - total[j]) << j;
            }
            X[i] >>= 1;
        }
        if (sum > max_sum) max_sum = sum;
    }
    printf("%lld", max_sum);
}