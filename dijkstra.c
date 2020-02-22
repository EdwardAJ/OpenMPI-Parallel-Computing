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

    for (int iteration = 0; iteration < N - 1; iteration++) {
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

    // // Print solution
    // for (int vertex = 0; vertex < N; vertex++) {
    //     // printf("%d to %ld\n", vertex, dist[vertex]);
    //     printf("%d to %d\n", vertex, graph[sourceVertex][vertex]);
    // }
}

int main(int argc, char *argv[]) {

    // Test function
    
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         scanf("%d", &graph[i][j]);
    //     }
    // }

    // graph = { 0, 4, 0, 0, 0, 0, 0, 8, 0,
    //                     4, 0, 8, 0, 0, 0, 0, 11, 0, 
    //                     0, 8, 0, 7, 0, 4, 0, 0, 2, 
    //                     0, 0, 7, 0, 9, 14, 0, 0, 0, 
    //                     0, 0, 0, 9, 0, 10, 0, 0, 0, 
    //                     0, 0, 4, 14, 10, 0, 2, 0, 0, 
    //                     0, 0, 0, 0, 0, 2, 0, 1, 6, 
    //                     8, 11, 0, 0, 0, 0, 1, 0, 7, 
    //                     0, 0, 2, 0, 0, 0, 6, 7, 0 };

    // dijkstra(graph, 1); 

    // // Print function
    // printf("Matrix: \n");
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         printf("%d ", graph[i][j]);
    //     }
    //     printf("\n");
    // }

    // Get matrix size from argument vector in , convert to int
    N = strtol(argv[1], NULL, 10);
    
    // Initialize matrix
    int graph[N][N];

    // Seed with NIM: Edward Alexander Jaya
    srand(13517115);
    // Fill the matrix with rand() function
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Mod by 100 so the result won't be too big.
            graph[i][j] = rand() % 100;
        }
    }

    MPI_Status Stat;
    MPI_Init(&argc, &argv);
    // rank is the id of processes,  numtasks is the number of processes
    int rank, numtasks;
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double start_time, end_time, total_time = 0.0;

    int numOfTaskPerProcess = N / (numtasks - 1);
    int destinationRank = 0;
    int tag = 1;
    int vertex = 0;

    // for each thread, synchronize before start
    MPI_Barrier(MPI_COMM_WORLD);
        
    // Do not count the initial synchronization time
    start_time = MPI_Wtime();

    if (rank == 0) {
        long* dataRecv;
        // Receive
        MPI_Recv(&dataRecv, N, MPI_LONG, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
        printf("Received from process %d ", MPI_ANY_SOURCE);
        // To do: store in the array
        free(dataRecv);
    } else {
        for (int vertex = (rank - 1) * numOfTaskPerProcess; vertex < (rank - 1) * numOfTaskPerProcess + numOfTaskPerProcess; vertex++) {
            long* dataSend = dijkstra(graph, vertex);
            MPI_Send(dataSend, N, MPI_LONG, destinationRank, tag, MPI_COMM_WORLD);
        }
    }

    // Synchronize again and count the time
    MPI_Barrier(MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    total_time = end_time - start_time;
    MPI_Finalize();
} 
