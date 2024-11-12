#include<stdio.h>
#include<stdlib.h>

#define int long long
signed main(){
    int N;
    scanf("%lld", &N);
    int A[N], A_t[N];
    for(int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
        A_t[i] = A[i];
    }
    int *total = (int*)calloc(32, sizeof(int));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < 32; j++) {
            total[j] += A_t[i] & 1;
            A_t[i] >>= 1;
        }
    }

    int x_bit[32];
    int half;
    half = N / 2;

    for(int i = 0; i < 32; i++) {
        if (total[i] > half) x_bit[i] = 1;
        else x_bit[i] = 0; 
    }
    
    int x = 0;
    for(int i = 31; i >= 0; i--) {
        x = x * 2 + x_bit[i];
    }
    printf("%lld\n", x);

    int sum = 0;
    for(int i = 0; i < N; i++) {
        sum += x ^ A[i];
    }
    printf("%lld", sum);

}