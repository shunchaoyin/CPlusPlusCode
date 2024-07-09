#include "Stack.h"

void error(char* msg)
{
    printf("error:%s", msg);
}

Stack::Stack()
{
    _top = -1;
}

bool Stack::isEmpty() const
{
    return _top < 0;
}

bool Stack::isFull() const
{
    return _top >= STACK_CAPACITY - 1;
}

int Stack::size() const
{
    return _top + 1;
}

int Stack::top() const
{
    if (isEmpty())
    {
        char msg[] = "underflow!";
        error(msg);
        // error("underflow!");
        return ERROR_RET;
    }
    return _stack[_top];
}

void Stack::push(int e)
{
    if (isFull())
    {
        char msg[] = "stack overflow!";
        error(msg);
    }
    else
    {
        _stack[++_top] = e;
    }
}

void Stack::pop()
{
    if (isEmpty())
    {
        char msg[] = "Stack is empty!";
        error(msg);
        return;
    }
    _top--;
}
