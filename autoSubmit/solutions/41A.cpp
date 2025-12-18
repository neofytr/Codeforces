#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string s, t;
    std::cin >> s >> t;
    std::reverse(s.begin(), s.end());
    if (s == t) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}