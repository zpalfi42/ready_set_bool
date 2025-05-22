#include <iostream>
#include <string>
#include <stack>

bool    eval_formula(std::string formula)
{
    std::stack<bool>    stack;

    for (size_t i = 0; i < formula.size(); i++)
    {
        if (isdigit(formula[i]))
        {
            if (formula[i] != '0' && formula[i] != '1')
            {
                std::cerr << "Error with the formula" << std::endl;
                return false;                
            }
            stack.push(formula[i]-'0');
        }
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

void run_test(const std::string& formula, bool expected_result)
{
    bool actual_result = eval_formula(formula);
    std::cout << "Formula: " << formula << " | Expected: " << (expected_result ? "true" : "false")
              << " | Actual: " << (actual_result ? "true" : "false") << " | ";
    if (actual_result == expected_result)
        std::cout << "PASS" << std::endl;
    else
        std::cout << "FAIL" << std::endl;
}

int main()
{
    run_test("00!&", false);
    run_test("10|", true);
    run_test("11&", true);
    run_test("10^", true);
    run_test("01>", true);
    run_test("11=", true);
    run_test("00=", true);
    run_test("1!", false);
    run_test("0!", true);
    run_test("10!|", true);
    run_test("11!&", false);
    run_test("00!^", true);
    run_test("10!>", true);
    run_test("01!&", false);
    run_test("111&&", true);
    run_test("000||", false);
    run_test("101^&", true);

    std::cout << "\nTesting invalid formulas (expecting errors and 'false' return from eval_formula):\n";
    run_test("1", false);
    run_test("&", false);
    run_test("1!&", false);
    run_test("12&", false);
    run_test("10!", false);

    return 0;
}