#include "Array.h"
#include <iostream>

void Array::copyFrom(int const *A, int low, int high)
{
    if (_capacity < high - low + 1)
    {
        if (NULL != _elems)
        {
            delete[] _elems;
            _size = high - low + 1;
            _elems = new int[_size];
        }
    }

    for (int i = low; i < high; i++)
    {
        _elems[i] = A[i];
    }
}

void Array::expand()
{
    _capacity *= DEFAULT_EXPAND_FACTOR;
    int *oldElems = _elems;
    _elems = new int[_capacity];
    copyFrom(oldElems, 0, _size);
    delete[] oldElems;
}
void Array::shrink()
{
    _capacity *= DEFAULT_SHRINK_FACTOR;
    int *oldElems = _elems;
    _elems = new int[_capacity];
    copyFrom(oldElems, 0, _size);
    delete[] oldElems;
}
void Array::exchange(int a, int b)
{
    int tmp = _elems[a];
    _elems[a] = _elems[b];
    _elems[b] = tmp;
}
int Array::find(int e, int low, int high) const
{
    if (high > _size - 1)
    {
        high = _size - 1;
    }
    for (int i = low; i < high; i++)
    {
        if (_elems[i] == e)
        {
            return i;
        }
    }
    return -1;
}

Array::Array(int c, int s, int v)
    : _capacity(c), _size(s)
{
    if (NULL == _elems)
    {
        _elems = new int[_capacity];
    }
    for (int i = 0; i < _size; i++)
    {
        _elems[i] = v;
    }
}
Array::Array(int const *A, int size)
{
    if (NULL == _elems)
    {
        _elems = new int[size];
        _capacity = size;
        _size = size;
    }
    copyFrom(A, 0, size);
}
Array::Array(const Array &v)
{
    if (NULL == _elems)
    {
        _capacity = v._capacity;
        _size = v._size;
        _elems = new int[_capacity];
    }
    copyFrom(v._elems, 0, v._size);
}
Array::~Array()
{
    delete[] _elems;
}
int &Array::operator[](int i) const
{
    return _elems[i];
}
int Array::size() const
{
    return _size;
}
int Array::capacity() const
{
    return _capacity;
}
bool Array::isEmpty() const
{
    return _size ? true : false;
}
bool Array::isOrdered() const
{
    for (int i = 0; i < _size - 1; i++)
    {
        if (_elems[i] > _elems[i + 1])
        {
            return false;
        }
    }
    return true;
}
bool Array::find(int e) const
{

    if (-1 == find(e, 0, _size))
    {
        return false;
    }
    else
    {
        return true;
    }
}
int Array::binarySearch(int e) const
{
    if (!isOrdered())
    {
        std::cout << "this array needs to be sorted!" << std::endl;
        return -1;
    }
    int low = 0;
    int left = 0;
    int right = _size - 1;
    int middle = 0;

    while (left <= right)
    {
        middle = (left + right) / 2;

        if (_elems[middle] > e)
        {
            right = middle - 1;
        }
        else if (_elems[middle] < e)
        {
            left = middle - 1;
        }
        else
        {
            return middle;
        }
    }
    return -1;
}

int Array::remove(int low, int high)
{
    if (high > _size - 1)
    {
        high = _size - 1;
    }
    int delta = high - low + 1;
    for (int i = low; i < low + delta; i++)
    {
        _elems[i] = _elems[i + delta];
    }
    _size = _size - delta;
    if (_size < _capacity * DEFAULT_SHRINK_FACTOR)
    {
        shrink();
    }
    return 0;
}

int Array::insert(int pos, int e)
{
    if (pos > _size)
    {
        pos = _size;
    }
    if (_size + 1 > _capacity)
    {
        expand();
    }
    for (int i = _size; i > pos; i--)
    {
        _elems[i] = _elems[i - 1];
    }
    _elems[pos] = e;
    _size++;
    return 0;
}
void Array::push_back(int e)
{
    insert(_size, e);
}
void Array::sort()
{
    for (int i = 0; i < _size - 1; i++)
    {
        for (int j = i; j < _size; j++)
        {
            if (_elems[i] < _elems[j])
            {
                exchange(i, j);
            }
        }
    }
}
void Array::shuffle()
{
    for (int i = 0; i < _size - 1; i++)
    {
        exchange(i, rand() % i);
    }
}
void Array::print()
{
    std::cout << "capacit :" << _capacity << std::endl;
    std::cout << "_size :" << _size << std::endl;
}