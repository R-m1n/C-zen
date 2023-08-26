#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <limits>

#include "algorithms/Sorting.h"
#include "datastructures/linear/LinkedList.h"
#include "datastructures/linear/Stack.h"
#include "datastructures/linear/Array.h"
#include "utility/Timer.h"

int count = 0;

template <size_t S>
void backBin(std::array<int, S> &arr, int n)
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

int increment(int n)
{
    return n + 1;
}

int main()
{
    // std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // std::vector<int> vec{8, 2, 10, 1, 9, 5, 4, 3, 6, 7};

    // std::vector<int> vec;
    cantor::ArrayList<int> vec;

    for (int i = 0; i <= 15; ++i)
    {
        vec.push_back(i);
        std::cout << vec.back() << ' ';
        std::cout << vec.capacity() << std::endl;
    }
    std::cout << vec.back() << ' ';
    std::cout << vec.capacity() << std::endl;

    std::cout << '\n';

    cantor::ArrayList<int> vec1 = std::move(vec);
    for (auto &&i : vec1)
        std::cout << i << '\n';

    // std::cout << '\n';

    // for (int i = 10; i <= 25; ++i)
    // {
    //     vec.push_back(i);
    //     std::cout << vec.back() << ' ';
    //     std::cout << vec.capacity() << std::endl;
    // }
    // std::cout << vec.back() << ' ';
    // std::cout << vec.capacity() << std::endl;

    // for (int i = 0; i <= 15; ++i)
    //     std::cout << vec.back() << '\n';

    // std::cout << vec.max_size() << std::endl;
    // std::cout << vec.capacity() << std::endl;
    // std::cout << vec.size() << std::endl;

    // for (auto &&i : vec)
    // {
    //     std::cout << i << '\n';
    // }
    // std::cout << '\n';

    // for (auto &&i : vec)
    // {
    //     std::cout << i << '\n';
    // }

    // while (s.size())
    // {
    //     auto [value, err] = s.pop();c

    //     std::cout << value.value_or(0) << '\n';
    // }

    return 0;
}
