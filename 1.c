#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 7
#define MAX_NEIGHBORS 5

typedef struct Node {
    char name;
    struct Node* neighbors[MAX_NEIGHBORS];
    int num_neighbors;
} Node;

// Función para inicializar un nodo con su nombre y vecinos
Node* createNode(char name) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->name = name;
    node->num_neighbors = 0;
    return node;
}

// Función para agregar un vecino a un nodo
void addNeighbor(Node* node, Node* neighbor) {
    if (node->num_neighbors < MAX_NEIGHBORS) {
        node->neighbors[node->num_neighbors++] = neighbor;
    } else {
        printf("Error: Too many neighbors for node %c\n", node->name);
    }
}

// Función para la búsqueda primero en amplitud
void BFS(Node* start, Node* goal) {
    if (start == NULL || goal == NULL) return;

    Node* queue[MAX_NODES];
    int visited[MAX_NODES] = {0};
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start->name - 'A'] = 1;

    while (front < rear) {
        Node* current = queue[front++];
        printf("%c -> ", current->name);

        if (current == goal) {
            printf("Objetivo alcanzado!\n");
            return;
        }

        for (int i = 0; i < current->num_neighbors; i++) {
            Node* neighbor = current->neighbors[i];
            if (!visited[neighbor->name - 'A']) {
                queue[rear++] = neighbor;
                visited[neighbor->name - 'A'] = 1;
            }
        }
    }

    printf("Objetivo no alcanzado desde el nodo inicial.\n");
}

// Función auxiliar para la búsqueda primero en profundidad
void DFSUtil(Node* current, Node* goal, int visited[]) {
    if (current == goal) {
        printf("%c -> Objetivo alcanazado!\n", current->name);
        exit(0);
    }

    printf("%c -> ", current->name);
    visited[current->name - 'A'] = 1;

    for (int i = 0; i < current->num_neighbors; i++) {
        Node* neighbor = current->neighbors[i];
        if (!visited[neighbor->name - 'A']) {
            DFSUtil(neighbor, goal, visited);
        }
    }
}

// Función para la búsqueda primero en profundidad
void DFS(Node* start, Node* goal) {
    if (start == NULL || goal == NULL) return;

    int visited[MAX_NODES] = {0};
    DFSUtil(start, goal, visited);

    printf("Objetivo no alcanzado desde el nodo inicial.\n");
}

int main() {
    // Crear nodos
    Node* A = createNode('A');
    Node* B = createNode('B');
    Node* C = createNode('C');
    Node* D = createNode('D');
    Node* E = createNode('E');
    Node* F = createNode('F');
    Node* G = createNode('G');

    // Establecer vecinos
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

    // Ejecutar búsqueda primero en amplitud
    printf("Busqueda primero en amplitud A--G: ");
    BFS(A, G);

    // Ejecutar búsqueda primero en profundidad
    printf("\nBusqueda primero en profundidad A--G: ");
    DFS(A, G);

    // Liberar memoria
    free(A);
    free(B);
    free(C);
    free(D);
    free(E);
    free(F);
    free(G);

    return 0;
}
