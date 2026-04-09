#include <iostream>

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    long long n, m, a;
    std::cin >> n >> m >> a;

    // Calculate the number of flagstones needed along the length 'n'
    // We use ceiling division: (x + y - 1) / y for ceil(x / y)
    long long flagstones_n_dim = (n + a - 1) / a;

    // Calculate the number of flagstones needed along the width 'm'
    long long flagstones_m_dim = (m + a - 1) / a;

    // The total number of flagstones is the product of flagstones along each dimension
    long long total_flagstones = flagstones_n_dim * flagstones_m_dim;

    std::cout << total_flagstones << std::endl;

    return 0;
}