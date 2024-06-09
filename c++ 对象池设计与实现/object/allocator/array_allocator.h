#pragma once

#include <object/allocator.h>

namespace yazi
{
    namespace object
    {
        template <typename T, int N>
        class ArrayAllocator : public Allocator<T>
        {
        public:
            ArrayAllocator()
            {
                for (int i = 0; i < N; i++)
                {
                    m_used[i] = false;
                }
            }

            ~ArrayAllocator() = default;

            virtual T * allocate()
            {
                for (int i = 0; i < N; i++)
                {
                    if (!m_used[i])
                    {
                        m_used[i] = true;
                        return reinterpret_cast<T *>(&m_data[sizeof(T) * i]);
                    }
                }

                // no free memory chunks could be found
                throw std::bad_alloc();
            }

            virtual void deallocate(T * p)
            {
                auto i = ((unsigned  char *)p - m_data) / sizeof(T);
                m_used[i] = false;
            }

        private:
            unsigned char m_data[sizeof(T) * N];
            bool m_used[N];
        };
    }
}