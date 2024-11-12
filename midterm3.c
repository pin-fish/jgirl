#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N;
    long long k;
    scanf("%d %lld", &N, &k);

    int *candies = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &candies[i]);
    }

    // Sort the candies array
    qsort(candies, N, sizeof(int), compare);

    // Sliding window approach to find the maximum number of children with the same number of candies
    long long current_sum = 0;
    int max_children = 1;
    int left = 0;
    long long  mean = candies[0];
    long long  mid = 0;
    long long  new_mid = 0, new_mean = 0;

    for (int right = 1; right < N; right++) {
        new_mean = (mean * (right - left) + candies[right])/(right - left + 1);
        for (int i = left; i <= right; i++) {
            if (candies[i] >= new_mean) {
                new_mid = i;
                break;
            }
        }
        current_sum += (candies[right] - candies[mid]);
        current_sum -= (new_mean - mean) * (right - new_mid);
        for (int i = mid; i <= new_mid; i++) {
            current_sum -= candies[i] - mean;
            current_sum += new_mean - candies[i];
        }
        current_sum += (new_mean - mean) * (mid - left);

        mean = new_mean;
        mid = new_mid;
        while (current_sum > k) {
            new_mean = (mean * (right - left + 1) - candies[left])/(right - left);
            for (int i = left + 1; i <= right; i++) {
                if (candies[i] >= new_mean) {
                    new_mid = i;
                    break;
                }
            }
            current_sum -= candies[left] - candies[mid];
            current_sum -= (mean - new_mean) * (new_mid - left - 1);
            for (int i = new_mid ; i <= mid; i++) {
                current_sum -= mean - candies[i];
                current_sum += candies[i] - new_mean;
            }
            current_sum += (mean - new_mean) * (right - mid);
            left++;
            mean = new_mean;
            mid = new_mid;
        }
        max_children = (right - left + 1) > max_children ? (right - left + 1) : max_children;
    }
    

    printf("%d\n", max_children);

    free(candies);
    return 0;
}