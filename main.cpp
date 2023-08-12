#include <iostream>
#include <string>
#include <vector>
#include <utility>

// #include "playground/wierdo-table/WeirdoTable.h"
#include "algorithms/Sorting.h"

void ocd::selection(std::vector<int> &vec)
{
    for (int i = 0; i < vec.size(); ++i)
        std::swap(vec[i], vec[ocd::min_index(vec, i)]);
}

int ocd::min_index(const std::vector<int> &vec, int start)
{
    int min = vec[start];
    int index = start;

    for (int i = start + 1; i < vec.size(); ++i)
        if (vec[i] < min)
        {
            min = vec[i];
            index = i;
        }

    return index;
}

int main()
{
    std::vector<int> vec{5, 2, 4, 10, 7, 1, 6};

    ocd::selection(vec);

    for (auto i : vec)
    {
        std::cout << i << '\n';
    }

    // for (int i = 0; i < vec.size(); ++i)
    //     std::cout << ocd::min(vec, i) << '\n';

    return 0;
}