#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

std::vector<int32_t>    negation(std::vector<int32_t>   a, std::vector<int32_t> universal)
{
    std::vector<int32_t>    res;
    std::set<int32_t>       temp(a.begin(), a.end());
    for (size_t i = 0; i < universal.size(); i++)
    {
        if (temp.find(universal[i]) == temp.end())
            res.push_back(universal[i]);
    }
    return res;
}

std::vector<int32_t>    conjunction(std::vector<int32_t> a, std::vector<int32_t> b)
{
    std::vector<int32_t>    res;
    std::vector<int32_t>::iterator  begin = (a.size() > b.size()) ? a.begin() : b.begin();
    std::vector<int32_t>::iterator  end = (a.size() > b.size()) ? a.end() : b.end();
    std::set<int32_t>   s(begin, end);
    std::vector<int32_t>    v = (a.size() <= b.size()) ? a : b;

    for (size_t i = 0; i < v.size(); i++)
    {
        if (s.find(v[i]) != s.end())
            res.push_back(v[i]);
    }
    return  res;   
}

std::vector<int32_t>    disjunction(std::vector<int32_t> a, std::vector<int32_t> b)
{
    std::vector<int32_t>::iterator  begin = (a.size() > b.size()) ? a.begin() : b.begin();
    std::vector<int32_t>::iterator  end = (a.size() > b.size()) ? a.end() : b.end();
    std::vector<int32_t>    res(begin, end);
    std::set<int32_t>       s(begin, end);
    std::vector<int32_t>    v = (a.size() <= b.size()) ? a : b;

    for (size_t i = 0; i < v.size(); i++)
    {
        if (s.find(v[i]) == s.end())
            res.push_back(v[i]);
    }
    return  res;    
}

std::vector<int32_t>    ex_disjunction(std::vector<int32_t> a, std::vector<int32_t> b)
{
    std::vector<int32_t>::iterator  begin = (a.size() > b.size()) ? a.begin() : b.begin();
    std::vector<int32_t>::iterator  end = (a.size() > b.size()) ? a.end() : b.end();
    std::set<int32_t>       s(begin, end);
    std::vector<int32_t>    v = (a.size() <= b.size()) ? a : b;

    std::vector<int32_t>    res;

    for (size_t i = 0; i < v.size(); i++)
    {
        if (s.find(v[i]) == s.end())
            res.push_back(v[i]);
    }

    begin = (a.size() > b.size()) ? b.begin() : a.begin();
    end = (a.size() > b.size()) ? b.end() : a.end();
    std::set<int32_t>       s2(begin, end);
    std::vector<int32_t>    v2 = (a.size() <= b.size()) ? b : a;

    for (size_t i = 0; i < v2.size(); i++)
    {
        if (s2.find(v2[i]) == s2.end())
            res.push_back(v2[i]);
    }

    return res;
}


std::vector<int32_t>    eval_set(std::string formula, std::vector<std::vector<int32_t>> sets)
{
    std::map<char, std::vector<int32_t>>    vars;
    size_t                                  count = 0;
    std::set<int32_t>                       temp;

    //  BUILD VARS MAP BY ASIGNING SETS FROM THE VETOR BY ORDER APEREANCE IN THE FORMULA
    for (size_t i = 0; i < formula.size(); i++)
    {
        if (formula[i] >= 'A' && formula[i] <= 'Z' && vars.find(formula[i]) == vars.end())
        {
            if (count >= sets.size())
            {
                std::cerr << "Error with the formula" << std::endl;
                return {};
            }
            vars[formula[i]] = sets[count];
            for (size_t j = 0; j < sets[count].size(); j++)
                temp.insert(sets[count][j]);
            count++;
        }
    }
    for (; count < sets.size(); count++)
        for (size_t j = 0; j < sets[count].size(); j++)
                temp.insert(sets[count][j]);
    
    std::stack<std::vector<int32_t>>    stack;
    std::vector<int32_t>                universal(temp.begin(), temp.end());
    for (size_t i = 0; i < formula.size(); i++)
    {
        if (formula[i] >= 'A' && formula[i] <= 'Z')
        {
            stack.push(vars[formula[i]]);
            continue ;
        }
        else if (formula[i] == '!' && stack.size() > 0)
        {
            std::vector<int32_t>    a = stack.top(); stack.pop();
            stack.push(negation(a, universal));
            continue ;
        }
        else if (stack.size() < 2)
        {
            std::cerr << "Error with the formula" << std::endl;
            return {};
        }
        std::vector<int32_t>    b = stack.top(); stack.pop();
        std::vector<int32_t>    a = stack.top(); stack.pop();
        switch (formula[i])
        {
        case '&': stack.push(conjunction(a, b)); break;
        case '|': stack.push(disjunction(a, b)); break;
        case '^': stack.push(ex_disjunction(a, b)); break;
        case '>': stack.push(disjunction(negation(a, universal), b)); break;
        case '=': stack.push(disjunction(conjunction(a, b),conjunction(negation(a, universal), negation(b, universal)))); break;
        default:
            {
                std::cerr << "Error with the formula" << std::endl;
                return {};
            }
        }
    }
    
    if (stack.size() != 1)
    {
        std::cerr << "Error with the formula" << std::endl;
        return {};
    }
    return stack.top();
}

void print_vector(const std::string& label, const std::vector<int32_t>& vec) {
    std::cout << label << " (Size: " << vec.size() << "): { ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    std::cout << " }" << std::endl;
}

std::vector<int32_t> sort_vector(std::vector<int32_t> vec) {
    std::sort(vec.begin(), vec.end());
    return vec;
}

