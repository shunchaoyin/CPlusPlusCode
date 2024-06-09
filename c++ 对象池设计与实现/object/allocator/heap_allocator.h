#pragma once

#include <algorithm>
#include <object/allocator.h>

namespace yazi
{
    namespace object
    {
        template <typename T, int N>
        class HeapAllocator : public Allocator<T>
        {
        public:
            enum State
            {
                FREE = 1,
                USED = 0
            };

            struct Entry
            {
                State state;
                T * p;

                // compare operator, needed for heap book keeping
                bool operator < (const Entry & other) const
                {
                    return state < other.state;
                }
            };

            HeapAllocator()
            {
                // number of available memory chunks is the size of the memory pool
                m_available = N;

                // all memory chunks are free, pointers are initialized
                for (int i = 0; i < N; i++)
                {
                    m_entry[i].state = FREE;
                    m_entry[i].p = reinterpret_cast<T *>(&m_data[sizeof(T) * i]);
                }

                // make heap of book keeping array
                std::make_heap(m_entry, m_entry + N);
            }

            ~HeapAllocator() = default;

            virtual T * allocate()
            {
                // allocation not possible if memory pool has no more space
                if (m_available <= 0)
                    throw std::bad_alloc();

                // the first memory chunk is always on index 0
                Entry e = m_entry[0];

                // remove first entry from heap
                std::pop_heap(m_entry, m_entry + N);

                // one memory chunk allocated, no more available
                m_available--;

                // mark the removed chunk
                m_entry[m_available].state = USED;
                m_entry[m_available].p = nullptr;

                // return pointer to the allocated memory
                return e.p;
            }

            virtual void deallocate(T * p)
            {
                // invalid pointers are ignored
                if (p == nullptr || m_available >= N)
                    return;

                // mark freed memory as such
                m_entry[m_available].state = FREE;
                m_entry[m_available].p = reinterpret_cast<T *>(p);

                // freed memory chunk, one more available
                m_available++;

                // heap book keeping
                std::push_heap(m_entry, m_entry + N);
            }

        private:
            unsigned char m_data[sizeof(T) * N];
            Entry m_entry[N];
            int m_available;
        };
    }
}