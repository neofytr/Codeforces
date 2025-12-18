#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::string s;
    std::cin >> s;

    int uppercase_count = 0;
    int lowercase_count = 0;

    for (char c : s) {
        if (std::isupper(c)) {
            uppercase_count++;
        } else {
            lowercase_count++;
        }
    }

    if (uppercase_count > lowercase_count) {
        // Convert entire word to uppercase
        for (char &c : s) {
            c = std::toupper(c);
        }
    } else {
        // Convert entire word to lowercase
        for (char &c : s) {
            c = std::tolower(c);
        }
    }

    std::cout << s << std::endl;

    return 0;
}