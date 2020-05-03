

typedef struct element{
    char data[10];
    struct element* next;
} element;

typedef element* element_ptr;

typedef struct stack
{
  element_ptr begin;
  unsigned int size;
} stack;

void push(stack* stack_, element_ptr element_to_be_added);

element_ptr top(stack* stack_);

element_ptr pop(stack* stack_);