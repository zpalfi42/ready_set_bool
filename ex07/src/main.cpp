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

bool    print_truth_table(std::string formula)
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

    for (size_t i = 0; i < combinations_vector.size(); i++)
    {
        std::map<char, bool>    current = combinations_vector[i];
        std::string             curr_formula;

        for (size_t i = 0; i < formula.size(); i++)
        {
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
        
        if (eval_formula(curr_formula))
            return true;
    }
    return false;
}

bool    sat(std::string formula)
{
    return print_truth_table(formula);
}

int main()
{
    std::cout << "Testing sat function:" << std::endl;

    std::cout << "Formula: AB| -> Satisfiable: " << (sat("AB|") ? "true" : "false") << std::endl;
    std::cout << "Formula: AB& -> Satisfiable: " << (sat("AB&") ? "true" : "false") << std::endl;
    std::cout << "Formula: AA!& -> Satisfiable: " << (sat("AA!&") ? "true" : "false") << std::endl;
    std::cout << "Formula: AA^ -> Satisfiable: " << (sat("AA^") ? "true" : "false") << std::endl;
    std::cout << "Formula: A -> Satisfiable: " << (sat("A") ? "true" : "false") << std::endl;
    std::cout << "Formula: A! -> Satisfiable: " << (sat("A!") ? "true" : "false") << std::endl;
    std::cout << "Formula: PQR&& -> Satisfiable: " << (sat("PQR&&") ? "true" : "false") << std::endl;
    std::cout << "Formula: PQR&| -> Satisfiable: " << (sat("PQR&|") ? "true" : "false") << std::endl;
    std::cout << "Formula: AB= -> Satisfiable: " << (sat("AB=") ? "true" : "false") << std::endl;
    std::cout << "Formula: AB> -> Satisfiable: " << (sat("AB>") ? "true" : "false") << std::endl;
    std::cout << "Formula: AA>! -> Satisfiable: " << (sat("AA>!") ? "true" : "false") << std::endl;

    return 0;
}