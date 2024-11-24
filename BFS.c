#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];   // Adjacency matrix for the graph
int visited[MAX];    // Array to keep track of visited nodes
int queue[MAX], front = -1, rear = -1;   // Queue for BFS

// Function to insert an element into the queue
void enqueue(int vertex) {
    if (rear == MAX - 1)
        printf("\nQueue overflow");
    else {
        if (front == -1)
            front = 0;
        rear = rear + 1;
        queue[rear] = vertex;
    }
}

// Function to remove and return an element from the queue
int dequeue() {
    if (front == -1 || front > rear) {
        printf("\nQueue underflow");
        return -1;
    } else {
        return queue[front++];
    }
}

// BFS algorithm
void bfs(int startVertex, int endVertex, int vertices) {
    int i;
    enqueue(startVertex);
    visited[startVertex] = 1;

    printf("BFS traversal: ");
    while (front <= rear) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        // Stop the search if the endVertex is found
        if (currentVertex == endVertex) {
            printf("\nPath to end node %d found.\n", endVertex);
            return;
        }

        for (i = 0; i < vertices; i++) {
            if (adj[currentVertex][i] == 1 && visited[i] == 0) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\nEnd node %d is not reachable from start node %d.\n", endVertex, startVertex);
}

int main() {
    int vertices, edges, u, v, startVertex, endVertex, i, j;

    // Input number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    // Initialize adjacency matrix to 0
    for (i = 0; i < vertices; i++)
        for (j = 0; j < vertices; j++)
            adj[i][j] = 0;

    // Input number of edges
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Input edges
    printf("Enter the edges (u v):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d%d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;  // For undirected graph
    }

    // Input starting and ending vertex for BFS
    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);
    printf("Enter the ending vertex: ");
    scanf("%d", &endVertex);

    // Initialize visited array to 0
    for (i = 0; i < vertices; i++)
        visited[i] = 0;

    // Perform BFS
    bfs(startVertex, endVertex, vertices);

    return 0;
}
