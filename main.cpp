#include <iostream>
#include <string>
#include <vector>
#include <utility>

// #include "playground/wierdo-table/WeirdoTable.h"
#include "algorithms/Sorting.h"
#include "utility/Timer.h"

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

void ocd::insertion(std::vector<int> &vec)
{
    util::Timer time;
    for (int curr_index = 0; curr_index < vec.size(); ++curr_index)
    {
        int current = vec[curr_index];

        int prev_index = curr_index - 1;

        while ((current < vec[prev_index]))
        {
            vec[prev_index + 1] = vec[prev_index];

            --prev_index;
        }

        vec[prev_index + 1] = current;
    }
}

int main()
{
    std::vector<int> vec{1, 2, 4, 10, 7, 5, 6};

    ocd::insertion(vec);

    // for (auto i : vec)
    // {
    //     std::cout << i << '\n';
    // }

    // for (int i = 0; i < vec.size(); ++i)
    //     std::cout << ocd::min(vec, i) << '\n';

    return 0;
}