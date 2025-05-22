#include <iostream>
#include <string>

// HAS A PROBLEM, ITERATES 32 TIMES ALWAYS, EVEN IF THE NUMBERS ARE 1+1
u_int32_t   adder_v0(u_int32_t a, u_int32_t b)
{
    u_int32_t   result = 0;
    u_int32_t   carry = 0;

    for (int i = 0; i < 32; i++)
    {
        // MOVES THE BITS i POSITIONS TO THE RIGHT AND THEN SELECTS THE LAS ONE
        // EXAMPLE: 4 IN BINARY: 0...0101, IF i=2 THEN (a >> i): 0...0001 AND a_bit: 1
        u_int32_t a_bit = (a >> i) & 1;
        u_int32_t b_bit = (b >> i) & 1;
        
        // SUM IS 1 IF ONE AND ONLY ONE OF THE BITS OR CARRY IS 1, ELSE 0
        u_int32_t sum = ((a_bit ^ b_bit) ^ carry);

        // ADS THE RESULT IN THE RIGHT POSITION BY SHIFTING THE BIT TO THE LEFT i POSITIONS AND THEN USING THE BITWISE OR.
        result |= (sum << i);

        // UPDATES THE VALUE OF THE CARRY. CARRY IS ONE IF a_bit AND b_bit ARE BOTH ONE, OR IF carry AND ONLY OF THE OTHER BITS IS ONE. ELSE 0
        carry = ((a_bit & b_bit) | (carry & (a_bit ^ b_bit)));
    }

    return result;
}

// LESS ITERATIONS, BETTER
u_int32_t   adder(u_int32_t a, u_int32_t b)
{
    u_int32_t carry = 0;

    while (b != 0)
    {
        // CALCULATE CARRY IN ALL THE POSITIONS AND SHIFT THEM TO THE LEFT.
        // FOR EXAMPLE 1 + 3 = 0001 + 0011 -> CARRY = 0001 (BEFORE SHIFT) 0010 (AFTER SHIFT) (ITERATION 1)
        // EXAMPLE 2 + 2 = 0010 + 0010 -> CARRY = 0100 (ITERATION 2)
        // EXAMPLE 0 + 4 = 0000 + 0100 -> CARRY = 0000 (ITERATION 3)
        carry = (a & b) << 1;

        // CALCULATE XOR IN ALL POSITIONS AND SAVE IN A.
        // EXAMPLE 1 + 3 = 0001 + 0011 -> a = 0010 (ITERATION 1)
        // EXAMPLE 2 + 2 = 0010 + 0010 -> a = 0000 (ITERATION 2)
        // EXAMPLE 0 + 4 = 0000 + 0100 -> a = 0100 (ITERATION 3)
		a = a ^ b;

        // SAVES CARRY IN B
		b = carry;
    }

    return a;
}


int main()
{
    // Test Case 1: Simple addition
    u_int32_t num1_1 = 5;
    u_int32_t num2_1 = 3;
    std::cout << num1_1 << " + " << num2_1 << " = " << adder(num1_1, num2_1) << std::endl;

    // Test Case 2: Addition with carry
    u_int32_t num1_2 = 7;
    u_int32_t num2_2 = 8;
    std::cout << num1_2 << " + " << num2_2 << " = " << adder(num1_2, num2_2) << std::endl;

    // Test Case 3: One number is zero
    u_int32_t num1_3 = 10;
    u_int32_t num2_3 = 0;
    std::cout << num1_3 << " + " << num2_3 << " = " << adder(num1_3, num2_3) << std::endl;

    // Test Case 4: Both numbers are zero
    u_int32_t num1_4 = 0;
    u_int32_t num2_4 = 0;
    std::cout << num1_4 << " + " << num2_4 << " = " << adder(num1_4, num2_4) << std::endl;

    // Test Case 5: Large numbers (within u_int32_t limits)
    u_int32_t num1_5 = 2000000000; // 2 billion
    u_int32_t num2_5 = 1500000000; // 1.5 billion
    std::cout << num1_5 << " + " << num2_5 << " = " << adder(num1_5, num2_5) << std::endl;

    // Test Case 6: Edge case - max value
    u_int32_t num1_6 = __UINT32_MAX__ - 1; // max - 1
    u_int32_t num2_6 = 1;
    std::cout << num1_6 << " + " << num2_6 << " = " << adder(num1_6, num2_6) << std::endl;

    // Test Case 7: Another edge case - max value
    u_int32_t num1_7 = __UINT32_MAX__;
    u_int32_t num2_7 = 0;
    std::cout << num1_7 << " + " << num2_7 << " = " << adder(num1_7, num2_7) << std::endl;

    // Test Case 8: Max value with a small number (demonstrates overflow if not handled by u_int32_t arithmetic)
    u_int32_t num1_8 = __UINT32_MAX__;
    u_int32_t num2_8 = 5;
    std::cout << num1_8 << " + " << num2_8 << " = " << adder(num1_8, num2_8) << std::endl;

    return 0;
}