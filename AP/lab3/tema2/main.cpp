#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring> // strcmp()

#include <bits/stdc++.h> // system()

#include <sys/wait.h> // waitpid(), wait()

#include "lock_functions.h" // lock unlock()

int main(void) {
  char comm[80], *fisier = "sortat.txt";
  pid_t pid_child;
  system("clear");
  FILE * file_pointer;
  int nr_1, nr_2;
  do {
    printf("SERVER$ ");
    scanf("%s", comm);
    // Daca este comanda de Sortare
    if (strcmp(comm, ":s") == 0) {

      // marcheaza faptul ca incepe sortarea
      //      - blochez semaforul
      if(!lock("semafor"))
      {
        // daca da eroare cu :: No such file or directory, trebuie sa ii dam o cale absoluta la LOCKDIR din lock_functions.h
        // nu se poate face lock
        printf("Procesul parinte nu poate face lock");
        exit(1);
      }
      // Fork
      pid_child = fork();

      if(pid_child == 0)
      {
        // child
        if(!lock("semafor"))
        {
          // nu se poate face lock
          printf("Procesul copil nu poate face lock");
          exit(1);
        }
        int nr1_1, nr2_2;
        file_pointer = fopen(fisier, "rt"); 
        if (file_pointer == NULL)
        {
          fprintf(stderr, "File <%s> can't be open\n", fisier);          
          break;
        }
        fscanf(file_pointer,"%d",&nr1_1);
        fscanf(file_pointer,"%d",&nr2_2);
        fclose(file_pointer);

        printf("Numere citite: %d, %d\n", nr1_1, nr2_2);
        printf("Suma lor: %d\n", (nr1_1+ nr2_2));
        unlock("semafor");
        exit(0);
      }
      else
      {
        printf("\n\tIntrodu nr_1: ");
        scanf("%d", &nr_1);
        printf("\n\tIntrodu nr_2: ");
        scanf("%d", &nr_2);
        file_pointer = fopen(fisier, "wt"); 
        if (file_pointer == NULL)
        {
          fprintf(stderr, "File <%s> can't be open\n", fisier);          
          break;
        }
        fprintf(file_pointer,"%d ",nr_1);
        fprintf(file_pointer,"%d",nr_2);
        fclose(file_pointer);
        unlock("semafor");
      }
      // Afisez - deoarece doar parintele ajunge aici
      int status;
      wait(&status);
      if(status == 0)
      {
        // fiul a facut exit(0) => status == 0
        printf("Suma a fost afisata mai sus.\n");
      }


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