#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    std::set<int> unique_numbers;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        unique_numbers.insert(x);
    }

    if (unique_numbers.size() < 2) {
        std::cout << "NO\n";
    } else {
        // The set stores elements in sorted order.
        // The first element is *unique_numbers.begin().
        // The second element is *std::next(unique_numbers.begin()).
        auto it = unique_numbers.begin();
        std::advance(it, 1); // Move iterator to the second element
        std::cout << *it << "\n";
    }

    return 0;
}