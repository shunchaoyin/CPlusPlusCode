#pragma once

#include <object/object_pool.h>
#include <object/allocator/array_allocator.h>
using namespace yazi::object;

const int max_size = 4;

class A
{
private:
    typedef ObjectPool<A, ArrayAllocator<A, max_size>> ObjectPool;
    static ObjectPool pool;
public:
    A() = delete;
    explicit A(int data) : m_data(data)
    {
        std::cout << "A construct: " << m_data << std::endl;
    }
    ~A()
    {
        std::cout << "A destruct: " << m_data << std::endl;
    }

    void * operator new(size_t n)
    {
        std::cout << "A new" << std::endl;
        return pool.allocate(n);
    }

    void operator delete(void * p)
    {
        std::cout << "A delete" << std::endl;
        pool.deallocate(p);
    }

private:
    int m_data;
};

A::ObjectPool A::pool;
