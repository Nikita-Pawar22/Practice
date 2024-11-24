#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// Priority Queue structure
typedef struct {
    int vertex;
    int priority;
} PriorityQueueItem;

typedef struct {
    PriorityQueueItem *items;
    int size;
    int capacity;
} PriorityQueue;

// Priority Queue Functions
PriorityQueue* createPriorityQueue(int initialCapacity) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = initialCapacity;
    pq->size = 0;
    pq->items = (PriorityQueueItem*)malloc(pq->capacity * sizeof(PriorityQueueItem));
    return pq;
}

void swap(PriorityQueueItem *a, PriorityQueueItem *b) {
    PriorityQueueItem temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, int index) {
    while (index > 0 && pq->items[index].priority < pq->items[(index - 1) / 2].priority) {
        swap(&pq->items[index], &pq->items[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

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

PriorityQueueItem dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty\n");
        PriorityQueueItem item = {-1, INF};  // Return an invalid item
        return item;
    }
    PriorityQueueItem item = pq->items[0];
    pq->items[0] = pq->items[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return item;
}

bool isPriorityQueueEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

typedef struct Node {
    int vertex;
    int weight;
    struct Node *next;
} Node;

typedef struct {
    Node **adjLists;
    int numVertices;
} Graph;

Graph* createGraph(int vertices) {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->numVertices = vertices;
    g->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    
    for (int i = 0; i < vertices; i++) {
        g->adjLists[i] = NULL;
    }
    return g;
}

void addEdge(Graph *g, int start, int end, int weight) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = end;
    newNode->weight = weight;
    newNode->next = g->adjLists[start];
    g->adjLists[start] = newNode;
}

int heuristic(int vertex, int goal) {
    return abs(vertex - goal); 
}

void aStar(Graph *g, int startVertex, int goalVertex) {
    int *dist = (int*)malloc(g->numVertices * sizeof(int));
    int *parent = (int*)malloc(g->numVertices * sizeof(int));
    bool *visited = (bool*)malloc(g->numVertices * sizeof(bool));
    PriorityQueue *pq = createPriorityQueue(MAX_VERTICES);
    
    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }
    
    dist[startVertex] = 0;
    enqueue(pq, startVertex, heuristic(startVertex, goalVertex));
    
    while (!isPriorityQueueEmpty(pq)) {
        PriorityQueueItem current = dequeue(pq);
        int currentVertex = current.vertex;
        
        if (visited[currentVertex]) continue;
        visited[currentVertex] = true;
        
        printf("Visited: %d\n", currentVertex);
        if (currentVertex == goalVertex) {
            printf("Goal %d reached\n", goalVertex);
            break;
        }
        
        Node *temp = g->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            int newDist = dist[currentVertex] + temp->weight;
            if (!visited[adjVertex] && newDist < dist[adjVertex]) {
                dist[adjVertex] = newDist;
                parent[adjVertex] = currentVertex;
                int priority = newDist + heuristic(adjVertex, goalVertex);
                enqueue(pq, adjVertex, priority);
            }
            temp = temp->next;
        }
    }
    
    // Print the path from startVertex to goalVertex
    printf("Path from %d to %d: ", startVertex, goalVertex);
    int path[100]; 
    int step = goalVertex;
    int pathIndex = 0;

    while (step != -1) {
        path[pathIndex++] = step; 
        step = parent[step];
    }
    
    for (int i = pathIndex - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");

    free(dist);
    free(parent);
    free(visited);
    free(pq->items);
    free(pq);
    for (int i = 0; i < g->numVertices; i++) {
        Node *temp = g->adjLists[i];
        while (temp) {
            Node *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(g->adjLists);
    free(g);
}

int main() {
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    Graph *g = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (start_vertex end_vertex weight):\n");
    for (int i = 0; i < edges; i++) {
        int start, end, weight;
        scanf("%d %d %d", &start, &end, &weight);
        addEdge(g, start, end, weight);
        addEdge(g, end, start, weight); // Assuming undirected graph
    }

    int startVertex, goalVertex;
    printf("Enter the start vertex: ");
    scanf("%d", &startVertex);

    printf("Enter the goal vertex: ");
    scanf("%d", &goalVertex);

    aStar(g, startVertex, goalVertex);

    return 0;
}
