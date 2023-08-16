#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

// #include "playground/wierdo-table/WeirdoTable.h"
#include "algorithms/Sorting.h"
#include "utility/Timer.h"

std::vector<int> ocd::merge(std::vector<int> vec)
{
    const size_t vec_size{vec.size()};

    if (vec_size == 1)
        return vec;

    const size_t boundry{vec_size / 2};

    std::vector<int> left;
    left.reserve(boundry);
    for (int i = 0; i < boundry; ++i)
        left.emplace_back(vec[i]);

    std::vector<int> right;
    right.reserve(vec_size - boundry);
    for (int i = boundry; i < vec_size; ++i)
        right.emplace_back(vec[i]);

    left = merge(left);
    right = merge(right);

    std::vector<int> sorted;
    sorted.reserve(left.size() + right.size());

    int left_index = 0;
    int right_index = 0;

    while (sorted.size() != left.size() + right.size())
    {
        int left_value = left[left_index];
        int right_value = right[right_index];

        // std::cout << left_value << ' ' << right_value << std::endl;

        if (left_index == left.size())
        {
            sorted.emplace_back(right_value);
            ++right_index;

            continue;
        }

        if (right_index == right.size())
        {
            sorted.emplace_back(left_value);
            ++left_index;

            continue;
        }

        if (left_value < right_value)
        {
            sorted.emplace_back(left_value);
            ++left_index;

            continue;
        }

        sorted.emplace_back(right_value);
        ++right_index;
    }

    return sorted;
}

int min(int i, int j)
{
    return i <= j ? i : j;
}

void ocd::insertion(std::vector<int> &vec)
{
    for (int curr_index = 1; curr_index < vec.size(); ++curr_index)
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
    std::vector<int> vec{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // std::vector<int> vec{8, 2, 5, 1, 9, 10, 4, 3, 6, 7};
    {
        util::Timer timer;
        auto sorted = ocd::merge(vec);

        for (auto i : sorted)
        {
            std::cout << i << '\n';
        }
    }

    // {
    //     util::Timer timer;
    //     ocd::insertion(vec);
    // }

    return 0;
}