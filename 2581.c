#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 10000

void add_book(int hash_map[], int *distinct_count, int title) {
    if(hash_map[title] == 0) {
        (*distinct_count)++;
    }
    hash_map[title]++;
}

void remove_book(int hash_map[], int *distinct_count, int title) {
    hash_map[title]--;
    if (hash_map[title] == 0) {
        (*distinct_count)--;
    }
}

// Function to count distinct titles in each k×k window
void count_distinct_titles(int **matrix, int n, int k) {
    int output_size = n - k + 1;
    int result[output_size][output_size];
    int t;

    for (int i = 0; i <= n - k; i++) {
        int hash_map[MAX_BOOKS] = {0};
        int distinct_count = 0;

        // Initialize the first k×k window for this row
        for (int x = 0; x < k; x++) {
            for (int y = 0; y < k; y++) {
                t = matrix[i + x][y];
                add_book(hash_map, &distinct_count, t);
            }
        }

        // Store the count for the first window in this row
        result[i][0] = distinct_count;

        // Slide the window to the right
        for (int j = 1; j <= n - k; j++) {
            // Remove the leftmost column of the current window
            for (int x = 0; x < k; x++) {
                t = matrix[i + x][j - 1];
                remove_book(hash_map, &distinct_count, t);
            }
            // Add the rightmost column of the new window
            for (int x = 0; x < k; x++) {
                t = matrix[i + x][j + k - 1];
                add_book(hash_map, &distinct_count, t);
            }
            // Store the distinct count for the current window
            result[i][j] = distinct_count;
        }
    }

    // Print result matrix
    for (int i = 0; i < output_size; i++) {
        for (int j = 0; j < output_size; j++) {
            printf("%d", result[i][j]);
            if(j < output_size - 1)
                printf(" ");
            
        }
        printf("\n");
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int **matrix = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    count_distinct_titles(matrix, n, k);

    return 0;
}
