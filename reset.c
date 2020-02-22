#include "mpi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

int N = 10;

long getVertexWithMinDistance(long dist[], bool pickedVertices[]) {
    long minDistance = LONG_MAX;
    int vertexWithMinDistance = -1;

    for (int vertex = 0; vertex < N; vertex++) {
        if (!pickedVertices[vertex] && dist[vertex] <= minDistance) {
            minDistance = dist[vertex];
            vertexWithMinDistance = vertex;
        }
    }
    return vertexWithMinDistance;
}


long* dijkstra(int graph[N][N], int sourceVertex) {

    // Distance from single source to all of the nodes
    long *dist = (long*) malloc(sizeof(long) * N);
    bool pickedVertices[N];

    for (int vertex = 0; vertex < N; vertex++) {
        if (vertex == sourceVertex) {
            dist[vertex] = 0;
        } else {
            // Initialize all distance to be infinity.
            dist[vertex] = LONG_MAX;
        }
        pickedVertices[vertex] = false;
    }

    dist[sourceVertex] = 0;

    for (int i = 0; i < N - 1; i++) {
        // Get minimum distance
        int vertexWithMinDistance = getVertexWithMinDistance(dist, pickedVertices);

        // Mark the vertice as picked
        pickedVertices[vertexWithMinDistance] = true;

        // Update distance value
        for (int vertex = 0; vertex < N; vertex++) {
            if ((!pickedVertices[vertex]) && 
                (graph[vertexWithMinDistance][vertex]) && 
                (dist[vertexWithMinDistance] != LONG_MAX) && 
                (dist[vertexWithMinDistance] + graph[vertexWithMinDistance][vertex] < dist[vertex])) {
                // Change dist[]
                dist[vertex] = dist[vertexWithMinDistance] + graph[vertexWithMinDistance][vertex];
            }
        }
    }
    return dist;
}

int main(int argc, char *argv[]) {
    int rank, numtasks;
    double start_time, end_time, total_time;
	MPI_Status Stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    start_time = MPI_Wtime();

    int graph[N][N];
    srand(13517115);
	// Fill the matrix with rand() function
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Mod by 100 so the result won't be too big.
            graph[i][j] = rand() % 100;
        }
    }

    // Print function
    printf("Matrix: \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    MPI_Barrier(MPI_COMM_WORLD);
	end_time = MPI_Wtime();
    total_time = end_time - start_time;
    MPI_Finalize();

    if (rank == 0) {
    	printf("%f\n", total_time);
	}

    // long *data = dijkstra(graph, 0);
    // for (int i = 0; i < N; ++i)
    // {
    // 	printf("%ld\n", data[i]);
    // }
    // free(data);
}