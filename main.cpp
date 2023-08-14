#include <iostream>
#include <string>
#include <vector>
#include <utility>

// #include "playground/wierdo-table/WeirdoTable.h"
#include "algorithms/Sorting.h"
#include "utility/Timer.h"

void ocd::bubble(std::vector<int> &vec)
{
    if (!vec.size())
        return;

    bool is_sorted{false};

    size_t sorted_items{0};

    while (!is_sorted)
    {
        is_sorted = true;

        for (int i = 0; i < vec.size() - sorted_items - 1; ++i)
            if (vec[i + 1] < vec[i])
            {
                std::swap(vec[i], vec[i + 1]);
                is_sorted = false;
            }

        ++sorted_items;
    }
}

int main()
{
    std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> vec2{8, 2, 5, 1, 9, 10, 4, 3, 6, 7};

    ocd::bubble(vec);

    for (auto i : vec)
    {
        std::cout << i << '\n';
    }

    return 0;
}