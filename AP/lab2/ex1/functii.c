#include <stddef.h>

#include "functii.h"

void push(stack* stack_, element_ptr element_to_be_added)
{
    if(stack_->begin == NULL)
    {
        stack_->begin = element_to_be_added;
        stack_->size = 1;
        return;
    }
    element_ptr previous_begining = stack_->begin;
    stack_->begin = element_to_be_added;
    stack_->begin->next = previous_begining;
    stack_->size++;
}

element_ptr top(stack* stack_)
{
    return stack_->begin;
}

element_ptr pop(stack* stack_)
{
    if(stack_->begin == NULL)
    {
        return NULL;
    }
    element_ptr first_element = stack_->begin;
    stack_->begin = first_element->next;
    stack_->size--;
    return first_element;
}