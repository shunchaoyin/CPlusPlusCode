#include <iostream>
#include <exception>
#include <cassert>
using namespace std;

// 1-10 为一个二维数组分配储存空间
template <typename T>
bool make2dArray(T **&x, int numberOfRows, int numberOfColumns)
{
    try
    {
        x = new T *[numberOfRows];
        for (int i = 0; i < numberOfRows; i++)
        {
            x[i] = new T[numberOfColumns];
        }
        return true;
    }
    catch (bad_alloc)
    {
        return false;
    }
}
// 1-11 创建一个数组，没有异常处理,这样反而更合理,异常处理放在下面的函数
template <typename T>
void make2dArray2(T **&x, int numberOfRows, int numberOfColumns)
{
    x = new T *[numberOfRows];
    for (int i = 0; i < numberOfRows; i++)
    {
        x[i] = new T[numberOfColumns];
    }
}

// try
// {
//     make2dArray2(x, r, c);
// }
// catch(_THROW_BAD_ALLOC)
// {
//     cerr << "could not create x" << endl;
// }

// 1-12 释放在函数make2array中分配的空间
template <typename T>
void delete2dArray(T **&x, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; i++)
    {
        delete[] x[i];
    }

    delete[] x;
    x = nullptr;
}

// practice
// 12
template <typename T>
void make2dArray3(T **&x, int numberOfRows, const T *rowSize)
{
    x = new T *[numberOfRows];
    for (int i = 0; i < numberOfRows; i++)
    {
        x[i] = new T[rowSize[i]];
    }
}

// 13
template <typename T>
T *changeLength1D(T *array, int oldLength, int newLength)
{
    T *newArray = new T[newLength];
    int minLength = min(oldLength, newLength);
    for (int i = 0; i < minLength; i++)
    {
        newArray[i] = array[i];
    }
    delete[] array;
    return newArray;
}

// 14 偷懒假设是n*n数组
template <typename T>
T **changeLength2D(T **&array, int oldLength, int newLength)
{
    T **newArray;
    newArray = new int *[newLength];
    for (int i = 0; i < newLength; i++)
    {
        newArray[i] = new int[newLength];
    }
    int minLength = min(oldLength, newLength);

    for (int i = 0; i < minLength; i++)
    {
        for (int j = 0; j < minLength; j++)
        {
            newArray[i][j] = array[i][j];
        }
    }

    for (int i = 0; i < oldLength; i++)
    {
        delete[] array[i];
    }
    delete[] array;
    return newArray;
}

int main()
{
    int *array = new int[5]{1, 2, 3, 4, 5};
    int oldLength = 5;
    int newLength = 3;
    int *newArray = changeLength1D(array, oldLength, newLength);
    assert(newArray[0] == 1);
    assert(newArray[1] == 2);
    assert(newArray[2] == 3);
    delete[] newArray;

    int **array2D;
    array2D = new int *[3];
    for (int i = 0; i < 3; i++)
    {
        array2D[i] = new int[3]{1,2,3};
    }
    int **new2Array = changeLength2D(array2D, 3, 2);

    delete[] new2Array[0];
    delete[] new2Array[1];
    delete[] new2Array;

    return 0;
}
