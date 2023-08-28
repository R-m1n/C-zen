#include <unordered_set>
#include <unordered_map>

#include "StackEvens.h"
#include "datastructures/linear/Stack.h"

enum class Symbol : char
{
    Plus = '+',
    Minus = '-',
    Multiply = '*',
    Divide = '/',
};

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

void postfix_eval(const std::string &input)
{
    cantor::Stack<int, sizeof(std::string)> operands;
    cantor::Stack<int, sizeof(std::string)> results;

    int counter = 0;

    int flag = 0;

    for (char ch : input)
    {
        int result = 0;

        ++flag;

        if ('0' <= ch && ch <= '9')
        {
            results.push(static_cast<int>(ch - '0'));

            ++counter;

            continue;
        }

        if (flag == input.size())
            while (!results.is_empty())
                operands.push(results.pop());

        else
            while (counter)
            {
                operands.push(results.pop());
                --counter;
            }

        result += operands.pop();

        while (!operands.is_empty())
        {
            switch (ch)
            {
            case static_cast<char>(Symbol::Plus):
                result += operands.pop();
                break;

            case static_cast<char>(Symbol::Minus):
                result -= operands.pop();
                break;

            case static_cast<char>(Symbol::Multiply):
                result *= operands.pop();
                break;

            case static_cast<char>(Symbol::Divide):
                result /= operands.pop();
            }
        }

        results.push(result);
    }

    std::cout << results.pop() << '\n';
}