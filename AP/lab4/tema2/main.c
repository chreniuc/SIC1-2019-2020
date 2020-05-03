#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mpi.h"

int is_vowel(char c);

// To be tested

main(int argc, char **argv) {
  int myrank;
  char message[100];
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  int master_rank = 0;
  // Get number of processes.
  int number_of_processes;
  MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);

  if (myrank == master_rank) {
    // Master rank
    char message_from_console[100];
    printf("[Master] Insert phrase: ");
    fflush(stdin);
    scanf("%s", message_from_console);
    printf("\n");
    int size_of_string;
    size_of_string = strlen(message_from_console);
    printf("\n");
    if(size_of_string < number_of_processes - 1)
    {
      printf("[Master] Insert a string that has at least 1 char per process.\n");
      exit(-1);
    }
    int chars_per_process = size_of_string/ (number_of_processes -1);
    if(chars_per_process * (number_of_processes-1) < size_of_string)
    {
      // if we get 7 chars and we have 2 processes, we will allocate 4 chars to each one.
      chars_per_process++;
    }

    int superior_limit, inferior_limit;
    superior_limit = 0;
    inferior_limit = 0;
    for(int i = 0; i < number_of_processes - 1; i++)
    {
      superior_limit = i*chars_per_process + chars_per_process;
      if(superior_limit > size_of_string)
      {
        // This is the last chunk of chars that should be sent,
        // we will send the rest.
        chars_per_process = size_of_string%chars_per_process;
      }
      // send
      MPI_Send(message_from_console + inferior_limit, chars_per_process, MPI_CHAR,
        i+1, 99, MPI_COMM_WORLD);
      inferior_limit = superior_limit;
    }
    
    printf("[Master] All work has been distributed to the slaves. Waiting for results.\n")
    int value_received;
    int number_of_vowels = 0;
    for(int i = 0; i < number_of_processes - 1; i++)
    {
      // Read results from slaves
      MPI_Recv(value_received, 1, MPI_INT, MPI_ANY_SOURCE, 99, MPI_COMM_WORLD, &status);
      printf("[Master] Received from a slave the number of vowels: %d\n", value_received);
      number_of_vowels = number_of_vowels + value_received;
    }

    printf("[Master] Total number of vowels is: %d\n", number_of_vowels);
  }
  else {
    // slave
    MPI_Recv(message, 100, MPI_CHAR, master_rank, 99, MPI_COMM_WORLD, &status);
    // Retrieve the number of elements
    int count;
    MPI_Get_count(&status, MPI_CHAR, &count);
    message[count] = '\0';
    printf("[Slave: %d] Number of elements retrieved from the message received: %d.\n",myrank, count);
    printf("[Slave: %d] Received: %s \n",myrank, message);
    printf("[Slave: %d] Preparing to start doing work.\n",myrank);
    int number_of_vowels = 0;
    for(int i = 0; i < count; i++)
    {
      if(is_vowel(message[i]) == 1)
      {
        number_of_vowels++;
      }
    }
    printf("[Slave: %d] Finished work. Number of vowels found: %d. Sending to master.\n",myrank, number_of_vowels);
    MPI_Send(number_of_vowels , 1, MPI_CHAR, master_rank, 99, MPI_COMM_WORLD);
  }
  MPI_Finalize();
}

int is_vowel(char ch)
{
  // https://www.programmingsimplified.com/c/source-code/c-program-check-vowel
  if(isalpha(ch) && (ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' ||
   ch == 'i' || ch == 'I' || ch =='o' || ch=='O' || ch == 'u' || ch == 'U'))
  {
    return 1;
  }
  return 0;
}