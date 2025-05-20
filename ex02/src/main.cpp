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

u_int32_t   multiplier(u_int32_t a, u_int32_t b)
{
    u_int32_t   res = 0;

    while (b != 0)
    {
        if (b & 1)
            res = adder(res, a);
        a = a << 1;
        b = b >> 1;
    }
    
    return res;
}

u_int32_t   gray_code(u_int32_t n)
{
    // CALCULATES XOR FOR ALL THE BITS OF n WITH ALL THE BITS OF n SHIFTED TO THE RIGHT, THIS WAY WE SAVE THE SIGNIFICANT BIT OF n
    // EXAMPLE: n = 5: 0101. n >> 1 = 0010. n XOR n>>1 = 0101 XOR 0010 = 0111 = 7
    u_int32_t res = n ^ (n >> 1);

    return res;
}

int main()
{
    std::cout << gray_code(5) << std::endl;
}