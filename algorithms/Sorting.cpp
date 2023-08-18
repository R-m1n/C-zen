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

void ocd::merge(std::vector<int> &vec)
{
    const size_t vec_size{vec.size()};

    if (vec_size == 1 || vec_size == 0)
        return;

    const size_t boundry{vec_size / 2};

    std::vector<int> left;
    left.reserve(boundry);
    for (int i = 0; i < boundry; ++i)
        left.emplace_back(vec[i]);

    std::vector<int> right;
    right.reserve(vec_size - boundry);
    for (int i = boundry; i < vec_size; ++i)
        right.emplace_back(vec[i]);

    merge(left);
    merge(right);

    std::vector<int> sorted;
    sorted.reserve(left.size() + right.size());

    std::vector<int>::iterator left_iter{left.begin()}, right_iter{right.begin()};

    while (!(left_iter == left.end() && right_iter == right.end()))
    {

        if (left_iter == left.end())
        {
            sorted.emplace_back(*right_iter);
            ++right_iter;

            continue;
        }

        if (right_iter == right.end())
        {
            sorted.emplace_back(*left_iter);
            ++left_iter;

            continue;
        }

        if (*left_iter < *right_iter)
        {
            sorted.emplace_back(*left_iter);
            ++left_iter;

            continue;
        }

        sorted.emplace_back(*right_iter);
        ++right_iter;
    }

    vec = std::move(sorted);
}