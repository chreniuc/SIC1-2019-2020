#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_menu()
{
  printf("1. Set file name.\n");
  printf("2. Write string to file.\n");
  printf("3. Read string from file.\n");
  printf("0. Exit.\n");
}
#define MAX_FILE_SIZE 100
#define MAX_FILE_NAME_SIZE 20

void main(void) {
  FILE *file_pointer;
  char file_content[MAX_FILE_SIZE];
  int option = 1;
  char file_name[MAX_FILE_NAME_SIZE];
  while(option != 0)
  {
    system("clear");
    print_menu();
    printf("\nChoose an option: ");
    scanf("%d", &option);
    printf("\nOption: %d\n", option);
    switch(option)
    {
      case 1:
      {
        printf("Insert the file name: ");
        fflush(stdin);
        scanf("%s", file_name);
        //fgets(file_name, MAX_FILE_NAME_SIZE, stdin);
        printf("\n");
        printf("File name: %s\n", file_name);
        getchar();
        getchar();
        break;
      }
      case 2:
      {
        printf("Insert the string to be written in the file: ");
        fflush(stdin);
        scanf("%s", file_content);
        //fgets(file_content, MAX_FILE_SIZE, stdin);
        file_pointer = fopen(file_name, "wb"); 
        if (file_pointer == NULL)
        {
          fprintf(stderr, "File <%s> can't be open\n", file_name);          
          break;
        }
        fputs(file_content,file_pointer );
        fclose(file_pointer);
        printf("String has been written in file.\n");
        strcpy(file_content, "");
        getchar();
        getchar();
        break;
      }
      case 3:
      {
        printf("Reading from file: %s\n",file_name );
        fflush(stdin);
        file_pointer = fopen(file_name, "rb"); 
        if (file_pointer == NULL)
        {
          fprintf(stderr, "File <%s> can't be open\n", file_name);          
          break;
        }
        fgets(file_content,MAX_FILE_SIZE,file_pointer );
        fclose(file_pointer);
        printf("File content: %s\n", file_content);
        getchar();
        getchar();
        break;
      }
      case 0:
      {
        printf("Exiting...\n");
        exit;
      }
      default:
      {
        printf("Unknown option...\n");
        break; 
      }
    }
  }
}