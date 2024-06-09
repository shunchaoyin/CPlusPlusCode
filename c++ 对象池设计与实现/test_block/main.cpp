#include <iostream>
#include <test_block/a.h>

const int max_size = 8;

int main()
{
    std::cout << sizeof(A) << std::endl;
    std::cout << sizeof(A *) << std::endl;

    A * arr[max_size] = {nullptr};
    for (int i = 0; i < max_size; i++)
    {
        A * a = new A(i);
        arr[i] = a;
    }

    for (int i = 0; i < max_size; i++)
    {
        std::cout << "[" << i << "]" << " = " << arr[i] << std::endl;
    }

    for (int i = 0; i < max_size; i++)
    {
        delete arr[i];
    }

    for (int i = 0; i < max_size; i++)
    {
        A * a = new A(i);
        arr[i] = a;
    }

    for (int i = 0; i < max_size; i++)
    {
        std::cout << "[" << i << "]" << " = " << arr[i] << std::endl;
    }

    return 0;
}
