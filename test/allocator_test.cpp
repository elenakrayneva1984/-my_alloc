#include <gtest/gtest.h>

#include <map>
#include "../my_alloc.h"
#include "../my_list.h"

TEST(MyAllocTest, MyAllocTest)
{
    using Map = std::map<int, long long, std::less<int>, MyPoolAllocator<long long>>;

    Map map;

    for (int i = 0; i < 1000; ++i)
    {
        map[i] = i;
    }

    for (int i = 0; i < 1000; ++i)
    {
        EXPECT_EQ(map[i], i);
    }
}

TEST(MyListTest, MyListTest)
{
    using List = MyList<int, MyPoolAllocator<int>>;

    List list;

    for (int i = 0; i < 1000; ++i)
    {
        list.insert(i);
    }

    List::Iterator it(&list);
    int i = 0;
    while (!it.IsEnd())
    {
        EXPECT_EQ(it->data, i);
        ++i;
        ++it;
    }
}