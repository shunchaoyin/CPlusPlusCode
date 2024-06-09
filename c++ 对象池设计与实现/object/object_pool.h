#pragma once

namespace yazi
{
    namespace object
    {
        template <typename T, typename Allocator>
        class ObjectPool
        {
        public:
            ObjectPool() = default;
            ~ObjectPool() = default;

            void * allocate(size_t n)
            {
                if (sizeof(T) != n)
                    throw std::bad_alloc();
                return m_allocator.allocate();
            }

            void deallocate(void * p)
            {
                m_allocator.deallocate(static_cast<T *>(p));
            }

        private:
            Allocator m_allocator;
        };
    }
}