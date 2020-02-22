#include "mpi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

int NUMBER_OF_VERTICES = 0;

long getVertexWithMinDistance(long dist[], bool pickedVertices[]) {
  long minDistance = LONG_MAX;
  int vertexWithMinDistance = -1;

  for (int vertex = 0; vertex < NUMBER_OF_VERTICES; vertex++) {
    if (!pickedVertices[vertex] && dist[vertex] <= minDistance) {
      minDistance = dist[vertex];
      vertexWithMinDistance = vertex;
    }
  }
  return vertexWithMinDistance;
}

void dijkstra(int graph[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES], int sourceVertex) {

  // Distance from single source to all of the nodes
  long dist[NUMBER_OF_VERTICES];
  bool pickedVertices[NUMBER_OF_VERTICES];

  for (int vertex = 0; vertex < NUMBER_OF_VERTICES; vertex++) {
    if (vertex == sourceVertex) {
      dist[vertex] = 0; 
    } else {
      // Initialize all distance to be infinity.
      dist[vertex] = LONG_MAX;
    }
    pickedVertices[vertex] = false;
  }

  for (int iteration = 0; iteration < NUMBER_OF_VERTICES - 1; iteration++) {
    // Get minimum distance
    int vertexWithMinDistance = getVertexWithMinDistance(dist, pickedVertices);

    // Mark the vertice as picked
    pickedVertices[vertexWithMinDistance] = true;

    // Update distance value
    for (int vertex = 0; vertex < NUMBER_OF_VERTICES; vertex++) {
      if (!pickedVertices[vertex] && graph[vertexWithMinDistance][vertex] && dist[vertexWithMinDistance] != LONG_MAX && dist[vertexWithMinDistance] + graph[vertexWithMinDistance][vertex] < dist[vertex]) {
        dist[vertex] = dist[vertexWithMinDistance] + graph[vertexWithMinDistance][vertex];
      }
    }
  }

  // Edit the real graph
  for (int vertex = 0; vertex < NUMBER_OF_VERTICES; vertex++) {
    graph[sourceVertex][vertex] = dist[vertex];
  }

  // Print solution
  for (int vertex = 0; vertex < NUMBER_OF_VERTICES; vertex++) {
    // printf("%d to %ld\n", vertex, dist[vertex]);
    printf("%d to %d\n", vertex, graph[sourceVertex][vertex]);
  }
}

int main(int argc, char *argv[]) {

  // Get matrix size from argument vector in , convert to int
  NUMBER_OF_VERTICES = strtol(argv[1], NULL, 10);

  // Initialize matrix
  int graph[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES];

  // Seed with NIM: Edward Alexander Jaya
  srand(13517115);
  // Fill the matrix with rand() function
  for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
    for (int j = 0; j < NUMBER_OF_VERTICES; j++) {
      // Mod by 100 so the result won't be too big.
      graph[i][j] = rand() % 100;
    }
  }

  // Test function
  
  // for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
  //   for (int j = 0; j < NUMBER_OF_VERTICES; j++) {
  //     scanf("%d", &graph[i][j]);
  //   }
  // }

  // graph = { 0, 4, 0, 0, 0, 0, 0, 8, 0,
  //           4, 0, 8, 0, 0, 0, 0, 11, 0, 
  //           0, 8, 0, 7, 0, 4, 0, 0, 2, 
  //           0, 0, 7, 0, 9, 14, 0, 0, 0, 
  //           0, 0, 0, 9, 0, 10, 0, 0, 0, 
  //           0, 0, 4, 14, 10, 0, 2, 0, 0, 
  //           0, 0, 0, 0, 0, 2, 0, 1, 6, 
  //           8, 11, 0, 0, 0, 0, 1, 0, 7, 
  //           0, 0, 2, 0, 0, 0, 6, 7, 0 };

  dijkstra(graph, 1); 

  // Print function
  printf("Matrix: \n");
  for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
    for (int j = 0; j < NUMBER_OF_VERTICES; j++) {
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }

  // Send argument vector
  MPI_Init(&argc, &argv);
  // dijkstra(graph, 0); 
  MPI_Finalize();
} 
