#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to check if two subarrays are identical
bool are_identical(int *A, int *B, int start, int M) {
    for (int i = 0; i < M; i++) {
        if (A[start + i] != B[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int N, M;
    
    // Read the length of array A
    scanf("%d", &N);
    int *A = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    // Read the length of array B
    scanf("%d", &M);
    int *B = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        scanf("%d", &B[i]);
    }

    // List to store the starting positions
    int *positions = (int *)malloc(N * sizeof(int));
    int count = 0;

    // Sliding window to find all subarrays in A that are identical to B
    for (int i = 0; i <= N - M; i++) {
        if (are_identical(A, B, i, M)) {
            positions[count++] = i;
        }
    }

    // Print the starting positions
    for (int i = 0; i < count; i++) {
        printf("%d ", positions[i]);
    }
    printf("\n");

    // Free allocated memory
    free(A);
    free(B);
    free(positions);

    return 0;
}