#include <iostream>
#include <string>
#include <vector>

// #include "playground/wierdo-table/WeirdoTable.h"
#include "algorithms/Sorting.h"

int main()
{
    std::vector<int> vec{5, 2, 4, 10, 7, 1, 6};

    ocd::insertion(vec);

    for (auto i : vec)
    {
        std::cout << i << '\n';
    }

    return 0;
}