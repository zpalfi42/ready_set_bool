#include <iostream>
#include <string>

u_int32_t   adder(u_int32_t a, u_int32_t b)
{
    u_int32_t carry = 0;

    while (b != 0)
    {
        carry = (a & b) << 1;
		a = a ^ b;
		b = carry;
    }

    return a;
}

// EXAMPLE 9 x 5: 1001 x 0101
// ITERATION 1: a = 1001, b = 0101, res = 0000. THE LAST BIT OF b IS 1 SO res = 0000 + 1001 = 1001.
// ITERATION 3: a = 10010, b = 010, res = 1001. THE LAST BIT OF b IS 0 SO NOTHING HAPPENS, JUST THE SHIFTS.
// ITERATION 3: a = 100100, b = 01, res = 1001. THE LAST BIT OF b IS 1 SO res = 001001 + 100100 = 101101.
// ITERATION 4: b is 0 SO THE FINAL RESULT IS res = 101101 = 45.
u_int32_t   multiplier(u_int32_t a, u_int32_t b)
{
    u_int32_t   res = 0;

    while (b != 0)
    {
        // IF THE LAST BIT OF B IS 1, ADD A TO THE RESULT
        if (b & 1)
            res = adder(res, a);
        
        // SHIFT A TO THE LEFT
        a = a << 1;
        // SHIFT B TO THE RIGHT
        b = b >> 1;
    }
    
    return res;
}

int main()
{
    // Test Case 1: Simple multiplication
    u_int32_t num1_1 = 9;
    u_int32_t num2_1 = 5;
    std::cout << num1_1 << " * " << num2_1 << " = " << multiplier(num1_1, num2_1) << std::endl;

    // Test Case 2: One number is zero
    u_int32_t num1_2 = 7;
    u_int32_t num2_2 = 0;
    std::cout << num1_2 << " * " << num2_2 << " = " << multiplier(num1_2, num2_2) << std::endl;

    // Test Case 3: Other number is zero
    u_int32_t num1_3 = 0;
    u_int32_t num2_3 = 12;
    std::cout << num1_3 << " * " << num2_3 << " = " << multiplier(num1_3, num2_3) << std::endl;

    // Test Case 4: Both numbers are zero
    u_int32_t num1_4 = 0;
    u_int32_t num2_4 = 0;
    std::cout << num1_4 << " * " << num2_4 << " = " << multiplier(num1_4, num2_4) << std::endl;

    // Test Case 5: Multiplication by 1
    u_int32_t num1_5 = 42;
    u_int32_t num2_5 = 1;
    std::cout << num1_5 << " * " << num2_5 << " = " << multiplier(num1_5, num2_5) << std::endl;

    // Test Case 6: Larger numbers
    u_int32_t num1_6 = 100;
    u_int32_t num2_6 = 25;
    std::cout << num1_6 << " * " << num2_6 << " = " << multiplier(num1_6, num2_6) << std::endl;

    // Test Case 7: Another set of larger numbers
    u_int32_t num1_7 = 123;
    u_int32_t num2_7 = 45;
    std::cout << num1_7 << " * " << num2_7 << " = " << multiplier(num1_7, num2_7) << std::endl;

    // Test Case 8: Maximum values (results in overflow if not handled by standard type sizes, but bitwise multiplication handles it)
    // Note: The result might wrap around if it exceeds u_int32_t max.
    u_int32_t num1_8 = 65535; // Example: equivalent to 2^16 - 1
    u_int32_t num2_8 = 65535; // Example: equivalent to 2^16 - 1
    std::cout << num1_8 << " * " << num2_8 << " = " << multiplier(num1_8, num2_8) << std::endl;

    return 0;
}