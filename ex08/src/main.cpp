#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>

std::vector<std::vector<int32_t>>   powerset(std::vector<int32_t>   A)
{
    std::vector<std::vector<int32_t>>   B;

    unsigned int    num_combinations = 1 << A.size();

    for (size_t i = 0; i < num_combinations; i++)
    {
        std::vector<int32_t> current;
        for (size_t j = 0; j < A.size(); j++)
            if (i & (1 << j))
                current.push_back(A[j]);
        B.push_back(current);
        current.clear();
    }
    return B;
}

int main()
{
    std::vector<int32_t> test_set_1 = {0, 2, 1, 4, 3};
    std::vector<std::vector<int32_t>> result_1 = powerset(test_set_1);

    std::cout << "Powerset of {0, 2, 1, 4, 3}:" << std::endl;
    for (size_t i = 0; i < result_1.size(); i++)
    {
        std::cout << "[";
        for (size_t j = 0; j < result_1[i].size(); j++)
        {
            std::cout << result_1[i][j];
            if (j != result_1[i].size() - 1)
                std::cout << ",";
        }
        std::cout << "],";
    }
    std::cout << std::endl << "Superset count: " << result_1.size() << " = 2^" << test_set_1.size() << std::endl << std::endl;

    std::vector<int32_t> test_set_2 = {};
    std::vector<std::vector<int32_t>> result_2 = powerset(test_set_2);
    
    std::cout << "Powerset of {}:" << std::endl;
    for (size_t i = 0; i < result_2.size(); i++)
    {
        std::cout << "[";
        for (size_t j = 0; j < result_2[i].size(); j++)
        {
            std::cout << result_2[i][j];
            if (j != result_2[i].size() - 1)
                std::cout << ",";
        }
        std::cout << "],";
    }
    std::cout << std::endl << "Superset count: " << result_2.size() << " = 2^" << test_set_2.size() << std::endl << std::endl;

    std::vector<int32_t> test_set_3 = {10};
    std::vector<std::vector<int32_t>> result_3 = powerset(test_set_3);
    
    std::cout << "Powerset of {10}:" << std::endl;
    for (size_t i = 0; i < result_3.size(); i++)
    {
        std::cout << "[";
        for (size_t j = 0; j < result_3[i].size(); j++)
        {
            std::cout << result_3[i][j];
            if (j != result_3[i].size() - 1)
                std::cout << ",";
        }
        std::cout << "],";
    }
    std::cout << std::endl << "Superset count: " << result_3.size() << " = 2^" << test_set_3.size() << std::endl << std::endl;

    std::vector<int32_t> test_set_4 = {1, 2, 3};
    std::vector<std::vector<int32_t>> result_4 = powerset(test_set_4);
    
    std::cout << "Powerset of {1, 2, 3}:" << std::endl;
    for (size_t i = 0; i < result_4.size(); i++)
    {
        std::cout << "[";
        for (size_t j = 0; j < result_4[i].size(); j++)
        {
            std::cout << result_4[i][j];
            if (j != result_4[i].size() - 1)
                std::cout << ",";
        }
        std::cout << "],";
    }
    std::cout << std::endl << "Superset count: " << result_4.size() << " = 2^" << test_set_4.size() << std::endl << std::endl;

    return 0;
}