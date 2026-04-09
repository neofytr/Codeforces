#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::getline(std::cin, s);

    char last_letter = ' '; // Initialize with a non-letter character

    // Iterate backwards from the character before the question mark
    // (s.length() - 1 is '?', so s.length() - 2 is the character before it)
    for (int i = s.length() - 2; i >= 0; --i) {
        char c = s[i];
        if (std::isalpha(c)) {
            last_letter = std::tolower(c); // Convert to lowercase for comparison
            break; // Found the last letter, exit loop
        }
    }

    if (last_letter == 'a' || last_letter == 'e' || last_letter == 'i' ||
        last_letter == 'o' || last_letter == 'u' || last_letter == 'y') {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}