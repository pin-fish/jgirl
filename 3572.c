#include<stdio.h>
#define int long long
signed main() {
    int k, d;
    scanf("%lld %lld", &k, &d);
    int max = -1, d_t = d, count = 1;
    while(d_t > 0) {
        count = d_t % 10;
        max ++;
        d_t /= 10;
    }
    //printf("count = %lld\n", count);
    //printf("max = %lld\n", max);

    int k_bit[max], d_bit[max], c_bit[max], e_bit[max];

    for(int i = 0; i < max; i++) {
        k_bit[i] = k % 2;
        d_bit[i] = d % 10;
        c_bit[i] = count % 2;
        k >>= 1;
        d /= 10;
        count >>= 1;
    }

    int c_max = max;
    for(int i = max-1; i >= 0; i--) {
        if (c_bit[i] == 0) c_max--;
        else break;
    }
    for(int i = max-1; i >= c_max; i--) {
        c_bit[i] = c_bit[i % c_max];
    }

    for(int i = 0; i < max; i++) {
        if (c_bit[i] == 0) {
            e_bit[i] = k_bit[i] ^ d_bit[i];
        } else {
            e_bit[i] = d_bit[i];
        }   
    }

/*
    //test
    printf("D=");
    for(int i = max-1; i >= 0; i--) {
        printf("%lld", d_bit[i]);
    }
    printf("\n");
    printf("K=");
    for(int i = max-1; i >= 0; i--) {
        printf("%lld", k_bit[i]);
    }
    printf("\n");
    printf("M=");
    for(int i = max-1; i >= 0; i--) {
        printf("%lld", c_bit[i]);
    }
    printf("\n");
    printf("E=");
    for(int i = max-1; i >= 0; i--) {
        printf("%lld", e_bit[i]);
    }
    printf("\n");
*/    

    int e = 0;
    for(int i = 0; i < max; i++) {
        e += e_bit[i] << i;
    }
    printf("%lld", e);
}