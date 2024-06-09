#include <iostream>
#include <test_array/a.h>

int main()
{
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
