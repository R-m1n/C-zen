#include <iostream>
#include <string>

#include "playground/wierdo-table/WeirdoTable.h"

int main()
{
    WeirdoTable wt;

    wt.insert("armin", 25);
    wt.insert("arian", 19);
    wt.insert("kiana", 23);

    wt["arian"] = 12;

    std::cout << wt["arian"];

    return 0;
}