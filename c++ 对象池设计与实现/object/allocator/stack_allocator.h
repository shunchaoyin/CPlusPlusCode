#pragma once

#include <array>
#include <object/allocator.h>

namespace yazi
{
    namespace object
    {
        template <typename T, int N>
        class StackAllocator : public Allocator<T>
        {
        public:
            StackAllocator()
            {
                m_allocated = 0;
                m_available = 0;
            }

            ~StackAllocator() = default;

            virtual T * allocate()
            {
                if (m_available <= 0 && m_allocated >= N)
                {
                    // no free memory chunks could be found
                    throw std::bad_alloc();
                }

                // Check if stack has available slots
                if (m_available > 0)
                {
                    // Return the next empty slot from the stack.
                    return m_stack[--m_available];
                }
                else
                {
                    // Make new slot available and return it.
                    auto p = m_data + sizeof(T) * m_allocated;
                    m_allocated++;
                    return reinterpret_cast<T *>(p);
                }
            }

            virtual void deallocate(T * p)
            {
                // Place the pointer back to the stack.
                m_stack[m_available++] = p;
            }

        private:
            unsigned char m_data[sizeof(T) * N];
            std::array<T *, N> m_stack;
            int m_allocated;
            int m_available;
        };
    }
}