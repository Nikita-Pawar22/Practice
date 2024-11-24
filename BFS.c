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

void DFS(int graph[MAX_NODES][MAX_NODES], int n, int start, int end) {
    int visited[MAX_NODES] = {0}; // To keep track of visited nodes
    Stack stack;
    initStack(&stack);

    // Start DFS from the start node
    push(&stack, start);
    visited[start] = 1;

    printf("DFS Traversal: ");
    while (!isEmpty(&stack)) {
        int current = pop(&stack);
        printf("%d ", current);

        // If the end node is reached, stop the traversal
        if (current == end) {
            printf("\nPath to end node %d found.\n", end);
            return;
        }

        // Visit all adjacent nodes
        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                push(&stack, i);
                visited[i] = 1;
            }
        }
    }
    printf("\nEnd node %d not reachable from start node %d.\n", end, start);
}

int main() {
    int n, start, end;
    int graph[MAX_NODES][MAX_NODES];

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the start node: ");
    scanf("%d", &start);

    printf("Enter the end node: ");
    scanf("%d", &end);

    DFS(graph, n, start, end);

    return 0;
}
