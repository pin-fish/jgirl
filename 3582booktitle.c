#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    // Allocate memory for book titles
    int *titles = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &titles[i]);
    }

    // Hash map to store the count of each book title in the current window
    int *countMap = (int *)calloc(10001, sizeof(int)); // Assuming book titles are in the range [0, 100000]
    int distinctCount = 0;

    // Initialize the first window
    for (int i = 0; i < k; i++) {
        if (countMap[titles[i]] == 0) {
            distinctCount++;
        }
        countMap[titles[i]]++;
    }

    // Print the number of distinct titles in the first window
    printf("%d ", distinctCount);

    // Slide the window from position k to n
    for (int i = k; i < n; i++) {
        // Remove the count of the book title that is going out of the window
        if (countMap[titles[i - k]] == 1) {
            distinctCount--;
        }
        countMap[titles[i - k]]--;

        // Add the count of the new book title that is coming into the window
        if (countMap[titles[i]] == 0) {
            distinctCount++;
        }
        countMap[titles[i]]++;

        // Print the number of distinct titles in the current window
        printf("%d", distinctCount);
        if (i < n - 1) {
            printf(" ");
        }
        
    }

    // Free allocated memory
    free(titles);
    free(countMap);

    return 0;
}