#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int cmp(const void *a, const void *b) {
    // 排序用的比較函數
    long long int diff = (*(long long int*)a - *(long long int*)b);
    return (diff > 0) - (diff < 0);
}

long long int closest_sum_to_M(long long int* nums, int N, long long int M) {
    qsort(nums, N, sizeof(long long int), cmp);  // 對數組進行排序
    long long int closest_Q = LLONG_MAX;  // 初始化最接近的 Q
    
    // 遍歷每個數，並用雙指針找出其對應的三元組
    for (int i = 0; i < N - 2; i++) {
        int left = i + 1;
        int right = N - 1;
        
        while (left < right) {
            long long int a = nums[i];
            long long int b = nums[left];
            long long int c = nums[right];
            long long int sum_abc = a + b + c;
            long long int Q = sum_abc * sum_abc * sum_abc;  // 計算 Q = (a + b + c)^3
            
            // 判斷這個 Q 是否比當前最優解更接近 M
            if (llabs(Q - M) < llabs(closest_Q - M)) {
                closest_Q = Q;
            }
            
            // 調整指針以尋找更接近的結果
            if (Q < M) {
                left++;  // 增加左指針，使 sum 變大
            } else {
                right--;  // 減少右指針，使 sum 變小
            }
        }
    }
    return closest_Q;
}

int main() {

    int N;
    long long int M;
    scanf("%d", &N);
    scanf("%lld", &M);
    long long int nums[N];
    for (int i = 0; i < N; i++) {
        scanf("%lld", &nums[i]);
    }
    
    long long int result = closest_sum_to_M(nums, N, M);
    printf("%lld\n", result);
    
    return 0;
}
