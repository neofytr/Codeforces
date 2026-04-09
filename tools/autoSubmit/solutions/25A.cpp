#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> even_indices;
    std::vector<int> odd_indices;

    for (int i = 1; i <= n; ++i) {
        int num;
        std::cin >> num;
        if (num % 2 == 0) {
            even_indices.push_back(i);
        } else {
            odd_indices.push_back(i);
        }
    }

    if (even_indices.size() == 1) {
        std::cout << even_indices[0] << std::endl;
    } else {
        // According to the problem statement, it is guaranteed that
        // exactly one of these numbers differs from the others in evenness.
        // So, if not exactly one even number, then it must be exactly one odd number.
        std::cout << odd_indices[0] << std::endl;
    }

    return 0;
}