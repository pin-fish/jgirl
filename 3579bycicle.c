#include <stdio.h>
#include <stdlib.h>

// Function to compare integers for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to perform binary search and find the correct position
int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2; //avoid overflow
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

int main() {
    int N, M;

    scanf("%d", &N);
    int bikeStations[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &bikeStations[i]);
    }
    
    scanf("%d", &M);
    int users[M];
    for (int i = 0; i < M; i++) {
        scanf("%d", &users[i]);
    }

    for (int i = 0; i < M; i++) {
        int close = binarySearch(bikeStations, N, users[i]);
        int left = close - 1;
        int right = close;
        while (left >= 0 || right < N) {
            if (left >= 0 && right < N) {
                if (abs(bikeStations[left] - users[i]) <= abs(bikeStations[right] - users[i])) {
                    printf("%d ", bikeStations[left--]);
                } else {
                    printf("%d ", bikeStations[right++]);
                }
            } else if (left >= 0) {
            printf("%d ", bikeStations[left--]);
            } else if (right < N) {
            printf("%d ", bikeStations[right++]);
            }
        }
        printf("\n");
    }
    
    return 0;
}