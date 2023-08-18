#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <stack>
#include <utility>

// #include "playground/wierdo-table/WeirdoTable.h"
#include "algorithms/Sorting.h"
#include "utility/Timer.h"

void backBin(std::array<bool, 3> arr, bool exhasted)
{
    if (exhasted)
        return;

    for (auto ri = arr.crbegin(); ri != arr.crend(); ++ri)
        std::cout << *ri;

    bool flag{true};
    for (bool &i : arr)
    {
        if (i == 0)
        {
            flag = false;
            i = 1;
            break;
        }

        i = 0;
    }

    std::cout << '\n';

    backBin(arr, flag);
}

void backBin(std::array<int, 5> &arr, int n, int k)
{
    if (n < 1)
    {
        for (auto ri = arr.crbegin(); ri != arr.crend(); ++ri)
            std::cout << *ri;

        std::cout << '\n';

        return;
    }

    for (int i = 0; i < k; ++i)
    {
        arr[n - 1] = i;

        backBin(arr, n - 1, k);
    }
}

int main()
{
    std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // std::vector<int> vec{8, 2, 5, 1, 9, 10, 4, 3, 6, 7};
    {
        util::Timer timer;
        ocd::merge(vec);
    }
    for (int i : vec)
    {
        std::cout << i << std::endl;
    }

    return 0;
}