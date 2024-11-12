#include<stdio.h>
#include<stdlib.h>
#define int long long

signed main(){
    int N, k;
    scanf("%llu %llu", &N, &k);
    int K1 = 0;
    for(int i = 0; i < k; i++) {
        K1 += 1 << i;
    }

    while(N--) {
        int a;
        scanf("%llu", &a);
        int *bit = (int*)calloc(64, sizeof(int));
        for(int i = 0; i < 64 ; i++) {
            bit[i] = a & K1;
            a >>= k;
        }
        /*
        for(int i = 63; i >= 0; i--) {
            printf("%llu ", bit[i]);
        }
        printf("\n");
        */
        for(int i = 0; i < 16; i+=2) {
            int temp = bit[i];
            bit[i] = bit[i+1];
            bit[i+1] = temp;
        }

        for(int i = 63; i >= 0; i--) {
            a += bit[i];
            if(i != 0)  a <<= k;
        }
        if(N == 0) printf("%u", a);
        else    printf("%u ", a);

    }
}
