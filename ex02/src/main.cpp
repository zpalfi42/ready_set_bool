#include <iostream>
#include <string>

u_int32_t   gray_code(u_int32_t n)
{
    // CALCULATES XOR FOR ALL THE BITS OF n WITH ALL THE BITS OF n SHIFTED TO THE RIGHT, THIS WAY WE SAVE THE SIGNIFICANT BIT OF n
    // EXAMPLE: n = 5: 0101. n >> 1 = 0010. n XOR n>>1 = 0101 XOR 0010 = 0111 = 7
    u_int32_t res = n ^ (n >> 1);

    return res;
}

int main()
{
    // Test Case 1: Example from description (n=5)
    u_int32_t num1 = 5;
    std::cout << "Gray code of " << num1 << " is: " << gray_code(num1) << std::endl;

    // Test Case 2: Zero
    u_int32_t num2 = 0;
    std::cout << "Gray code of " << num2 << " is: " << gray_code(num2) << std::endl;

    // Test Case 3: One
    u_int32_t num3 = 1;
    std::cout << "Gray code of " << num3 << " is: " << gray_code(num3) << std::endl;

    // Test Case 4: Powers of 2 (e.g., 2, 4, 8)
    u_int32_t num4 = 2; // Binary 10 -> Gray 11 (3)
    std::cout << "Gray code of " << num4 << " is: " << gray_code(num4) << std::endl;

    u_int32_t num5 = 4; // Binary 100 -> Gray 110 (6)
    std::cout << "Gray code of " << num5 << " is: " << gray_code(num5) << std::endl;
    
    u_int32_t num6 = 8; // Binary 1000 -> Gray 1100 (12)
    std::cout << "Gray code of " << num6 << " is: " << gray_code(num6) << std::endl;

    // Test Case 5: Sequential numbers to see the pattern
    u_int32_t num7 = 0;
    std::cout << "Gray code of " << num7 << " is: " << gray_code(num7) << std::endl;
    u_int32_t num8 = 1;
    std::cout << "Gray code of " << num8 << " is: " << gray_code(num8) << std::endl;
    u_int32_t num9 = 2;
    std::cout << "Gray code of " << num9 << " is: " << gray_code(num9) << std::endl;
    u_int32_t num10 = 3; // Binary 11 -> Gray 10 (2)
    std::cout << "Gray code of " << num10 << " is: " << gray_code(num10) << std::endl;
    u_int32_t num11 = 4;
    std::cout << "Gray code of " << num11 << " is: " << gray_code(num11) << std::endl;
    u_int32_t num12 = 5;
    std::cout << "Gray code of " << num12 << " is: " << gray_code(num12) << std::endl;
    u_int32_t num13 = 6; // Binary 110 -> Gray 101 (5)
    std::cout << "Gray code of " << num13 << " is: " << gray_code(num13) << std::endl;
    u_int32_t num14 = 7; // Binary 111 -> Gray 100 (4)
    std::cout << "Gray code of " << num14 << " is: " << gray_code(num14) << std::endl;

    // Test Case 6: A larger number
    u_int32_t num15 = 255; // Binary 11111111 -> Gray 10000000 (128)
    std::cout << "Gray code of " << num15 << " is: " << gray_code(num15) << std::endl;

    // Test Case 7: Maximum u_int32_t value (or close to it)
    u_int32_t num16 = __UINT32_MAX__;
    std::cout << "Gray code of UINT32_MAX (" << num16 << ") is: " << gray_code(num16) << std::endl;

    return 0;
}