#include <stdio.h>
#include <stdlib.h>
#define int long long

signed main() {
    int n, L;
    scanf("%lld %lld", &n, &L);

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    int currentSum = 0;
    int maxSum = 0;
    int maxIndex = 0;

    // Calculate the sum of the first L elements
    for (int i = 0; i < L; i++) {
        currentSum += arr[i];
    }
    maxSum = currentSum;
    maxIndex = 1;

    // Slide the window from the start to the end of the array
    for (int i = L; i < n; i++) {
        currentSum = currentSum - arr[i - L] + arr[i];
        if (currentSum >= maxSum) {
            maxSum = currentSum;
            maxIndex = i - L + 1 + 1;
        }
    }

    // Print the result
    printf("%lld %lld\n", maxSum, maxIndex);

    // Free allocated memory
    free(arr);

    return 0;
}