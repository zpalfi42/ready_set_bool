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
    std::cout << multiplier(9, 5) << std::endl;
}