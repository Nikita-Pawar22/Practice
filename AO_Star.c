#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct Node {
    int isSolved;
    int cost;
    int heuristic;
    int numAndChildren;
    int andChildren[100];
    int numOrChildren;
    int orChildren[100];
} Node;

Node* graph;
int N;

void initializeGraph() {
    // Initialize all nodes to unsolved and set high cost
    for (int i = 0; i < N; i++) {
        graph[i].isSolved = 0;
        graph[i].cost = INF;
        graph[i].numAndChildren = 0;
        graph[i].numOrChildren = 0;
    }

    printf("Enter the heuristic values for each node:\n");
    for (int i = 0; i < N; i++) {
        printf("Heuristic value for node %d: ", i);
        scanf("%d", &graph[i].heuristic);
    }

    printf("Enter the child details for each node (AND and OR children separately):\n");
    for (int i = 0; i < N; i++) {
        printf("Number of AND children for node %d: ", i);
        scanf("%d", &graph[i].numAndChildren);
        for (int j = 0; j < graph[i].numAndChildren; j++) {
            printf("AND Child %d of node %d: ", j + 1, i);
            scanf("%d", &graph[i].andChildren[j]);
        }

        printf("Number of OR children for node %d: ", i);
        scanf("%d", &graph[i].numOrChildren);
        for (int j = 0; j < graph[i].numOrChildren; j++) {
            printf("OR Child %d of node %d: ", j + 1, i);
            scanf("%d", &graph[i].orChildren[j]);
        }
    }
}

// AO* algorithm: Returns the minimum cost to solve the problem from the current node
int AOStar(int node) {
    if (graph[node].isSolved) {
        return graph[node].cost;
    }

    // Base case: If a node has no children, it's a leaf node
    if (graph[node].numAndChildren == 0 && graph[node].numOrChildren == 0) {
        graph[node].isSolved = 1;
        graph[node].cost = graph[node].heuristic;  // Leaf node cost = heuristic
        return graph[node].cost;
    }

    int andCost = 0, orCost = INF;

    // Compute cost for AND children
    for (int i = 0; i < graph[node].numAndChildren; i++) {
        int child = graph[node].andChildren[i];
        int childCost = AOStar(child);  // Recursively solve for the child
        if (childCost == INF) {
            andCost = INF;  // If any AND child is unsolvable, this part is unsolvable
            break;
        }
        andCost += childCost;  // Sum costs for AND children
    }

    // Compute cost for OR children
    for (int i = 0; i < graph[node].numOrChildren; i++) {
        int child = graph[node].orChildren[i];
        int childCost = AOStar(child);  // Recursively solve for the child
        if (childCost < orCost) {
            orCost = childCost;  // Minimize cost for OR children
        }
    }

    // Total cost = heuristic + min(andCost, orCost)
    graph[node].cost = graph[node].heuristic + ((andCost < orCost) ? andCost : orCost);

    // Mark the current node as solved
    graph[node].isSolved = 1;

    return graph[node].cost;
}

int main() {
    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &N);

    graph = (Node*)malloc(N * sizeof(Node));
    initializeGraph();

    printf("Solving AO* Algorithm...\n");
    int solutionCost = AOStar(0);  // Start from the root node (node 0)

    if (solutionCost != INF) {
        printf("The minimum cost from the root to solve the problem is: %d\n", solutionCost);
    } else {
        printf("No solution found.\n");
    }

    free(graph);
    return 0;
}
