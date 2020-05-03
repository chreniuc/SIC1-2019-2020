#include <stddef.h> // NULL
#include <string.h> // strcpy
#include <stdlib.h> // malloc
#include <stdio.h> // printf
#include "functii.h" // stack

int main()
{
    stack stiva;

    stiva.begin = NULL;
    stiva.size = 0;
    // Push two elements and then remove them.
    element_ptr first_element = (element_ptr) malloc( sizeof(element) );
    strcpy(first_element->data, "Second");
    push(&stiva, first_element);

    first_element = (element_ptr) malloc( sizeof(element) );
    strcpy(first_element->data, "First");
    push(&stiva, first_element);
    // Print and free the elements
    printf("Content: %s. Stack size: %d\n", top(&stiva)->data, stiva.size);
    free(pop(&stiva));
    printf("Content: %s. Stack size: %d\n", top(&stiva)->data, stiva.size);
    free(pop(&stiva));
    printf("Stack size: %d\n", stiva.size);
    return 0;
}