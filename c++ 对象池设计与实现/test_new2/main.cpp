#include <iostream>
#include <test_new2/a.h>

int main()
{
    A * a = new A();

    delete a;

    return 0;
}
