#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    long long factorial = 1; // Use long long just to be safe, though int is enough for n <= 10
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }
    std::cout << factorial << std::endl;
    return 0;
}