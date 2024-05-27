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

// Función para calcular el valor de un estado (nodo)
int evaluateState(Node* state) {
    int value = 0;
    // Sumar los pesos de los nodos presentes en el estado
    if (state->name == 'A') value += 3;
    else if (state->name == 'B') value += 5;
    else if (state->name == 'C') value += 2;
    else if (state->name == 'D') value += 17;
    else if (state->name == 'E') value += 8;
    else if (state->name == 'F') value += 19;
    else if (state->name == 'G') value += 17;
    return value;
}

// Función para encontrar el mejor estado alcanzable desde un estado dado
Node* findBestNeighbor(Node* current) {
    int currentValue = evaluateState(current);
    Node* bestNeighbor = NULL;
    int bestValue = currentValue;

    // Iterar sobre los vecinos del estado actual
    for (int i = 0; i < current->num_neighbors; i++) {
        Node* neighbor = current->neighbors[i];
        int neighborValue = evaluateState(neighbor);
        if (neighborValue > bestValue) {
            bestNeighbor = neighbor;
            bestValue = neighborValue;
        }
    }

    return bestNeighbor;
}

// Función para la búsqueda local por ascenso de colina
void hillClimbing(Node* initial) {
    Node* current = initial;

    while (1) {
        int currentValue = evaluateState(current);
        Node* next = findBestNeighbor(current);
        if (next == NULL || evaluateState(next) <= currentValue) {
            break;  // No hay un vecino mejor o hemos alcanzado un máximo local
        }
        current = next;
    }

    // Imprimir el mejor estado encontrado
    printf("El mejor estado alcanzable desde %c es %c\n", initial->name, current->name);
}

int main() {
    // Crear los nodos y establecer vecinos
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

    // Ejecutar la búsqueda local por ascenso de colina desde cada nodo
    hillClimbing(A);
    hillClimbing(B);
    hillClimbing(C);
    hillClimbing(D);
    hillClimbing(E);
    hillClimbing(F);
    hillClimbing(G);

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
