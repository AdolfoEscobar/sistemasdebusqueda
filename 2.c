#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 7
#define MAX_NEIGHBORS 5

typedef struct Node {
    char name;
    struct Node* neighbors[MAX_NEIGHBORS];
    int num_neighbors;
    int heuristic;
} Node;

int straight_line_distances[MAX_NODES][MAX_NODES] = {
    {0, 5, 9, 7, 7, 8, 15},
    {5, 0, 8, 14, 9, 13, 12},
    {9, 8, 0, 10, 18, 16, 15},
    {7, 14, 10, 0, 14, 7, 19},
    {7, 9, 18, 14, 0, 7, 17},
    {8, 13, 16, 7, 7, 0, 16},
    {15, 12, 15, 19, 17, 16, 0}
};

Node* createNode(char name, int heuristic) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->name = name;
    node->num_neighbors = 0;
    node->heuristic = heuristic;
    return node;
}

void addNeighbor(Node* node, Node* neighbor) {
    if (node->num_neighbors < MAX_NEIGHBORS) {
        node->neighbors[node->num_neighbors++] = neighbor;
    } else {
        printf("Error: Too many neighbors for node %c\n", node->name);
    }
}

int straightLineDistance(Node* node1, Node* node2) {
    return straight_line_distances[node1->name - 'A'][node2->name - 'A'];
}

void BestFirstSearch(Node* start, Node* goal) {
    if (start == NULL || goal == NULL) return;

    Node* queue[MAX_NODES];
    int visited[MAX_NODES] = {0};
    int front = 0, rear = 0;

    queue[rear++] = start;

    while (front < rear) {
        Node* current = queue[front++];
        printf("%c -> ", current->name);

        if (current == goal) {
            printf("Objetivo alcanzado!\n");
            return;
        }

        visited[current->name - 'A'] = 1; // Mark the node as visited after dequeuing it

        // Sort the neighbors by the sum of heuristic value and accumulated distance
        for (int i = 0; i < current->num_neighbors; i++) {
            for (int j = i + 1; j < current->num_neighbors; j++) {
                int distance_i = straightLineDistance(current->neighbors[i], goal);
                int distance_j = straightLineDistance(current->neighbors[j], goal);
                if (current->neighbors[i]->heuristic + distance_i > current->neighbors[j]->heuristic + distance_j) {
                    Node* temp = current->neighbors[i];
                    current->neighbors[i] = current->neighbors[j];
                    current->neighbors[j] = temp;
                }
            }
        }

        for (int i = 0; i < current->num_neighbors; i++) {
            Node* neighbor = current->neighbors[i];
            if (!visited[neighbor->name - 'A']) {
                queue[rear++] = neighbor;
            }
        }
    }

    printf("Objetivo no alcanzado desde el nodo inicial.\n");
}

void GreedySearch(Node* start, Node* goal) {
    if (start == NULL || goal == NULL) return;

    Node* current = start;
    int visited[MAX_NODES] = {0};
    printf("%c -> ", current->name);

    while (current != goal) {
        visited[current->name - 'A'] = 1; // Mark the current node as visited

        Node* next = NULL;
        int min_distance = 9999;

        // Find the neighbor closest to the goal and that has not been visited
        for (int i = 0; i < current->num_neighbors; i++) {
            Node* neighbor = current->neighbors[i];
            if (!visited[neighbor->name - 'A']) {
                int distance = straightLineDistance(neighbor, goal);
                if (distance < min_distance) {
                    min_distance = distance;
                    next = neighbor;
                }
            }
        }

        // If there is no next node, it means the goal is not reachable
        if (next == NULL) {
            printf("Objetivo no alcanzado desde el nodo inicial.\n");
            return;
        }

        current = next;
        printf("%c -> ", current->name);
    }

    printf("Objetivo alcanzado!\n");
}

int main() {
    Node* A = createNode('A', 15);
    Node* B = createNode('B', 12);
    Node* C = createNode('C', 15);
    Node* D = createNode('D', 19);
    Node* E = createNode('E', 17);
    Node* F = createNode('F', 16);
    Node* G = createNode('G', 0);

    addNeighbor(A, B);
    addNeighbor(A, C);
    addNeighbor(A, D);
    addNeighbor(A, E);
    addNeighbor(A, F);

    addNeighbor(B, A);
    addNeighbor(B, C);
    addNeighbor(B, E);

    addNeighbor(C, A);
    addNeighbor(C, B);
    addNeighbor(C, D);
    addNeighbor(C, G);

    addNeighbor(D, A);
    addNeighbor(D, C);
    addNeighbor(D, F);

    addNeighbor(E, A);
    addNeighbor(E, B);
    addNeighbor(E, F);
    addNeighbor(E, G);

    addNeighbor(F, A);
    addNeighbor(F, D);
    addNeighbor(F, E);

    addNeighbor(G, C);
    addNeighbor(G, E);

    Node* goal = G;

    printf("Tecnica primero por lo mejor A--G: ");
    BestFirstSearch(A, goal);

    printf("\nBusqueda vara A--G: ");
    GreedySearch(A, goal);

    return 0;
}
