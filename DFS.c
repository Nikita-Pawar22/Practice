#include <stdio.h>
#include <stdlib.h>

// Node structure for adjacency list
struct Node {
    int dest;
    struct Node* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct Node* head;
};

// Function to create a new adjacency list node
struct Node* createNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the adjacency list
void addEdge(struct AdjList adj[], int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = adj[src].head;
    adj[src].head = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = adj[dest].head;
    adj[dest].head = newNode;
}

// Recursive function to perform DFS
void DFSRec(struct AdjList adj[], int visited[], int vertex) {
    // Mark the current vertex as visited and print it
    visited[vertex] = 1;
    printf("%d ", vertex);

    // Recur for all the vertices adjacent to this vertex
    struct Node* temp = adj[vertex].head;
    while (temp != NULL) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex]) {
            DFSRec(adj, visited, adjVertex);
        }
        temp = temp->next;
    }
}

// Function to initialize DFS
void DFS(struct AdjList adj[], int V, int startVertex) {
    // Create a visited array and initialize all vertices as not visited
    int visited[V];
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }

    // Start DFS from the given vertex
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSRec(adj, visited, startVertex);
    printf("\n");
}

int main() {
    int V, E;
    
    // Take number of vertices and edges as input
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    // Create an array of adjacency lists
    struct AdjList adj[V];
    for (int i = 0; i < V; i++) {
        adj[i].head = NULL;
    }

    // Take input for the edges
    printf("Enter the edges (format: source destination):\n");
    for (int i = 0; i < E; i++) {
        int src, dest;
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(adj, src, dest);
    }

    // Take the starting vertex for DFS
    int startVertex;
    printf("Enter the source vertex for DFS: ");
    scanf("%d", &startVertex);

    // Call DFS function
    DFS(adj, V, startVertex);

    return 0;
}
