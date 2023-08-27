#include <unordered_set>
#include <unordered_map>

#include "StackEvens.h"
#include "datastructures/linear/Stack.h"

bool cantor::check_symbol_balance(const std::string &input)
{
    cantor::StackList<char> stack;

    for (char c : input)
    {
        bool is_open_delimiter = c == '(' || c == '{' || c == '[' || c == '<';

        bool is_close_delimiter = c == ')' || c == '}' || c == ']' || c == '>';

        if (is_open_delimiter)
            stack.push(c);

        else if (is_close_delimiter)
        {
            if (stack.is_empty())
                return false;

            bool match = stack.top() + 1 == c || stack.top() + 2 == c;

            if (match)
            {
                stack.pop();

                continue;
            }

            return false;
        }
    }

    return stack.is_empty();
}