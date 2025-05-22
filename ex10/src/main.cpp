#include <iostream>
#include <iomanip> // Required for std::fixed and std::setprecision
#include <cstdint> // Required for u_int16_t, u_int32_t, and __UINT32_MAX__

// The map function (as corrected by you)
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

int main()
{
    u_int32_t max_val = __UINT32_MAX__;
    std::cout << "Value of __UINT32_MAX__: " << max_val << std::endl;

    // --- First test case: x=10, y=11 ---
    u_int16_t x_val_1 = 10;
    u_int16_t y_val_1 = 11;

    u_int32_t calculated_res_val_1 = 0;
    for (int i = 0; i < 16; ++i) {
        u_int16_t temp_x_bit = (x_val_1 >> i) & 1;
        u_int16_t temp_y_bit = (y_val_1 >> i) & 1;
        u_int16_t temp_interleaved_pair = (temp_y_bit << 1) | temp_x_bit;
        calculated_res_val_1 = calculated_res_val_1 | (static_cast<u_int32_t>(temp_interleaved_pair) << i * 2);
    }
    std::cout << "Calculated raw res for (" << x_val_1 << ", " << y_val_1 << "): " << calculated_res_val_1 << std::endl;

    double res_1 = map(x_val_1, y_val_1);
    // Set output precision for the double value
    std::cout << std::fixed << std::setprecision(20); // Print with 20 decimal places
    std::cout << "Result from map(" << x_val_1 << ", " << y_val_1 << "): " << res_1 << std::endl;

    // Reset precision if needed for subsequent outputs, or just keep it
    // std::cout << std::defaultfloat;

    std::cout << "\n"; // Newline for readability

    // --- Second test case: x=12345, y=54321 ---
    u_int16_t x_val_2 = 12345;
    u_int16_t y_val_2 = 54321;

    u_int32_t calculated_res_val_2 = 0;
    for (int i = 0; i < 16; ++i) {
        u_int16_t temp_x_bit = (x_val_2 >> i) & 1;
        u_int16_t temp_y_bit = (y_val_2 >> i) & 1;
        u_int16_t temp_interleaved_pair = (temp_y_bit << 1) | temp_x_bit;
        calculated_res_val_2 = calculated_res_val_2 | (static_cast<u_int32_t>(temp_interleaved_pair) << i * 2);
    }
    std::cout << "Calculated raw res for (" << x_val_2 << ", " << y_val_2 << "): " << calculated_res_val_2 << std::endl;

    double res_2 = map(x_val_2, y_val_2);
    std::cout << "Result from map(" << x_val_2 << ", " << y_val_2 << "): " << res_2 << std::endl;

    std::cout << "\n"; // Newline for readability

    // --- Third test case: x=65535, y=65533 (the "almost 1" case) ---
    u_int16_t x_val_3 = 65534; // 0xFFFF
    u_int16_t y_val_3 = 65534; // 0xFFFD

    u_int32_t calculated_res_val_3 = 0;
    for (int i = 0; i < 16; ++i) {
        u_int16_t temp_x_bit = (x_val_3 >> i) & 1;
        u_int16_t temp_y_bit = (y_val_3 >> i) & 1;
        u_int16_t temp_interleaved_pair = (temp_y_bit << 1) | temp_x_bit;
        calculated_res_val_3 = calculated_res_val_3 | (static_cast<u_int32_t>(temp_interleaved_pair) << i * 2);
    }
    std::cout << "Calculated raw res for (" << x_val_3 << ", " << y_val_3 << "): " << calculated_res_val_3 << std::endl;

    double res_3 = map(x_val_3, y_val_3);
    std::cout << "Result from map(" << x_val_3 << ", " << y_val_3 << "): " << res_3 << std::endl;

    return 0;
}