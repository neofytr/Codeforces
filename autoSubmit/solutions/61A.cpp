#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s1, s2;
    std::cin >> s1 >> s2;

    std::string result = "";
    result.reserve(s1.length()); // Pre-allocate memory for efficiency

    for (size_t i = 0; i < s1.length(); ++i) {
        if (s1[i] == s2[i]) {
            result += '0';
        } else {
            result += '1';
        }
    }

    std::cout << result << std::endl;

    return 0;
}