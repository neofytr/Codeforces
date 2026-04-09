#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cctype> // For std::isdigit

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // List of alcoholic drinks for quick lookup
    std::unordered_set<std::string> alcoholic_drinks = {
        "ABSINTH", "BEER", "BRANDY", "CHAMPAGNE", "GIN", "RUM", "SAKE",
        "TEQUILA", "VODKA", "WHISKEY", "WINE"
    };

    int n;
    std::cin >> n;

    int checks_needed = 0;
    std::string s;

    for (int i = 0; i < n; ++i) {
        std::cin >> s;

        // Check if the input string represents an age or a drink
        // If the first character is a digit, it's an age.
        // Otherwise, it's a drink name (guaranteed by problem statement).
        if (std::isdigit(s[0])) {
            int age = std::stoi(s); // Convert string to integer age
            if (age < 18) {
                // If the person is underage, Vasya needs to check what they are drinking.
                checks_needed++;
            }
        } else {
            // It's a drink name. Check if it's an alcoholic drink.
            if (alcoholic_drinks.count(s)) {
                // If they are drinking alcohol, Vasya needs to check their age.
                checks_needed++;
            }
        }
    }

    std::cout << checks_needed << std::endl;

    return 0;
}