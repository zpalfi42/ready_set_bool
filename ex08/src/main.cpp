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
    std::vector<int32_t>                A;
    A.push_back(0);
    A.push_back(2);
    A.push_back(1);
    A.push_back(4);
    A.push_back(3);
    std::vector<std::vector<int32_t>>   B = powerset(A);

    for (size_t i = 0; i < B.size(); i++)
    {
        std::cout << "[";
        for (size_t j = 0; j < B[i].size(); j++)
        {
            std::cout << B[i][j];
            if (j != B[i].size() - 1)
                std::cout << ",";
        }
        std::cout << "],";
    }
    std::cout << std::endl << "Superset count: " << B.size() << " = 2^" << A.size() << std::endl;
}