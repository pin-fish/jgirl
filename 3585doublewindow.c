#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_VAL 65536

int main() {
    int N, budget, K;
    scanf("%d %d %d", &budget, &N, &K);
    int arr[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    int countMap[MAX_VAL + 1] = {0}; // Hash map to count elements
    int distinctCount = 0; // Number of distinct elements in the current window
    int currentSum = 0; // Sum of the current window
    int minLength = N + 1; // Initialize minLength to a large value

    int start = 0;
    for (int end = 0; end < N; end++) {
        // Add the current element to the window
        if (countMap[arr[end]] == 0) {
            distinctCount++;
        }
        countMap[arr[end]]++;
        currentSum += arr[end];

        // Check if the current window meets the constraints
        while (currentSum >= budget && distinctCount >= K) {
            // Update the minimum length
            if (end - start + 1 < minLength) {
                minLength = end - start + 1;
            }

            // Remove the start element from the window
            countMap[arr[start]]--;
            if (countMap[arr[start]] == 0) {
                distinctCount--;
            }
            currentSum -= arr[start];
            start++;
        }
    }

    // Print the result
    if (minLength == N + 1) {
        printf("-1\n");
    } else {
        printf("%d\n", minLength);
    }

    return 0;
}