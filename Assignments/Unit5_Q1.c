/*A network of n locations is represented as a graph. Write a C program that accepts the graph
using an Adjacency Matrix, accepts a starting vertex, performs a graph traversal, displays the visit
order, and ensures that a vertex is not processed repeatedly. Test it with connected and partially
connected graphs.*/


#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int queue[MAX];

int main() {
    int n, i, j, start;
    int front = 0, rear = -1;
    int current, count = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of vertices!\n");
        return 0;
    }

    printf("Enter adjacency matrix (%d x %d):\n", n, n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("Enter starting vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid starting vertex!\n");
        return 0;
    }

    visited[start] = 1;
    queue[++rear] = start;

    printf("BFS Traversal: ");

    while (front <= rear) {
        current = queue[front++];
        printf("%d ", current);
        count++;

        for (i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }

    printf("\n");

    if (count < n) {
        printf("Graph is partially connected from vertex %d.\n", start);
        printf("Unvisited vertices: ");

        for (i = 0; i < n; i++) {
            if (!visited[i]) {
                printf("%d ", i);
            }
        }
        printf("\n");
    } else {
        printf("All vertices are reachable from vertex %d.\n", start);
    }

    return 0;
}
