#include <stdio.h>
#include <stdlib.h>

// Global variables
int N, S;
int *P;
int **paths;
int pathIndex = 0;

// Function to add a path in reverse order (leaf to root)
void addPath(int *path, int length) {
    paths[pathIndex] = (int *)calloc(length + 1, sizeof(int));
    for (int i = length - 1; i >= 0; i--) {
        paths[pathIndex][length - 1 - i] = path[i];
    }
    paths[pathIndex][length] = 0;  // Null-terminate the path
    pathIndex++;
}

// DFS function to find paths from root to leaf
void dfs(int node, int currentSum, int *path, int length) {
    if (node >= N || P[node] == 0) return;  // If node is out of bounds or null

    path[length] = P[node];
    currentSum += P[node];
    length++;

    int left = 2 * node + 1;
    int right = 2 * node + 2;

    // Check if it's a leaf node
    if ((left >= N && right >= N) || (P[left] == 0 && P[right] == 0)) {
        if (currentSum == S) addPath(path, length);  // Add valid path
    } else {
        dfs(left, currentSum, path, length);  // Left child
        dfs(right, currentSum, path, length); // Right child
    }
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

    // Allocate memory for paths
    paths = (int **)calloc(N, sizeof(int *));
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

    dfs(0, 0, path, 0);

    if (pathIndex == 0) {
        printf("-1\n");
    } else {
        for (int i = 0; i < pathIndex; i++) {
            for (int j = 0; paths[i][j] != 0; j++) {
                printf("%d", paths[i][j]);
                if(paths[i][j+1] != 0) printf(" ");
            }
            printf("\n");
            free(paths[i]);  // Free memory for each path after printing
        }
    }

    // Free all dynamically allocated memory
    free(P);
    free(paths);
    free(path);

    return 0;
}
