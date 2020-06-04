#include <string.h>
#include <stdio.h>
#include "mpi.h"

// To be tested

main(int argc, char **argv) {
  int myrank;
  char message[100];
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  if (myrank%2 == 0) {
    sprintf(message, "Hello there from rank: %d", myrank);
    printf("Sender process will send this message: %s", message);
    MPI_Send(message, strlen(message) + 1, MPI_CHAR, myrank+1, 99, MPI_COMM_WORLD);
  }
  else {
    MPI_Recv(message, 100, MPI_CHAR, myrank-1, 99, MPI_COMM_WORLD, &status);
    // Retrieve the number of elements
    int count;
    printf("My rank: %d \n", myrank);
    MPI_Get_count(&status, MPI_CHAR, &count);
    printf("Number of elements retrieved from the message received: %d.\n", count);
    printf("\tReceived: %s \n", message);
  }
  MPI_Finalize();
}