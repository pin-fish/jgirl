#include <stdio.h>
#include <stdlib.h>

// Function to find the maximums of every K consecutive elements in A
void findMaxInSlidingWindow(int *arr, int N, int K) {
    // Create a deque to store indices of array elements
    int *deque = (int *)malloc(N * sizeof(int));
    int front = 0, rear = -1;

    // Process first K elements separately to initialize the deque
    for (int i = 0; i < K; i++) {
        while (rear >= front && arr[i] >= arr[deque[rear]]) {
            rear--;
        }
        deque[++rear] = i;
    }

    // Process the remaining elements
    for (int i = K; i < N; i++) {
        // The element at the front of the deque is the largest element of the previous window
        printf("%d ", arr[deque[front]]);

        // Remove the elements which are out of this window
        if (deque[front] <= i - K) {
            front++;
        }

        // Remove all elements smaller than the currently being added element (arr[i])
        while (rear >= front && arr[i] >= arr[deque[rear]]) {
            rear--;
        }

        // Add current element at the rear of deque
        deque[++rear] = i;
    }

    // Print the maximum element of the last window
    printf("%d ", arr[deque[front]]);

    free(deque); // Free dynamically allocated memory
}

int main() {
    int N, K;
    // Read N and K
    scanf("%d %d", &N, &K);
    int *A = (int *)malloc(N * sizeof(int));

    // Read array A
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    // Find and print maximums of each sliding window
    findMaxInSlidingWindow(A, N, K);

    free(A); // Free dynamically allocated memory
    return 0;
}
