#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>

std::vector<int32_t>    eval_set(std::string formula, std::vector<std::vector<int32_t>> sets)
{
    
}

int main()
{
    std::vector<std::vector<int32_t>>   sets;
    std::vector<int32_t>    A, B;
    A.push_back(2);
    B.push_back(3);
    A.push_back(4);
    B.push_back(5);
    A.push_back(6);
    B.push_back(7);
    A.push_back(8);
    B.push_back(9);
    std::vector<int32_t>    result = eval_set("AB&", sets);
}