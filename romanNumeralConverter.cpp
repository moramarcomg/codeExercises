// Roman Numeral Converter
// Convert an integer (1-3999) to a Roman numeral.
// Roman numerals use combinations of letters: I, V, X, L, C, D, M.

#include <iostream>
#include <string>
#include <vector>

std::string intToRoman(int num) {
    // Greedy approach: map values in descending order with their symbols.
    // Chosen because Roman numerals are built from largest to smallest,
    // and the subtraction cases (IV, IX, XL, etc.) are explicitly listed,
    // so no special-case logic is needed at runtime.
    std::vector<std::pair<int, std::string>> value = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"},  {90, "XC"},  {50, "L"},  {40, "XL"},
        {10, "X"},   {9, "IX"},   {5, "V"},   {4, "IV"},
        {1, "I"}
    };

    std::string result;
    for (const auto& [val, symbol] : value) {
        while (num >= val) {
            result += symbol;
            num -= val;
        }
    }
    return result;
}

int main() {
    std::cout << 58 << " -> " << intToRoman(58) << std::endl;      // LVIII
    std::cout << 1994 << " -> " << intToRoman(1994) << std::endl;  // MCMXCIV
    std::cout << 3999 << " -> " << intToRoman(3999) << std::endl;  // MMMCMXCIX
    return 0;
}
