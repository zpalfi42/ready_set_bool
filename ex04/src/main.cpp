#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>

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

void    print_truth_table(std::string formula)
{
    std::vector<char>                       vars;
    std::vector<std::map<char, bool>>  combinations_vector;

    for (size_t i = 0; i < formula.size(); i++)
        if (formula[i] >= 'A' && formula[i] <= 'Z')
            vars.push_back(formula[i]);

    unsigned int    num_combinations = 1 << vars.size();

    for (size_t i = 0; i < num_combinations; i++)
    {
        std::map<char, bool>    current;
        for (size_t j = 0; j < vars.size(); j++)
        {
            char    var = vars[j];

            bool    value = (i >> j) & 1;
            current[var] = value;
        }
        combinations_vector.push_back(current);
        current.clear();
    }

    for (size_t i = 0; i < vars.size(); i++)
        std::cout << "\t" << vars[i] << "\t|";
    std::cout << "\t=\t|" << std::endl;

    for (size_t i = 0; i < combinations_vector.size(); i++)
    {
        std::map<char, bool>    current = combinations_vector[i];
        std::string             curr_formula;
        for (std::map<char, bool>::iterator it = current.begin(); it != current.end(); it++)
        {
            std::cout << "\t" << it->second << "\t|";
        }
        for (size_t i = 0; i < formula.size(); i++)
        {
            // std::cout << std::endl << current[formula[i]];
            if (formula[i] >= 'A' && formula[i] <= 'Z')
            {
                if (current[formula[i]])
                    curr_formula += '1';
                else
                    curr_formula += '0';
            }
            else
                curr_formula += formula[i];
        }
        
        std::cout << "\t" << eval_formula(curr_formula) << "\t|" << std::endl;
    }
}

int main()
{
    print_truth_table("AB&C|");
}