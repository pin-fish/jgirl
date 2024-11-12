#include<stdio.h>

int main() {
    int k, d;
    scanf("%d %d", &k, &d);
    int m = 1, n = 1, k_t = k, d_t = d;
    while(k_t > 1) {
        m++;
        k_t >>= 1;
    }
    while(d_t > 1) {
        n++;
        d_t >>= 1;
    }
    int max = m > n ? m : n;

    int k_bit[max], d_bit[max], c_bit[max], e_bit[max];
    k_t = k;
    d_t = d;
    int count = 0;
    for(int i = 0; i < max; i++) {
        k_bit[i] = k_t % 2;
        d_bit[i] = d_t % 2;
        if (k_bit[i] ^ d_bit[i] == 1)   count++;
        k_t >>= 1;
        d_t >>= 1;
    }
    printf("%d", count);

    int c_max = max;
    for(int i = 0; i < max; i++) {
        c_bit[i] = count % 2;
        count >>= 1;
    }
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

    for(int i = max-1; i >= 0; i--) {
        printf("%d", e_bit[i]);
    }

    /*
    binary 2 decimal
    int e = 0;
    for(int i = 0; i < max; i++) {
        e += e_bit[i] << i;
    }*/
}