#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s;

    int consecutive_zeros = 0;
    int consecutive_ones = 0;
    bool dangerous = false;

    for (char c : s) {
        if (c == '0') {
            consecutive_zeros++;
            consecutive_ones = 0;
        } else { // c == '1'
            consecutive_ones++;
            consecutive_zeros = 0;
        }

        if (consecutive_zeros >= 7 || consecutive_ones >= 7) {
            dangerous = true;
            break; 
        }
    }

    if (dangerous) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}