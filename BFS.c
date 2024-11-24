#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 26 // Maximum number of vertices (A-Z)

int adj[MAX][MAX]; // Adjacency matrix
int visited[MAX];
int queue[MAX], front = -1, rear = -1;

// Function to map a character to its index (A -> 0, B -> 1, ..., Z -> 25)
int charToIndex(char c) {
    return c - 'A';
}

// Function to map an index back to a character (0 -> A, 1 -> B, ..., 25 -> Z)
char indexToChar(int i) {
    return i + 'A';
}

// Enqueue function for BFS
void enqueue(int vertex) {
    if (rear == MAX - 1)
        printf("Queue is full\n");
    else {
        if (front == -1) front = 0;
        queue[++rear] = vertex;
    }
}

// Dequeue function for BFS
int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue[front++];
}

// BFS function with optional goal state
void bfs(char startVertex, int vertices, char goalVertex) {
    int i;
    int startIndex = charToIndex(startVertex);
    int goalIndex = goalVertex != '\0' ? charToIndex(goalVertex) : -1;

    enqueue(startIndex);
    visited[startIndex] = 1;

    printf("BFS Traversal starting from vertex %c: ", startVertex);
    while (front <= rear) {
        int currentVertex = dequeue();
        printf("%c ", indexToChar(currentVertex));

        // If goal state is specified and reached, stop BFS
        if (currentVertex == goalIndex) {
            printf("\nGoal vertex %c reached. Stopping traversal.\n", goalVertex);
            return;
        }

        // Check all adjacent vertices
        for (i = 0; i < vertices; i++) {
            if (adj[currentVertex][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

int main() {
    int vertices, edges, i;
    char startVertex, goalVertex;
    int goalChoice;

    // Input number of vertices
    printf("Enter the number of vertices in the graph (e.g., 5 for A-E): ");
    scanf("%d", &vertices);

    // Input number of edges
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    // Initialize adjacency matrix and visited array
    for (i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adj[i][j] = 0;
        }
        visited[i] = 0;
    }

    // Input edges
    printf("Enter the edges (format: A B for an edge between A and B):\n");
    for (i = 0; i < edges; i++) {
        char u, v;
        printf("Edge %d: ", i + 1);
        scanf(" %c %c", &u, &v);
        adj[charToIndex(u)][charToIndex(v)] = 1;
        adj[charToIndex(v)][charToIndex(u)] = 1; // If the graph is undirected
    }

    // Input the starting vertex for BFS
    printf("Enter the starting vertex for BFS (e.g., A): ");
    scanf(" %c", &startVertex);

    // Ask user whether they want to traverse the entire graph or go to a goal state
    printf("Do you want to traverse the entire graph or stop at a goal vertex?\n");
    printf("Enter 1 for entire graph, 2 for goal vertex: ");
    scanf("%d", &goalChoice);

    if (goalChoice == 2) {
        printf("Enter the goal vertex (e.g., B): ");
        scanf(" %c", &goalVertex);
        bfs(startVertex, vertices, goalVertex);
    } else {
        bfs(startVertex, vertices, '\0'); // Pass '\0' for no goal
    }

    return 0;
}
