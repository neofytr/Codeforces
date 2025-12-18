#include <bits/stdc++.h>

int count_vowels(const std::string& s) {
    int count = 0;
    for (char c : s) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line1, line2, line3;

    std::getline(std::cin, line1);
    std::getline(std::cin, line2);
    std::getline(std::cin, line3);

    int s1 = count_vowels(line1);
    int s2 = count_vowels(line2);
    int s3 = count_vowels(line3);

    if (s1 == 5 && s2 == 7 && s3 == 5) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}