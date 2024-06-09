#include <iostream>
#include <test_malloc/a.h>

int main()
{
    A * a = new A(0);
    a->show();

    delete a;

    return 0;
}