int main() {
    std::cout << "Starting Set Evaluation Test Cases!" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    std::vector<std::vector<int32_t>> sets_for_eval;
    std::vector<int32_t> setA = {1, 2, 3, 4, 5};
    std::vector<int32_t> setB = {4, 5, 6, 7, 8};
    std::vector<int32_t> setC = {1, 3, 5, 7, 9};
    std::vector<int32_t> setD = {2, 4, 6, 8, 10};
    std::vector<int32_t> setE = {};

    sets_for_eval.push_back(setA);
    sets_for_eval.push_back(setB);
    sets_for_eval.push_back(setC);
    sets_for_eval.push_back(setD);
    sets_for_eval.push_back(setE);

    std::cout << "--- Initial Sets ---" << std::endl;
    print_vector("Set A", setA);
    print_vector("Set B", setB);
    print_vector("Set C", setC);
    print_vector("Set D", setD);
    print_vector("Set E (Empty)", setE);
    std::cout << "--------------------" << std::endl;
    
    std::cout << "\n--- Test Case 5: Negation (!A) ---" << std::endl;
    std::vector<int32_t> result5 = eval_set("A!", sets_for_eval);
    std::cout << "Expected Output for \"A!\": {6, 7, 8, 9, 10}" << std::endl;
    print_vector("Your Function's Result (A!)", sort_vector(result5));
    
    std::cout << "\n--- Test Case 2: Conjunction (A&B) ---" << std::endl;
    std::vector<int32_t> result2 = eval_set("AB&", sets_for_eval);
    std::cout << "Expected Output for \"AB&\": {4, 5}" << std::endl;
    print_vector("Your Function's Result (AB&)", sort_vector(result2));
    
    std::cout << "\n--- Test Case 3: Disjunction (A|B) ---" << std::endl;
    std::vector<int32_t> result3 = eval_set("AB|", sets_for_eval);
    std::cout << "Expected Output for \"AB|\": {1, 2, 3, 4, 5, 6, 7, 8}" << std::endl;
    print_vector("Your Function's Result (AB|)", sort_vector(result3));
    
    std::cout << "\n--- Test Case 4: Exclusive Disjunction (A^B) ---" << std::endl;
    std::vector<int32_t> result4 = eval_set("AB^", sets_for_eval);
    std::cout << "Expected Output for \"AB^\": {1, 2, 3, 6, 7, 8}" << std::endl;
    print_vector("Your Function's Result (AB^)", sort_vector(result4));
    
    std::cout << "\n--- Test Case 6: Material Condition (A>B) ---" << std::endl;
    std::vector<int32_t> result6 = eval_set("AB>", sets_for_eval);
    std::cout << "Expected Output for \"AB>\": {4, 5, 6, 7, 8, 9, 10}" << std::endl;
    print_vector("Your Function's Result (AB>)", sort_vector(result6));

    std::cout << "\n--- Test Case 1: Simple Equivalence (AB=) ---" << std::endl;
    std::vector<int32_t> result1 = eval_set("AB=", sets_for_eval);
    std::cout << "Expected Output for \"AB=\": {4, 5, 9, 10}" << std::endl;
    print_vector("Your Function's Result (AB=)", sort_vector(result1));
    
    sets_for_eval.clear();
    sets_for_eval.push_back(setA);
    sets_for_eval.push_back(setE);
    sets_for_eval.push_back(setB);
    sets_for_eval.push_back(setC);
    sets_for_eval.push_back(setD);

    std::cout << "\n--- Test Case 7: Using an Empty Set (AE|) ---" << std::endl;
    std::vector<int32_t> result8 = eval_set("AE|", sets_for_eval);
    std::cout << "Expected Output for \"AE|\": {1, 2, 3, 4, 5}" << std::endl;
    print_vector("Your Function's Result (AE|)", sort_vector(result8));

    sets_for_eval.clear();
    sets_for_eval.push_back(setE);
    sets_for_eval.push_back(setA);
    sets_for_eval.push_back(setB);
    sets_for_eval.push_back(setC);
    sets_for_eval.push_back(setD);

    std::cout << "\n--- Test Case 8: Using an Empty Set and Negation (E!) ---" << std::endl;
    std::vector<int32_t> result9 = eval_set("E!", sets_for_eval);
    std::cout << "Expected Output for \"E!\": {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}" << std::endl;
    print_vector("Your Function's Result (E!)", sort_vector(result9));

    sets_for_eval.clear();
    sets_for_eval.push_back(setA);
    sets_for_eval.push_back(setE);
    sets_for_eval.push_back(setB);
    sets_for_eval.push_back(setC);
    sets_for_eval.push_back(setD);

    std::cout << "\n--- Test Case 9: Invalid Formula (A&, insufficient operands) ---" << std::endl;
    std::vector<int32_t> result10 = eval_set("A&", sets_for_eval);
    print_vector("Your Function's Result (A&)", result10);

    sets_for_eval.clear();
    sets_for_eval.push_back(setA);
    sets_for_eval.push_back(setB);
    sets_for_eval.push_back(setC);
    sets_for_eval.push_back(setD);
    sets_for_eval.push_back(setE);

    std::cout << "\n--- Test Case 10: Mismatched Set Count (ABC&, but only A,B provided) ---" << std::endl;
    std::vector<std::vector<int32_t>> smaller_sets = {setA, setB};
    std::vector<int32_t> result11 = eval_set("ABC&", smaller_sets);
    print_vector("Your Function's Result (ABC& with less sets)", result11);

    return 0;
}