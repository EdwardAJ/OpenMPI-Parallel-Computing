#include "mpi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

int N = 1000;

int getmin_index(long **graph, bool pickedVertices[N], int sourceVertex) {
    int minDistance = CHAR_MAX;
    int min_index = -1;

    for (int j = 0; j < N; j++) {
        if (!pickedVertices[j] && graph[sourceVertex][j] <= minDistance) {
            minDistance = graph[sourceVertex][j];
            min_index = j;
        }
    }
    return min_index;
}

void print(long **graph){
    printf("Matrix: \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%ld ", graph[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(long** graph, int sourceVertex) {

    // Distance from single source to all of the nodes
    bool pickedVertices[N];

    for (int vertex = 0; vertex < N; vertex++) {
        pickedVertices[vertex] = false;
    }

    for (int i = 0; i < N - 1; i++) {
        // Get minimum distance
        int min_index = getmin_index(graph, pickedVertices, sourceVertex);

        // Mark the vertice as picked
        pickedVertices[min_index] = true;

        // Update distance value
        for (int vertex = 0; vertex < N; vertex++) {
            if ((!pickedVertices[vertex]) && 
                (graph[min_index][vertex]) && 
                (graph[sourceVertex][min_index] != INT_MAX) &&
                (graph[sourceVertex][min_index] + graph[min_index][vertex] < graph[sourceVertex][vertex])) {
                
                graph[sourceVertex][vertex] = graph[sourceVertex][min_index] + graph[min_index][vertex];
            }
        }
    }
    return;
}

int main(int argc, char *argv[]) {
	
    // Get matrix size from argument vector in , convert to int
    N = strtol(argv[1], NULL, 10);

    long** graph;
    graph = (long**) malloc(sizeof(long*) * N);
    for (int i = 0; i < N; ++i)
    {
        graph[i] = (long*) malloc(sizeof(long) * N);
    }
    int numtasks, rank, dest, source, rc, count, tag=1;
    double start_time, end_time, total_time;

    srand(13517115);
	// Fill the matrix with rand() function
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Mod by 100 so the result won't be too big.
            graph[i][j] = rand() % 100;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(i == j || graph[i][j])){
                graph[i][j] = INT_MAX;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j){
                graph[i][j] = 0;
            }
        }
    }

    MPI_Status Stat;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    int jobs = N/(numtasks-1);
    long* dataRecv;
    int destinationRank = 0;
    count = 0;
    if (!rank){
        dataRecv = (long*) malloc(sizeof(long) * N*jobs);
        while(count<numtasks-1){
            MPI_Recv(dataRecv, N*jobs, MPI_LONG, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
            printf("Received from process %d ", Stat.MPI_SOURCE);
            for (int i = 0; i < N*jobs; ++i)
            {
                graph[Stat.MPI_SOURCE*jobs-jobs][i] = dataRecv[i];
            }
            count++;
        }
        free(dataRecv);
    }
    else{
        for (int i = rank*jobs-jobs; i < rank*jobs; ++i)
        {
            dijkstra(graph, i);
            // printf("Print job %d from rank %d\n", i, rank);
        }
        MPI_Send(graph[rank*jobs-jobs], N*jobs, MPI_LONG, destinationRank, tag, MPI_COMM_WORLD);
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    total_time = end_time - start_time;
    MPI_Finalize();
    if (rank == 0) {
        printf("%f\n", total_time);
    }
    for (int i = 0; i < N; ++i)
    {
        free(graph[i]);
    }
    free(graph);
}
