#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Priority Queue to store nodes to be explored
typedef struct {
    int vertex;
    int priority;
} PriorityQueueItem;

typedef struct {
    PriorityQueueItem *items;
    int size;
    int capacity;
} PriorityQueue;

// Function to create a new Priority Queue
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->items = (PriorityQueueItem*)malloc(capacity * sizeof(PriorityQueueItem));
    return pq;
}

// Function to swap two items in the priority queue
void swap(PriorityQueueItem *a, PriorityQueueItem *b) {
    PriorityQueueItem temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the priority queue
void heapifyUp(PriorityQueue *pq, int index) {
    while (index > 0 && pq->items[index].priority < pq->items[(index - 1) / 2].priority) {
        swap(&pq->items[index], &pq->items[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Function to heapify the priority queue after extraction
void heapifyDown(PriorityQueue *pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->items[left].priority < pq->items[smallest].priority) {
        smallest = left;
    }
    if (right < pq->size && pq->items[right].priority < pq->items[smallest].priority) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&pq->items[index], &pq->items[smallest]);
        heapifyDown(pq, smallest);
    }
}

// Function to add an item to the priority queue
void enqueue(PriorityQueue *pq, int vertex, int priority) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->items = (PriorityQueueItem*)realloc(pq->items, pq->capacity * sizeof(PriorityQueueItem));
    }
    pq->items[pq->size].vertex = vertex;
    pq->items[pq->size].priority = priority;
    pq->size++;
    heapifyUp(pq, pq->size - 1);
}

// Function to extract the item with the highest priority from the queue
PriorityQueueItem dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty\n");
        PriorityQueueItem item = {-1, INT_MAX};  // Return an invalid item
        return item;
    }
    PriorityQueueItem item = pq->items[0];
    pq->items[0] = pq->items[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return item;
}

// Function to check if the priority queue is empty
int isPriorityQueueEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

// Function to perform Best First Search
void bestFirstSearch(int graph[MAX_NODES][MAX_NODES], int numNodes, int start, int goal, int heuristics[]) {
    if (start == goal) {
        printf("Start node is the same as the goal node. No need to search.\n");
        return;
    }

    PriorityQueue *pq = createPriorityQueue(numNodes);
    int visited[MAX_NODES] = {0};
    int parent[MAX_NODES];

    for (int i = 0; i < numNodes; i++) {
        parent[i] = -1;
    }

    enqueue(pq, start, heuristics[start]);
    visited[start] = 1;

    while (!isPriorityQueueEmpty(pq)) {
        PriorityQueueItem current = dequeue(pq);
        int currentNode = current.vertex;

        if (currentNode == goal) {
            printf("Goal reached: %d\n", goal);
            break;
        }

        for (int i = 0; i < numNodes; i++) {
            if (graph[currentNode][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = currentNode;
                enqueue(pq, i, heuristics[i]);
            }
        }
    }

    // Print the path
    printf("Path from %d to %d: ", start, goal);
    int path[MAX_NODES];
    int step = goal;
    int pathIndex = 0;

    while (step != -1) {
        path[pathIndex++] = step;
        step = parent[step];
    }

    for (int i = pathIndex - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");

    // Clean up
    free(pq->items);
    free(pq);
}

int main() {
    int numNodes, start, goal;

    // Take user input for the number of nodes, adjacency matrix, and heuristic values
    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);

    int graph[MAX_NODES][MAX_NODES];
    int heuristics[MAX_NODES];

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the heuristic values for each node:\n");
    for (int i = 0; i < numNodes; i++) {
        scanf("%d", &heuristics[i]);
    }

    printf("Enter the starting node: ");
    scanf("%d", &start);

    printf("Enter the goal node: ");
    scanf("%d", &goal);

    // Perform Best First Search
    bestFirstSearch(graph, numNodes, start, goal, heuristics);

    return 0;
}
