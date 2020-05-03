#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring> // strcmp()

#include <bits/stdc++.h> // system()

#include <sys/wait.h> // waitpid(), wait()

#include "lock_functions.h" // lock unlock()

int citesteSir(int s[]);

void write_to_file(int size, int s[], char* filename);

void read_from_file(int* size, int s[], char* filename);

void mergeSort(int arr[], int l, int r);

int main(void) {
  char comm[80], *fisier_nesortat = "nesortat.txt", *fisier_sortat="sortat.txt";
  int sir[100], N;
  pid_t pid_child;
  FILE * file_pointer;
  system("clear");
  do {
    printf("SERVER$ ");
    scanf("%s", comm);
    // Daca este comanda de Sortare
    if (strcmp(comm, ":s") == 0) {
      N = citesteSir(sir);
      printf("Sirul preluat are %d elemente\n", N);

      // Scriere in fisier:
      write_to_file(N, sir, fisier_nesortat);
      // Fork
      pid_child = fork();
      if(pid_child == 0)
      {
      // marcheaza faptul ca incepe sortarea
      //      - blochez semaforul
      if(!lock("semafor"))
      {
        // daca da eroare cu :: No such file or directory, trebuie sa ii dam o cale absoluta la LOCKDIR din lock_functions.h
        // nu se poate face lock
        printf("Lock pentru sortare nu poate face\n");
        exit(1);
      }
      // daca sunt fiu ...
      //      - citesc din fisier
      //      - sortez
      //      - copii sirul sortat in fisierul sortat.txt
      //      - deblochez semaforul
      //      - exit();
      int size;
      int sir_nesoratat[50];
      printf("Copilul citeste sirul din fisier.\n");
      read_from_file(&size,sir_nesoratat,fisier_nesortat );
      // Sortez
      printf("Copilul sorteaza sirul.\n");
      mergeSort(sir_nesoratat,0, size-1);
      // scriere in fisir sortat
      printf("Copilul scrie sirul in fisier.\n");
      write_to_file(size, sir_nesoratat, fisier_sortat);
      unlock("semafor");
      exit(0);
      }
      else
      {
        int status;
        wait(&status);
        if(status != 0)
        {
          // Facem asta, sa evitam cazul in care parintele ajunge sa faca lock inainte de copil.
          // fiul a facut exit(0) => status == 0
          printf("A fost o problema cu inchiderea procesului copil.\n");
        }
        // daca sunt parinte astept finalizarea sortarii, prin
        //      - testarea semaforului, daca s-a deblocat
        if(!lock("semafor"))
        {
          // daca da eroare cu :: No such file or directory, trebuie sa ii dam o cale absoluta la LOCKDIR din lock_functions.h
          // nu se poate face lock
          printf("Lock pentru citirea sirului sortat nu poate face");
          exit(1);
        }
        printf("Parintele poate citi sirul sortat. \n");
        read_from_file(&N,sir,fisier_sortat );
        unlock("semafor");
      }
      // Afisez - deoarece doar parintele ajunge aici
      printf("Sir sortat: \n");
      for(int index = 0; index < N; index++)
      {
        printf("%d ", sir[index]);
      }
      printf("\n");
    } else if (strcmp(comm, ":q") == 0) {
      printf("FINISH\n");
      return 0;
    } else if (strcmp(comm, ":c") == 0)
      system("clear");
    else if (strcmp(comm, ":h") == 0)
      printf("\tHELP\n\t:q - parasire program"
             "\n\t:h - Help"
             "\n\t:c - stergere ecran"
             "\n\t:s - preluare sir + sortare\n");
    else
      printf("Comanda necunoscuta!\nFolositi ':h'"
             " pentru Help.\n");
  } while (!0);

  return 0;
}

int citesteSir(int s[]) {
  int n = 0, i;
  printf("\tIntrodu nr. de elemente: ");
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    printf("S[ %d ] = ", i);
    scanf("%d", &s[i]);
  }
  return n;
}


void write_to_file(int size, int s[], char* filename)
{
  fprintf(stderr, "Writing to file: %s\n", filename);
  FILE * file_pointer;
  file_pointer = fopen(filename, "wt"); 
  if (file_pointer == NULL)
  {
    fprintf(stderr, "File <%s> can't be open\n", filename);          
    exit(-1);
  }
  fprintf(file_pointer,"%d ",size);
  for (int i = 0; i < size; i++)
  {
    fprintf(file_pointer,"%d ",s[i]);
  }
  fclose(file_pointer);
  printf("\n");
}

void read_from_file(int* size, int s[], char* filename)
{
  fprintf(stderr, "Reading from file: %s\n", filename);
  FILE * file_pointer;
  file_pointer = fopen(filename, "rt"); 
  if (file_pointer == NULL)
  {
    fprintf(stderr, "File <%s> can't be open\n", filename);          
    exit(-1);
  }
  fscanf(file_pointer,"%d ",size);
  printf("Putem citi: %d elemente\n", *size);
  for (int i = 0; i < *size; i++)
  {
    fscanf(file_pointer,"%d ",&s[i]);
    printf("%d ", s[i]);
  }
  printf("\n");
  fclose(file_pointer);
}

// https://www.geeksforgeeks.org/c-program-for-merge-sort/
// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 