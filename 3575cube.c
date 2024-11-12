#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *arr = (int *)malloc(N * sizeof(int));
    //int *dup = (int *)calloc(N, sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    /*
    int l = 0, r = 1;
    while(r < N) {
        if (arr[l] == arr[r])
            dup[l] = 1;
        else{
            l++;
            arr[l] = arr[r];
        }
        r++;
    }
    N = l + 1;
    */
    /*
    printf("Array arr: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Array dup: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", dup[i]);
    }
    printf("\n");
    */

    int left = 0, right = N - 1;
    int Q = 0;

    while (left < right) {
        long long sum = arr[left] + arr[right];
        long long cube = sum * sum * sum;
        printf("left[%d]: %d, right[%d]: %d\n", left, arr[left], right, arr[right]);

        if (cube <= M) {
            Q += (right - left);
            //if (dup[left] == 1) Q += 1;
            printf("Q+=: %lld\n", right - left);
            left++;
        } else {
            right--;
            //if (left == right)  break;
        }
        //printf("Q: %lld\n", Q);
    }
    //printf("left[%d]: %d, right[%d]: %d, Q: %lld\n", left, arr[left], right, arr[right], Q);

    printf("%d", Q);

    free(arr);
    //free(dup);
    return 0;
}