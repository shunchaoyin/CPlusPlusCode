#include <exception>
#include <iostream>
#include <string>

int abc(int a, int b, int c)
{
    if (a < 0 && b < 0 && c < 0)
    {
        throw 1;
    }
    if (a == 0 && b == 0 && c == 0)
    {
        throw 2;
    }
    return a + b * c;
}

template <typename T>
int cal_counts(const T *array, T val, int n)
{
    if (n < 1)
        throw "n is little than 1 .";
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] == val)
            count++;
    }
    return count;
}

int main()
{
    // 10
    try
    {
        // std::cout << abc(0, 0, 0) << std::endl;
    }
    catch (int e) // becareful this const
    {
        if (e == 1)
        {
            std::cerr << "the parameter to abc all were little than 0" << std::endl;
        }
        if (e == 2)
        {
            std::cerr << "the parameters to abc all were 0!" << std::endl;
        }
        return 1;
    }

    // 11
    try
    {
        int array[5] = {1};
        int n = 0;
        cal_counts(array, 1, n);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }

    return 0;
}
