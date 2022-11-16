#pragma once

#include <array>
#include <map>
#include <iostream>
#include <algorithm>

#include <assert.h>

const constexpr int PoolSize = 10;

template <typename T, size_t N = PoolSize>
class PoolsManager
{
public:
    using pool_chank= std::array<T, N>;

    static PoolsManager& GetPoolsManager()
    {
        if (pools_manager)
            return *pools_manager;

        pools_manager = new PoolsManager();
        return *pools_manager;
    }

    T* AllocatePool(size_t n)
    {
        for (auto& chunk : memoryPool)
        {
            auto& ar = *chunk.first;
            if (chunk.second + n <= N)
            {
                T* ptr = &ar[0] + chunk.second;

                chunk.second += n;
                return ptr;
            }
        }
        return AppendNewChunk(n);
    }

    void Dealloc(T* p)
    {
        for (auto &ar : memoryPool){
            if(p > ar.first->end())
                continue;
            for (auto it = ar.first->begin(); it!=ar.first->end(); it++){
                if(it == p) {
                    if(--ar.second == 0)
                    {
                        delete ar.first;
                        memoryPool.erase(ar.first);
                    }
                    return;
                }
            }
        }
    }
    PoolsManager()
    {
    }

    ~PoolsManager()
    {
        memoryPool.erase(memoryPool.begin(),memoryPool.end());
    }

private:

    PoolsManager(const PoolsManager&) = delete;
    PoolsManager(PoolsManager&&) = delete;

    PoolsManager& operator = (const PoolsManager&) = delete;
    PoolsManager& operator = (PoolsManager&&) = delete;

    T* AppendNewChunk(size_t n)
    {
        auto newChunk = new pool_chank();
        memoryPool.emplace(std::make_pair(newChunk, n));
        return reinterpret_cast<T*> (newChunk);
    }

private:
    std::map<pool_chank*, size_t> memoryPool;

    static PoolsManager* pools_manager;
};

template <typename T, size_t N>
PoolsManager<T, N>* PoolsManager<T, N>::pools_manager = nullptr;