#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义路径结构体
typedef struct {
    int *nodes;
    int head_index;
} Path;

// 全局变量
int N, S;
int *P;
Path *paths;
int pathIndex = 0;

// 添加路径函数（从叶子到根的逆序）
void addPath(int *path, int length, int node) {
    paths[pathIndex].nodes = (int *)calloc(length + 1, sizeof(int));
    for (int i = length - 1; i >= 0; i--) {
        paths[pathIndex].nodes[length - 1 - i] = path[i];
    }
    paths[pathIndex].nodes[length] = 0;  // 以0结尾
    paths[pathIndex].head_index = node;
    pathIndex++;
}

// DFS函数，从根到叶寻找路径
void dfs(int node, int currentSum, int *path, int length) {
    if (node >= N || P[node] == 0) return;  // 如果节点越界或为空

    path[length] = P[node];
    currentSum += P[node];
    length++;

    int left = 2 * node + 1;
    int right = 2 * node + 2;

    // 检查是否为叶节点
    if (currentSum == S) addPath(path, length, node);  // 添加有效路径

    dfs(left, currentSum, path, length);  // 左子节点
    dfs(right, currentSum, path, length); // 右子节点
}

// 比较函数，用于按头节点索引排序路径
int comparePaths(const void *a, const void *b) {
    Path *pathA = (Path *)a;
    Path *pathB = (Path *)b;
    return pathA->head_index - pathB->head_index;
}

int main() {
    if (scanf("%d", &N) != 1) {
        fprintf(stderr, "Error reading N\n");
        return 1;
    }
    
    P = (int *)calloc(N + 1, sizeof(int));
    if (!P) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        if (scanf("%d", &P[i]) != 1) {
            fprintf(stderr, "Error reading P[%d]\n", i);
            free(P);
            return 1;
        }
    }
    P[N] = 0;

    if (scanf("%d", &S) != 1) {
        fprintf(stderr, "Error reading S\n");
        free(P);
        return 1;
    }

    // 分配内存用于存储路径
    paths = (Path *)calloc(N, sizeof(Path));
    if (!paths) {
        fprintf(stderr, "Memory allocation for paths failed\n");
        free(P);
        return 1;
    }

    int *path = (int *)calloc(N, sizeof(int));
    if (!path) {
        fprintf(stderr, "Memory allocation for path failed\n");
        free(P);
        free(paths);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        if (P[i] != 0) {
            dfs(i, 0, path, 0);
        }
    }

    // 按头节点索引排序路径
    qsort(paths, pathIndex, sizeof(Path), comparePaths);

    printf("%d\n", pathIndex);

    for (int i = 0; i < pathIndex; i++) {
        for (int j = 0; paths[i].nodes[j] != 0; j++) {
            printf("%d", paths[i].nodes[j]);
            if (paths[i].nodes[j + 1] != 0) printf(" ");
        }
        printf("\n");
        free(paths[i].nodes);  // 打印后释放每个路径的内存
    }

    // 释放所有动态分配的内存
    free(P);
    free(paths);
    free(path);

    return 0;
}
