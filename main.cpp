#include <map>
#include "my_alloc.h"
#include "my_list.h"

static long long fact(int n)
{
    long long factorial = 1;
    for (int i = 1; i <= n; ++i)
        factorial *= i;

    return factorial;
}

int main()
{
    std::map<int, long long> map_standart;

    for (int i = 0; i < 10; ++i)
        map_standart[i] = fact(i);

    for (auto pair : map_standart)
        std::cout << pair.first << " " << pair.second << std::endl;


    std::map<int, long long, std::less<int>, MyPoolAllocator<long long>> my_map;
    for (int i = 0; i < 10; ++i)
        my_map[i] = fact(i);

    for (auto pair : my_map)
        std::cout << pair.first << " " << pair.second << std::endl;

    MyList<int> my_list;

    for (int i = 0; i < 10; ++i)
        my_list.insert(i);

    my_list.print();

	MyList<int, MyPoolAllocator<int>> my_list_and_alloc;
    for (int i = 0; i < 10; ++i)
        my_list_and_alloc.insert(i);

    my_list_and_alloc.print();
    return 0;
}
