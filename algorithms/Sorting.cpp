#include <vector>
#include "Sorting.h"

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

void ocd::selection(std::vector<int> &vec)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        int min_index = i;

        for (int j = i + 1; j < vec.size(); ++j)
            if (vec[j] < vec[min_index])
                min_index = j;

        std::swap(vec[i], vec[min_index]);
    }
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
