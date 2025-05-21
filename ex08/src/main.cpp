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
            if (count > sets.size())
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
    {
        for (size_t j = 0; j < sets[count].size(); j++)
                temp.insert(sets[count][j]);
    }
    
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
    std::cout << "Starting Set Evaluation Test Cases! Quack, quack!" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    // Define some base sets for evaluation
    std::vector<std::vector<int32_t>> sets_for_eval;
    std::vector<int32_t> setA = {1, 2, 3, 4, 5};
    std::vector<int32_t> setB = {4, 5, 6, 7, 8};
    std::vector<int32_t> setC = {1, 3, 5, 7, 9};
    std::vector<int32_t> setD = {2, 4, 6, 8, 10};
    std::vector<int32_t> setE = {}; // An empty set

    sets_for_eval.push_back(setA); // Index 0: A
    sets_for_eval.push_back(setB); // Index 1: B
    sets_for_eval.push_back(setC); // Index 2: C
    sets_for_eval.push_back(setD); // Index 3: D
    sets_for_eval.push_back(setE); // Index 4: E (for testing empty sets)

    // Optional: Print the initial sets for reference
    std::cout << "--- Initial Sets ---" << std::endl;
    print_vector("Set A", setA);
    print_vector("Set B", setB);
    print_vector("Set C", setC);
    print_vector("Set D", setD);
    print_vector("Set E (Empty)", setE);
    std::cout << "--------------------" << std::endl;

    // --- Test Case 1: Simple Equivalence (AB=) --- (Your original test case)
    // A = {1, 2, 3, 4, 5}
    // B = {4, 5, 6, 7, 8}
    // A <=> B: elements that are in both or neither
    // (A & B) | (!A & !B)
    // (4,5) | ({global} - {1,2,3,4,5} & {global} - {4,5,6,7,8})
    // Assuming global = union of all sets: {1,2,3,4,5,6,7,8,9,10}
    // !A = {6,7,8,9,10}, !B = {1,2,3,9,10}
    // !A & !B = {9,10}
    // Expected: {4, 5, 9, 10}
    std::cout << "\n--- Test Case 1: Simple Equivalence (AB=) ---" << std::endl;
    std::vector<int32_t> result1 = eval_set("AB=", sets_for_eval);
    // Note: The expected output for "AB=" from your problem statement {4, 5, 9, 10, 11, 12}
    // seems to imply a different global set or calculation.
    // Based on standard set logic and the provided sets, a more likely expected output is {4, 5, 9, 10}.
    // You should verify the exact calculation for 'equivalence' with your problem's definition.
    std::cout << "Expected Output for \"AB=\": {4, 5, 9, 10} (Verify with problem def.)" << std::endl;
    print_vector("Your Function's Result (AB=)", sort_vector(result1)); // Sort for consistent comparison

    // --- Test Case 2: Conjunction (A&B) ---
    // A = {1, 2, 3, 4, 5}
    // B = {4, 5, 6, 7, 8}
    // A & B: Intersection {4, 5}
    std::cout << "\n--- Test Case 2: Conjunction (A&B) ---" << std::endl;
    std::vector<int32_t> result2 = eval_set("AB&", sets_for_eval);
    std::cout << "Expected Output for \"AB&\": {4, 5}" << std::endl;
    print_vector("Your Function's Result (AB&)", sort_vector(result2));

    // --- Test Case 3: Disjunction (A|B) ---
    // A = {1, 2, 3, 4, 5}
    // B = {4, 5, 6, 7, 8}
    // A | B: Union {1, 2, 3, 4, 5, 6, 7, 8}
    std::cout << "\n--- Test Case 3: Disjunction (A|B) ---" << std::endl;
    std::vector<int32_t> result3 = eval_set("AB|", sets_for_eval);
    std::cout << "Expected Output for \"AB|\": {1, 2, 3, 4, 5, 6, 7, 8}" << std::endl;
    print_vector("Your Function's Result (AB|)", sort_vector(result3));

    // --- Test Case 4: Exclusive Disjunction (A^B) ---
    // A = {1, 2, 3, 4, 5}
    // B = {4, 5, 6, 7, 8}
    // A ^ B: Symmetric Difference {1, 2, 3, 6, 7, 8}
    std::cout << "\n--- Test Case 4: Exclusive Disjunction (A^B) ---" << std::endl;
    std::vector<int32_t> result4 = eval_set("AB^", sets_for_eval);
    std::cout << "Expected Output for \"AB^\": {1, 2, 3, 6, 7, 8}" << std::endl;
    print_vector("Your Function's Result (AB^)", sort_vector(result4));

    // --- Test Case 5: Negation (!A) ---
    // Global set for these tests will be the union of A, B, C, D, E = {1,2,3,4,5,6,7,8,9,10}
    // !A: {6, 7, 8, 9, 10}
    std::cout << "\n--- Test Case 5: Negation (!A) ---" << std::endl;
    std::vector<int32_t> result5 = eval_set("A!", sets_for_eval);
    std::cout << "Expected Output for \"A!\": {6, 7, 8, 9, 10}" << std::endl;
    print_vector("Your Function's Result (A!)", sort_vector(result5));

    // --- Test Case 6: Material Condition (A>B) ---
    // A > B: !A | B (elements not in A, or in B)
    // !A = {6, 7, 8, 9, 10}
    // B = {4, 5, 6, 7, 8}
    // !A | B = {4, 5, 6, 7, 8, 9, 10}
    std::cout << "\n--- Test Case 6: Material Condition (A>B) ---" << std::endl;
    std::vector<int32_t> result6 = eval_set("AB>", sets_for_eval);
    std::cout << "Expected Output for \"AB>\": {4, 5, 6, 7, 8, 9, 10}" << std::endl;
    print_vector("Your Function's Result (AB>)", sort_vector(result6));

    // --- Test Case 8: Using an Empty Set (AE|) ---
    // A = {1, 2, 3, 4, 5}
    // E = {}
    // A | E = {1, 2, 3, 4, 5}
    std::cout << "\n--- Test Case 7: Using an Empty Set (AE|) ---" << std::endl;
    std::vector<int32_t> result8 = eval_set("AE|", sets_for_eval);
    std::cout << "Expected Output for \"AE|\": {1, 2, 3, 4, 5}" << std::endl;
    print_vector("Your Function's Result (AE|)", sort_vector(result8));

    // --- Test Case 9: Using an Empty Set and Negation (!E) ---
    // Global set is {1..10}
    // !E = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    std::cout << "\n--- Test Case 8: Using an Empty Set and Negation (E!) ---" << std::endl;
    std::vector<int32_t> result9 = eval_set("E!", sets_for_eval);
    std::cout << "Expected Output for \"E!\": {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}" << std::endl;
    print_vector("Your Function's Result (E!)", sort_vector(result9));

    // --- Test Case 10: Invalid Formula (Example: Not enough operands for an operator) ---
    // Note: Behavior is undefined, but your function might handle it with an error.
    std::cout << "\n--- Test Case 9: Invalid Formula (A&, insufficient operands) ---" << std::endl;
    // Expected: Undefined behavior, perhaps an error message from your function.
    std::vector<int32_t> result10 = eval_set("A&", sets_for_eval);
    print_vector("Your Function's Result (A&)", result10); // Don't sort, as it might be empty or error

    // --- Test Case 11: Mismatched Set Count (Example: Formula uses 'C' but only A,B provided) ---
    // Note: Behavior is undefined.
    std::cout << "\n--- Test Case 10: Mismatched Set Count (ABC&, but only A,B provided) ---" << std::endl;
    std::vector<std::vector<int32_t>> smaller_sets = {setA, setB};
    // Expected: Undefined behavior, perhaps an error message.
    std::vector<int32_t> result11 = eval_set("ABC&", smaller_sets);
    print_vector("Your Function's Result (ABC& with less sets)", result11);

    std::cout << "\nAll test cases finished! Keep quacking at it!" << std::endl;

    return 0;
}