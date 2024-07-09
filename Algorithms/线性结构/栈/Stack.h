#include <stdio.h>

#define STACK_CAPACITY 3
#define ERROR_RET 0XEFEFEFEF



class Stack
{
private:
    int _stack[STACK_CAPACITY];
    int _top;

public:
    Stack();
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    int top() const;
    void push(int e);
    void pop();
};