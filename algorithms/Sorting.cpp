#include <vector>
#include "Sorting.h"

void ocd::insertion(std::vector<int> &vec)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        int current = vec[i];

        for (int j = i - 1; j >= 0; --j)
        {
            if (current < vec[j])
                vec[j + 1] = vec[j];

            else
                break;

            vec[j] = current;
        }
    }
}