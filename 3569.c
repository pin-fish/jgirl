#include<stdio.h>

int main() {
    int Q;
    scanf("%d", &Q);
    while(Q--) {
        int n;
        scanf("%d", &n);
        while(n--) {
            unsigned int a, x = 1, y = 2;
            scanf("%d", &a);
            for(int i = 0; i < 16; i++) {
                unsigned int j = a & x;
                unsigned int k = a & y;
                a = a - j - k;
                a = a + (j << 1) + (k >> 1);
                x = x << 2;
                y = y << 2;
            }
            if (n==0) printf("%u", a);
            else printf("%u ", a);
        }
        printf("\n");
    }
}