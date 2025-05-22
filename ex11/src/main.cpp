#include <iostream>
#include <iomanip>
#include <cstdint>
#include <utility>
#include <random>
#include <chrono>

double map(u_int16_t x, u_int16_t y)
{
    int i = 0;
    u_int32_t res = 0;
    while (i < 16)
    {
        u_int16_t x_bit = (x >> i) & 1;
        u_int16_t y_bit = (y >> i) & 1;
        u_int16_t temp = (y_bit << 1) | x_bit;
        res = res | (static_cast<u_int32_t>(temp) << i * 2);
        i++;
    }
    return static_cast<double>(res) / static_cast<double>(__UINT32_MAX__);
}

std::pair<u_int16_t, u_int16_t> reverse_map(double n)
{
    u_int32_t a = static_cast<u_int32_t>(n * __UINT32_MAX__);
    u_int16_t x = 0;
    u_int16_t y = 0;
    for (int i = 0; i < 32; i++)
    {
        u_int16_t bit = (a >> i) & 1;
        if (i % 2 == 0)
            x = x | (bit << (i / 2));
        else
            y = y | (bit << ((i-1) / 2));
    }
    return std::pair<u_int16_t, u_int16_t>(x, y);
}

int main()
{
    std::cout << std::fixed << std::setprecision(10);

    // Test Case 1: Arbitrary values
    u_int16_t testX1 = 12345;
    u_int16_t testY1 = 54321;
    double mappedValue1 = map(testX1, testY1);
    std::pair<u_int16_t, u_int16_t> unmappedValues1 = reverse_map(mappedValue1);
    std::cout << "--- Test Case 1 ---" << std::endl;
    std::cout << "Original X: " << testX1 << ", Original Y: " << testY1 << std::endl;
    std::cout << "Mapped Value: " << mappedValue1 << std::endl;
    std::cout << "Unmapped X: " << unmappedValues1.first << ", Unmapped Y: " << unmappedValues1.second << std::endl;
    std::cout << "Match: " << (testX1 == unmappedValues1.first && testY1 == unmappedValues1.second ? "YES" : "NO") << std::endl << std::endl;

    // Test Case 2: Zero values
    u_int16_t testX2 = 0;
    u_int16_t testY2 = 0;
    double mappedValue2 = map(testX2, testY2);
    std::pair<u_int16_t, u_int16_t> unmappedValues2 = reverse_map(mappedValue2);
    std::cout << "--- Test Case 2 (Zeros) ---" << std::endl;
    std::cout << "Original X: " << testX2 << ", Original Y: " << testY2 << std::endl;
    std::cout << "Mapped Value: " << mappedValue2 << std::endl;
    std::cout << "Unmapped X: " << unmappedValues2.first << ", Unmapped Y: " << unmappedValues2.second << std::endl;
    std::cout << "Match: " << (testX2 == unmappedValues2.first && testY2 == unmappedValues2.second ? "YES" : "NO") << std::endl << std::endl;

    // Test Case 3: Maximum values for u_int16_t
    u_int16_t testX3 = __UINT16_MAX__;
    u_int16_t testY3 = __UINT16_MAX__;
    double mappedValue3 = map(testX3, testY3);
    std::pair<u_int16_t, u_int16_t> unmappedValues3 = reverse_map(mappedValue3);
    std::cout << "--- Test Case 3 (Max Values) ---" << std::endl;
    std::cout << "Original X: " << testX3 << ", Original Y: " << testY3 << std::endl;
    std::cout << "Mapped Value: " << mappedValue3 << std::endl;
    std::cout << "Unmapped X: " << unmappedValues3.first << ", Unmapped Y: " << unmappedValues3.second << std::endl;
    std::cout << "Match: " << (testX3 == unmappedValues3.first && testY3 == unmappedValues3.second ? "YES" : "NO") << std::endl << std::endl;

    // Test Case 4: One max, one zero
    u_int16_t testX4 = __UINT16_MAX__;
    u_int16_t testY4 = 0;
    double mappedValue4 = map(testX4, testY4);
    std::pair<u_int16_t, u_int16_t> unmappedValues4 = reverse_map(mappedValue4);
    std::cout << "--- Test Case 4 (Max X, Zero Y) ---" << std::endl;
    std::cout << "Original X: " << testX4 << ", Original Y: " << testY4 << std::endl;
    std::cout << "Mapped Value: " << mappedValue4 << std::endl;
    std::cout << "Unmapped X: " << unmappedValues4.first << ", Unmapped Y: " << unmappedValues4.second << std::endl;
    std::cout << "Match: " << (testX4 == unmappedValues4.first && testY4 == unmappedValues4.second ? "YES" : "NO") << std::endl << std::endl;

    // Test Case 5: Zero X, Max Y
    u_int16_t testX5 = 0;
    u_int16_t testY5 = __UINT16_MAX__;
    double mappedValue5 = map(testX5, testY5);
    std::pair<u_int16_t, u_int16_t> unmappedValues5 = reverse_map(mappedValue5);
    std::cout << "--- Test Case 5 (Zero X, Max Y) ---" << std::endl;
    std::cout << "Original X: " << testX5 << ", Original Y: " << testY5 << std::endl;
    std::cout << "Mapped Value: " << mappedValue5 << std::endl;
    std::cout << "Unmapped X: " << unmappedValues5.first << ", Unmapped Y: " << unmappedValues5.second << std::endl;
    std::cout << "Match: " << (testX5 == unmappedValues5.first && testY5 == unmappedValues5.second ? "YES" : "NO") << std::endl << std::endl;

    // Test Case 6: Random values
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<u_int16_t> dist(0, __UINT16_MAX__);

    std::cout << "--- Test Case 6 (Random Values) ---" << std::endl;
    for (int i = 0; i < 5; ++i) {
        u_int16_t randX = dist(rng);
        u_int16_t randY = dist(rng);
        double mappedRand = map(randX, randY);
        std::pair<u_int16_t, u_int16_t> unmappedRand = reverse_map(mappedRand);
        std::cout << "  Original X: " << randX << ", Original Y: " << randY << std::endl;
        std::cout << "  Mapped Value: " << mappedRand << std::endl;
        std::cout << "  Unmapped X: " << unmappedRand.first << ", Unmapped Y: " << unmappedRand.second << std::endl;
        std::cout << "  Match: " << (randX == unmappedRand.first && randY == unmappedRand.second ? "YES" : "NO") << std::endl << std::endl;
    }

    return 0;
}