#include <vector>
#include "Sorting.h"

void ocd::insertion(std::vector<int> &vec)
{
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