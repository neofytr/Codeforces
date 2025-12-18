#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::string s;
    std::cin >> s;

    std::string result_stack;

    for (char c : s) {
        if (result_stack.empty() || result_stack.back() != c) {
            result_stack.push_back(c);
        } else {
            result_stack.pop_back();
        }
    }

    std::cout << result_stack << std::endl;

    return 0;
}