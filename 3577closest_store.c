#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n], b[m];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }

    int i = 0, j = 0;
    while (i < n) {
        while (j < m - 1 && abs(a[i] - b[j + 1]) < abs(a[i] - b[j]))
            j++;
        if (i < n-1)
            printf("%d ", abs(a[i] - b[j]));
        else
            printf("%d", abs(a[i] - b[j]));
        i++;
    }

    return 0;
}