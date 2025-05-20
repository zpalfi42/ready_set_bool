#include <iostream>
#include <string>
#include <stack>

bool    eval_formula(std::string formula)
{
    std::stack<bool>    stack;

    for (size_t i = 0; i < formula.size(); i++)
    {
        if (isdigit(formula[i]))
            stack.push(formula[i]-'0');
        else
        {
            if (formula[i] == '!' && stack.size() > 0)
            {
                bool a = stack.top(); stack.pop();
                stack.push(!a);
                continue ;
            }
            else if (stack.size() < 2)
            {
                std::cerr << "Error with the formula" << std::endl;
                return false;
            }
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            switch (formula[i])
            {
                case '&': stack.push(a & b); break;
                case '|': stack.push(a | b); break;
                case '^': stack.push(a ^ b); break;
                case '>': stack.push(!a | b); break;
                case '=': stack.push(a == b); break;
                default:
                {
                    std::cerr << "Error with the formula" << std::endl;
                    return false;
                }
            }
        }
    }
    if (stack.size() != 1)
    {
        std::cerr << "Error with the formula" << std::endl;
        return false;
    }
    return stack.top();
}

int main()
{
    std::cout << eval_formula("00!&") << std::endl;
}