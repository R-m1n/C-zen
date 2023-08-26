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

    cantor::StackArray<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);

    cantor::StackArray<int> stack1 = std::move(stack);

    // while (!stack.is_empty())
    //     std::cout << stack.pop() << '\n';

    while (!stack1.is_empty())
        std::cout << stack1.pop() << '\n';

    return 0;
}
