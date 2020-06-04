#include <iostream>

using namespace std;
#include "mpi.h"

bool is_palindrom(int number);

// To be tested

main(int argc, char **argv) {
  int myrank;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  int master_rank = 0;
  // Get number of processes.
  int number_of_processes;
  MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);

  if (myrank == master_rank) {
    // Master rank
    int* numbers_from_console;
    int size_of_vector;
    cout << "[Master] Insert size of vector: " ;
    cin >> size_of_vector;
    cout << endl;
    numbers_from_console = new int[size_of_vector];
    if(size_of_vector < number_of_processes - 1)
    {
      printf("[Master] Insert at least 1 number per process.\n");
      delete[] numbers_from_console;
      exit(-1);
    }
    int chars_per_process = size_of_vector/ (number_of_processes -1);
    if(chars_per_process * (number_of_processes-1) < size_of_vector)
    {
      // if we get 7 numbers and we have 2 processes, we will allocate 4 numbers to each one.
      chars_per_process++;
    }
    cout << "[Master] Insert the numbers: " ;
    for(int i =0; i < size_of_vector; i++)
    {
        cin >> numbers_from_console[i];
    }

    cout << "[Master] Contents of vector: ";
    for(int i =0; i < size_of_vector; i++)
    {
        cout << numbers_from_console[i] << " ";
    }
    cout << endl;

    int superior_limit, inferior_limit;
    superior_limit = 0;
    inferior_limit = 0;
    for(int i = 0; i < number_of_processes - 1; i++)
    {
      superior_limit = i*chars_per_process + chars_per_process;
      if(superior_limit > size_of_vector)
      {
        // This is the last chunk of chars that should be sent,
        // we will send the rest.
        chars_per_process = size_of_vector%chars_per_process;
      }
      // send
      MPI_Send(numbers_from_console + inferior_limit, chars_per_process, MPI_INT,
        i+1, 99, MPI_COMM_WORLD);
      inferior_limit = superior_limit;
    }
    
    cout << "[Master] All work has been distributed to the slaves. Waiting for results." <<endl;
    int values[2];
    int number_of_palindroms = 0;
    int sum_of_palindroms = 0;

    int value_received;
    int number_of_vowels = 0;
    for(int i = 0; i < number_of_processes - 1; i++)
    {
      // Read results from slaves
      MPI_Recv(values, 2, MPI_INT, MPI_ANY_SOURCE, 99, MPI_COMM_WORLD, &status);
      cout << "[Master] Received from a slave the number of palindroms: "<< values[0] << ". And the sum: " <<  values[1] << endl;
      number_of_palindroms +=values[0];
      sum_of_palindroms +=values[1];
    }
    cout << "============================================================================" << endl;
    cout << "[Master] The total number of palindroms is: " << number_of_palindroms << ". The sum is: " << sum_of_palindroms << endl;
  }
  else {
    // slave
    int numbers_from_master[100];
    MPI_Recv(numbers_from_master, 100, MPI_INT, master_rank, 99, MPI_COMM_WORLD, &status);
    // Retrieve the number of elements
    int count;
    MPI_Get_count(&status, MPI_INT, &count);
    cout << "[Slave: "<< myrank<< "] Number of elements retrieved from the message received: "<< count<< "." << endl;
    cout << "[Slave: "<< myrank<< "] Received: " << endl;
    for(int i =0; i < count; i++)
    {
        cout << numbers_from_master[i] << " ";
    }
    cout << endl;
    cout << "[Slave: "<< myrank<< "] Preparing to start doing work." << endl;

    int number_of_palindroms = 0;
    int sum_of_palindroms = 0;
    for(int i = 0; i < count; i++)
    {
      if(is_palindrom(numbers_from_master[i]))
      {
        number_of_palindroms++;
        sum_of_palindroms+= numbers_from_master[i];
      }
    }
    cout << "[Slave: "<< myrank<< "] Finished work. Number of palindroms: " << ". Sum of palindroms: " << sum_of_palindroms<< ". Sending to master" << endl;
    int values[2];
    values[0] = number_of_palindroms;
    values[1] = sum_of_palindroms;
    MPI_Send(values , 2, MPI_INT, master_rank, 99, MPI_COMM_WORLD);
  }
  MPI_Finalize();
}


bool is_palindrom(int number)
{
    int n = number;
    int digit = 0;
    int rev = 0;
    do
    {
        digit = number % 10;
        rev = (rev * 10) + digit;
        number = number / 10;
    } while (number != 0);
    if(n == rev)
    {
        return true;
    }
    return false;
}