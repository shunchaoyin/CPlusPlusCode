#pragma once

#include <object/object_pool.h>
#include <object/allocator/malloc_allocator.h>
using namespace yazi::object;

class A
{
private:
    typedef ObjectPool<A, MallocAllocator<A>> ObjectPool;
    static ObjectPool pool;
public:
    A() : m_data(0)
    {
    }
    explicit A(int data) : m_data(data)
    {
        std::cout << "A construct" << std::endl;
    }

    virtual ~A()
    {
        std::cout << "A destruct" << std::endl;
    };

    void show() const
    {
        std::cout << "A: " << m_data << std::endl;
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
