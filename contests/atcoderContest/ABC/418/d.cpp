#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;
    std::string T;
    std::cin >> T;

    std::vector<int> prefix_ones(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        prefix_ones[i + 1] = prefix_ones[i] + (T[i] - '0');
    }

    long long total_beautiful_substrings = 0;
    long long even_vals = 0;
    long long odd_vals = 0;

    for (int k = 0; k <= N; ++k) {
        int val_mod_2 = (k - prefix_ones[k]) % 2;
        if (val_mod_2 < 0) {
            val_mod_2 += 2;
        }

        if (val_mod_2 == 0) {
            total_beautiful_substrings += even_vals;
            even_vals++;
        } else {
            total_beautiful_substrings += odd_vals;
            odd_vals++;
        }
    }

    std::cout << total_beautiful_substrings << std::endl;

    return 0;
}