#include <bits/stdc++.h>

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // A set to store unique pairs of (species, color)
    std::set<std::pair<std::string, std::string>> unique_leaves;

    for (int i = 0; i < n; ++i) {
        std::string species, color;
        std::cin >> species >> color;
        // Insert the pair into the set. std::set automatically handles uniqueness.
        unique_leaves.insert({species, color});
    }

    // The size of the set will be the number of unique leaves Alyona has picked.
    std::cout << unique_leaves.size() << std::endl;

    return 0;
}