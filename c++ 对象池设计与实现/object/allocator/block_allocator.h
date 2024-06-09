#pragma once

#include <cstring>
#include <object/allocator.h>

namespace yazi
{
    namespace object
    {
        template <typename T, int ChunksPerBlock>
        class BlockAllocator : public Allocator<T>
        {
        public:
            BlockAllocator() : m_head(nullptr) {}
            virtual ~BlockAllocator() = default;

            virtual T * allocate()
            {
                if (m_head == nullptr)
                {
                    if (sizeof(T) < sizeof(T *))
                    {
                        std::cerr << "object size less than pointer size" << std::endl;
                        throw std::bad_alloc();
                    }
                    m_head = allocate_block(sizeof(T));
                }
                Chunk * p = m_head;
                m_head = m_head->next;
                return reinterpret_cast<T *>(p);
            }

            virtual void deallocate(T * p)
            {
                auto chunk = reinterpret_cast<Chunk *>(p);
                chunk->next = m_head;
                m_head = chunk;
            }

        private:
            struct Chunk
            {
                Chunk * next;
            };

            Chunk * allocate_block(size_t chunk_size)
            {
                size_t block_size = ChunksPerBlock * chunk_size;
                auto head = reinterpret_cast<Chunk *>(::malloc(block_size));
                auto chunk = head;
                for (int i = 0; i < ChunksPerBlock - 1; i++)
                {
                    chunk->next = reinterpret_cast<Chunk *>(reinterpret_cast<unsigned char *>(chunk) + chunk_size);
                    chunk = chunk->next;
                }
                chunk->next = nullptr;
                return head;
            }

        private:
            Chunk * m_head;
        };
    }
}