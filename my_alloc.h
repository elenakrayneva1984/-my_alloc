#ifndef my_alloc_H
#define my_alloc_H
#include <cstddef>

#include "pool.h"

template <typename T, size_t Reserv = PoolSize>
class MyPoolAllocator
{
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    template<typename U>
    struct rebind
    {
        using other = MyPoolAllocator<U, Reserv>;
    };

    MyPoolAllocator() = default;
    MyPoolAllocator(const MyPoolAllocator&) = default;

    ~MyPoolAllocator() {
        PoolsManager<T, Reserv>::GetPoolsManager().~PoolsManager();
    }

    template <typename U, size_type S>
    MyPoolAllocator(const MyPoolAllocator<U, S>&) {}

    MyPoolAllocator& operator = (const MyPoolAllocator& other) = default;
    pointer allocate(size_type n, const void* /*hint*/ = 0);
    void deallocate(pointer p, size_type /*n*/);

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args);

    template<typename U>
    void destroy(U* p);
};

template <typename T, size_t Reserv>
typename MyPoolAllocator<T, Reserv>::pointer MyPoolAllocator<T, Reserv>::allocate(size_type n, const void* )
{
    return PoolsManager<T, Reserv>::GetPoolsManager().AllocatePool(n);
}

template <typename T, size_t Reserv>
void MyPoolAllocator<T, Reserv>::deallocate(pointer p, size_type n)
{
    PoolsManager<T, Reserv>::GetPoolsManager().Dealloc(p);
}

template <typename T, size_t Reserv>
template <typename U, typename... Args>
void MyPoolAllocator<T, Reserv>::construct(U* p, Args&&... args)
{
    new (p) U(std::forward<Args>(args)...);
}

template <typename T, size_t Reserv>
template <typename U>
void MyPoolAllocator<T, Reserv>::destroy(U* p)
{
    p->~U();
}

template<size_t Reserv>
class MyPoolAllocator<void, Reserv>
{
public:
    using value_type = void;
    using pointer = void *;
    using const_pointer = const void *;

    template<typename U>
    struct rebind
    {
        typedef MyPoolAllocator<U, Reserv> other;
    };
};

template<typename T, size_t Reserv, typename U, size_t S>
inline bool operator == (const MyPoolAllocator<T, Reserv>&, const MyPoolAllocator<U, S>&)
{
    return true;
}

template<typename T, size_t Reserv, typename U, size_t S>
inline bool operator != (const MyPoolAllocator<T, Reserv>&, const MyPoolAllocator<U, S>&)
{
    return false;
}
#endif // my_alloc_H