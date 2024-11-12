#include <stdio.h>
#include <stdlib.h>
#define int long long
int main() {
    int n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k); // Reading n, m, k

    int *A = (int *)malloc((n+1) * sizeof(int));
    int *B = (int *)malloc((m+1) * sizeof(int));
    
    // Reading array A
    for (int i = 0; i < n; i++) {
        scanf("%lld", &A[i]);
    }

    // Reading array B
    for (int i = 0; i < m; i++) {
        scanf("%lld", &B[i]);
    }

    int count = 0; // Counter for the number of valid (i, j) pairs

    int j = 0;
    // Two-pointer approach to find pairs where A[i] - B[j] == k
    for (int i = 0; i < n; i++) {  
        while (j < m && A[i] - B[j] > k) {
            j++;
        }
        if (j==m) j = m-1;
        if (j < m && A[i] - B[j] == k) {
            count++;  // Move j to the next element to avoid counting the same pair again
        }
        //printf("i = %lld, j = %lld, count = %lld\n", i, j, count);
    }
    j = 0;
    // Two-pointer approach to find pairs where |A[i] - B[j]| == k
    for (int i = 0; i < m; i++) {  
        while (j < n && B[i] - A[j] > k) {
            j++;
        }
        if (j==n) j = n-1;
        if (j < n && B[i] - A[j] == k) {
            count++;  // Move j to the next element to avoid counting the same pair again
        }
        //printf("i = %lld, j = %lld, count = %lld\n", i, j, count);
    }

    printf("%lld\n", count); // Output the result

    return 0;
}
