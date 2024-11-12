#include <stdio.h>
#include <stdlib.h>
#define ll long long

int main(){
    int n, x = 0, nxor;
    scanf("%d", &n);
    ll *arr = (ll *)malloc(n * sizeof(ll));
    ll *sum = (ll *)malloc(n * sizeof(ll));
    ll max = 0;
    for(int i = 0; i < n; i++){
        scanf("%lld", &arr[i]);
        max += arr[i];
        sum[i] = 0;
    }
    
    for(int i = 0; i < 30; i++){
        ll num_1 = 0;
        
        for(int j = 0; j < n; j++){
            //計算第i位為1的數量
            num_1 += (arr[j] >> i) & 1;
        }
        for(int j = 0; j < n - 2; j++){
            //計算在第i位與(Aj xor Aj+1 xor Aj+2)不同的A數量
            sum[j] += (num_1 - (2 * num_1 - n) * ((arr[j] >> i)^(arr[j+1] >> i)^(arr[j+2] >> i) & 1)) << i;
        }
    }
    for(int i = 0; i < n + 1; i++){
        if(sum[i] > max) max = sum[i];
    }
    printf("%lld\n", max);
}