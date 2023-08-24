#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cassert>

#include "algorithms/Sorting.h"
#include "datastructures/linear/LinkedList.h"
#include "datastructures/linear/Stack.h"
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

int main()
{
    // std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // std::vector<int> vec{8, 2, 10, 1, 9, 5, 4, 3, 6, 7};
    // std::vector<int> vec{5, 2, 8, 6, 3, 6, 9, 5};

    cantor::Stack<int, 5> s;

    s.push(1);
    s.push(5);
    s.push(6);
    s.push(7);
    s.push(2);

    while (s.size())
    {
        auto [value, err] = s.pop();

        std::cout << value.value_or(0) << '\n';
    }
    return 0;
}