#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct Stack {
    int items[MAX_NODES];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Push an element onto the stack
void push(Stack *s, int value) {
    if (s->top < MAX_NODES - 1) {
        s->items[++(s->top)] = value;
    }
}

// Pop an element from the stack
int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return -1;
}

// Perform DFS and return the traversal
void DFS(int graph[MAX_NODES][MAX_NODES], int n, int start, int *traversal, int *size) {
    int visited[MAX_NODES] = {0}; // To keep track of visited nodes
    Stack stack;
    initStack(&stack);

    // Start DFS from the start node
    push(&stack, start);
    visited[start] = 1;

    while (!isEmpty(&stack)) {
        int current = pop(&stack);
        traversal[(*size)++] = current; // Add the current node to the traversal

        // Visit all adjacent nodes
        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                push(&stack, i);
                visited[i] = 1;
            }
        }
    }
}

// Perform DFS to find a path to the goal node
int DFSGoal(int graph[MAX_NODES][MAX_NODES], int n, int start, int goal, int *path, int *size) {
    int visited[MAX_NODES] = {0}; // To keep track of visited nodes
    Stack stack;
    initStack(&stack);

    push(&stack, start);
    visited[start] = 1;

    while (!isEmpty(&stack)) {
        int current = pop(&stack);
        path[(*size)++] = current;

        // If the goal node is found, return success
        if (current == goal) {
            return 1;
        }

        // Visit all adjacent nodes
        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                push(&stack, i);
                visited[i] = 1;
            }
        }
    }

    // If the goal is not found, return failure
    return 0;
}

int main() {
    int n, start, goal;
    int graph[MAX_NODES][MAX_NODES];
    int traversal[MAX_NODES], traversalSize = 0;
    int goalPath[MAX_NODES], goalPathSize = 0;

    // Input the number of nodes
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    // Input the adjacency matrix
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Input the start node
    printf("Enter the start node: ");
    scanf("%d", &start);

    // Perform DFS traversal from the start node
    DFS(graph, n, start, traversal, &traversalSize);

    // Print the DFS traversal
    printf("The DFS traversal for this is: ");
    for (int i = 0; i < traversalSize; i++) {
        printf("%d ", traversal[i]);
    }
    printf("\n");

    // Ask for the goal node
    printf("Enter the goal node: ");
    scanf("%d", &goal);

    // Perform DFS to find the goal node
    if (DFSGoal(graph, n, start, goal, goalPath, &goalPathSize)) {
        printf("DFS for goal node %d: ", goal);
        for (int i = 0; i < goalPathSize; i++) {
            printf("%d ", goalPath[i]);
        }
        printf("\n");
    } else {
        printf("Goal node %d is not reachable from start node %d.\n", goal, start);
    }

    return 0;
}
