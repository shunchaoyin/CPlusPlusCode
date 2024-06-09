#include <iostream>
#include <test_new/a.h>

int main()
{
    A * a = new A();

    delete a;

    return 0;
}
