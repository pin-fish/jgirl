#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

int is_special[MAX_N];
int block = 0;
int count = 0;

// Define the structure for the adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Define the graph structure
typedef struct Graph {
    Node* adjList[MAX_N];
    int visited[MAX_N];
} Graph;

// Function to create a new adjacency list node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the graph
void initGraph(Graph* g, int n) {
    for (int i = 0; i < n; i++) {
        g->adjList[i] = NULL;
        g->visited[i] = 0;
    }
}

// Function to add an edge to the graph
void addEdge(Graph* g, int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;

    newNode = createNode(u);
    newNode->next = g->adjList[v];
    g->adjList[v] = newNode;
}

// DFS function to detect cycles in the graph
int dfs(Graph* g, int v, int parent) {
    g->visited[v] = block;
    //printf("%d visited\n", v + 1);


    Node* temp = g->adjList[v];
    while (temp != NULL) {
        int neighbor = temp->vertex;

        if (g->visited[neighbor] == 0) {
            dfs(g, neighbor, v);
        } else if (neighbor != parent) {
            if (is_special[block] == 0) {
                is_special[block] = 1;
                count++;
                //printf("block %d is special\n", block);
            }
        }
        temp = temp->next;
    }
    return 0;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Graph g;
    initGraph(&g, n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&g, u - 1, v - 1);  // Adjusting for 0-based index
    }

    for (int i = 0; i < n; i++) {
        if (g.visited[i] == 0) {  // New component found
            block++;
            //printf("block %d start from %d\n", block, i + 1);
            dfs(&g, i, -1);
        }
    }
    printf("%d\n", block);

    // Free allocated memory (optional)
    for (int i = 0; i < n; i++) {
        Node* temp = g.adjList[i];
        while (temp != NULL) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }

    return 0;
}
