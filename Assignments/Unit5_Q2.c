/*A transportation network contains cities connected by roads with different costs. Write a C
program implementing Dijkstra’s Shortest Path Algorithm that accepts the number of vertices,
weighted adjacency matrix and source vertex, computes the minimum distance from the source to
every other vertex, and displays each destination with its shortest distance. Test it using at least
five vertices.*/


#include <stdio.h>

#define MAX 100
#define INF 999999

int main() {
    int graph[MAX][MAX];
    int distance[MAX];
    int visited[MAX];
    int n, source, i, j;
    int min, u;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of vertices!\n");
        return 0;
    }

    printf("Enter weighted adjacency matrix (0 for no edge):\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);

            if (graph[i][j] < 0) {
                printf("Negative weights are not allowed!\n");
                return 0;
            }
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &source);

    if (source < 0 || source >= n) {
        printf("Invalid source vertex!\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        distance[i] = INF;
        visited[i] = 0;
    }

    distance[source] = 0;

    for (i = 0; i < n - 1; i++) {
        min = INF;
        u = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && distance[j] < min) {
                min = distance[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && graph[u][j] > 0 &&
                distance[u] != INF &&
                distance[u] + graph[u][j] < distance[j]) {

                distance[j] = distance[u] + graph[u][j];
            }
        }
    }

    printf("\nShortest distances from source vertex %d:\n", source);
    printf("Destination\tDistance\n");

    for (i = 0; i < n; i++) {
        if (distance[i] == INF)
            printf("%d\t\tUnreachable\n", i);
        else
            printf("%d\t\t%d\n", i, distance[i]);
    }

    return 0;
}
