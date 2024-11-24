#include <stdio.h>
#include <stdlib.h>

// Node structure for adjacency list
struct Node {
    char dest;
    struct Node* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct Node* head;
};

// Function to create a new adjacency list node
struct Node* createNode(char dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the adjacency list
void addEdge(struct AdjList adj[], char src, char dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = adj[src - 'A'].head; // Adjust index for characters
    adj[src - 'A'].head = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = adj[dest - 'A'].head;
    adj[dest - 'A'].head = newNode;
}

// Recursive function to perform DFS with goal vertex option
int DFSRec(struct AdjList adj[], int visited[], char vertex, char goalVertex, int entireGraph) {
    // Mark the current vertex as visited and print it
    visited[vertex - 'A'] = 1;
    printf("%c ", vertex);

    // If we reach the goal vertex and entireGraph is not selected, stop traversal
    if (!entireGraph && vertex == goalVertex) {
        printf("\nGoal vertex %c reached. Stopping traversal.\n", vertex);
        return 0;
    }

    // Recur for all the vertices adjacent to this vertex
    struct Node* temp = adj[vertex - 'A'].head;
    while (temp != NULL) {
        char adjVertex = temp->dest;
        if (!visited[adjVertex - 'A']) {
            if (!DFSRec(adj, visited, adjVertex, goalVertex, entireGraph)) {
                return 0; // Stop traversal
            }
        }
        temp = temp->next;
    }
    return 1; // Continue traversal
}

// Function to initialize DFS
void DFS(struct AdjList adj[], int V, char startVertex, int entireGraph, char goalVertex) {
    // Create a visited array and initialize all vertices as not visited
    int visited[V];
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }

    // Start DFS from the given vertex
    printf("DFS Traversal starting from vertex %c: ", startVertex);
    DFSRec(adj, visited, startVertex, goalVertex, entireGraph);
    printf("\n");
}

int main() {
    int V, E;

    // Take number of vertices and edges as input
    printf("Enter the number of vertices in the graph (e.g., 5 for A-E): ");
    scanf("%d", &V);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    // Create an array of adjacency lists
    struct AdjList adj[V];
    for (int i = 0; i < V; i++) {
        adj[i].head = NULL;
    }

    // Take input for the edges
    printf("Enter the edges (format: A B for an edge between A and B):\n");
    for (int i = 0; i < E; i++) {
        char src, dest;
        printf("Edge %d: ", i + 1);
        scanf(" %c %c", &src, &dest);
        addEdge(adj, src, dest);
    }

    // Take the starting vertex for DFS
    char startVertex;
    printf("Enter the starting vertex for DFS (e.g., A): ");
    scanf(" %c", &startVertex);

    // Ask the user if they want to traverse the entire graph or stop at a goal vertex
    int choice;
    printf("Do you want to traverse the entire graph or stop at a goal vertex?\n");
    printf("Enter 1 for entire graph, 2 for goal vertex: ");
    scanf("%d", &choice);

    int entireGraph = (choice == 1);
    char goalVertex = '\0';
    if (!entireGraph) {
        printf("Enter the goal vertex (e.g., E): ");
        scanf(" %c", &goalVertex);
    }

    // Call DFS function
    DFS(adj, V, startVertex, entireGraph, goalVertex);

    return 0;
}
