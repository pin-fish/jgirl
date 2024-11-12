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
    int bikeStations[N][2];
    int R[N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &bikeStations[i][j]);
        }
        R[i] = (bikeStations[i][0] * bikeStations[i][0]) + (bikeStations[i][1] * bikeStations[i][1]);
    }
    
    scanf("%d", &M);
    int u, v;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &u, &v);
        int r = (u * u) + (v * v);
        int close = binarySearch(R, N, r);
        int left = close - 1;
        int right = close;
        while (left >= 0 || right < N) {
            if (left >= 0 && right < N) {
                if (abs(R[left] - r) <= abs(R[right] - r)) {
                    int leftmost = left;
                    while (leftmost >= 0 && R[leftmost] == R[left]) {
                        leftmost--;
                    }
                    leftmost++;
                    for(int j = left; j >= leftmost; j--) {
                        printf("(%d,%d)", bikeStations[j][0], bikeStations[j][1]);
                    }
                    left = leftmost - 1;
                } else {
                    int rightmost = right;
                    while (rightmost < N && R[rightmost] == R[right]) {
                        rightmost++;
                    }
                    rightmost--;
                    for(int j = right; j <= rightmost; j++) {
                        printf("(%d,%d)", bikeStations[j][0], bikeStations[j][1]);
                    }
                    right = rightmost + 1;
                }
            } else if (left >= 0) { // right >＝ N
                int leftmost = left;
                while (leftmost >= 0 && R[leftmost] == R[left]) {
                    leftmost--;
                }
                leftmost++;
                for(int j = left; j >= leftmost; j--) {
                    printf("(%d,%d)", bikeStations[j][0], bikeStations[j][1]);
                }
                left = leftmost - 1;
            } else if (right < N) {
                int rightmost = right;
                while (rightmost < N && R[rightmost] == R[right]) {
                    rightmost++;
                }
                rightmost--;
                for(int j = right; j <= rightmost; j++) {
                    printf("(%d,%d)", bikeStations[j][0], bikeStations[j][1]);
                }
                right = rightmost + 1;
            }
        }
        printf("\n");
    }
    
    return 0;
}