#include "mpi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

int N = 5000;

int getmin_index(short **graph, bool pickedVertices[N], int sourceVertex) {
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

void print(short **graph){
    printf("Matrix: \n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(short **graph, int sourceVertex) {

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
	
    short** graph;
    graph = (short**) malloc(sizeof(short*) * 5000);
    for (int i = 0; i < 5000; ++i)
    {
        graph[i] = (short*) malloc(sizeof(short) * 5000);
    }


    // Get matrix size from argument vector in , convert to int
    printf("pass\n");
    srand(13517115);
	// Fill the matrix with rand() function
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Mod by 100 so the result won't be too big.
            graph[i][j] = 1;
        }
    }
    /*for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(i == j || graph[i][j])){
                graph[i][j] = CHAR_MAX;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j){
                graph[i][j] = 0;
            }
        }
    }*/

    /*for (int i = 0; i < N; ++i)
    {
        dijkstra(graph, i);
        printf("%d\n", i);
    }*/
    print(graph);
    for (int i = 0; i < 5000; ++i)
    {
        free(graph[i]);
    }
    free(graph);
}