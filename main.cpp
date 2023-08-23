#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <stack>
#include <utility>
#include <cassert>

// #include "playground/wierdo-table/WeirdoTable.h"
#include "algorithms/Sorting.h"
#include "datastructures/linear/LinkedList.h"
#include "utility/Timer.h"

int count = 0;

void backBin(std::array<int, 3> &arr, int n)
{
    if (n < 1)
    {
        if ((arr[0] == arr[1]) || (arr[0] == arr[2]) || (arr[1] == arr[2]))
        {
            ++count;

            for (auto ri = arr.crbegin(); ri != arr.crend(); ++ri)
                std::cout << *ri;

            std::cout << '\n';
        }

        return;
    }

    for (int i = 1; i <= 9; i++)
    {
        arr[n - 1] = i;

        backBin(arr, n - 1);
    }
}

int bound(std::vector<int> vec)
{
    size_t lis{0};

    for (size_t left_bound{0}; left_bound < vec.size(); ++left_bound)
    {
        size_t temp_lis{0};

        size_t right_bound{vec.size() - 1};
        while (vec[left_bound] > vec[right_bound])
            --right_bound;
    }

    return lis;
}

struct Whatever
{
    int *n = nullptr;
};

int main()
{
    // std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // std::vector<int> vec{8, 2, 10, 1, 9, 5, 4, 3, 6, 7};
    // std::vector<int> vec{5, 2, 8, 6, 3, 6, 9, 5};

    cantor::LinkedList<int> list;
    cantor::LinkedList<int> list1{1, 2, 3, 4, 5};
    // cantor::LinkedList<int>::iterator iter;

    // assert(list.insert(3, 2) == cantor::Error::None);

    // for (int i = 0; i < 5; ++i)
    // {

    //     for (int i = 1; i < 1000000; ++i)
    //         list.push_back(i);
    //     {
    //         util::Timer timer;
    //         list.clear();
    //     }
    // }
    for (int i = 1; i < 5; ++i)
        list.push_back(i);

    for (auto &&i : list1)
        std::cout << i << '\n';

    // {
    //     util::Timer timer;
    //     list.find(0);
    // }

    // std::cout << list.size() << '\n';

    // list.remove_back();

    return 0;
}