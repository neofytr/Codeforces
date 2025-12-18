#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    // The problem states d_i years to rise from rank i to rank i+1.
    // There are n-1 such values: d_1, d_2, ..., d_{n-1}.
    // We store these in a 0-indexed vector.
    // d[0] will correspond to d_1 (time from rank 1 to 2)
    // d[1] will correspond to d_2 (time from rank 2 to 3)
    // ...
    // d[k-1] will correspond to d_k (time from rank k to k+1)
    // d[n-2] will correspond to d_{n-1} (time from rank n-1 to n)
    std::vector<int> d(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> d[i];
    }

    int a, b;
    std::cin >> a >> b;

    long long total_years = 0;

    // Vasya is currently at rank 'a' and dreams of holding rank 'b'.
    // Since 1 <= a < b <= n, Vasya always needs to advance.
    // He needs to go through the following promotions:
    // a   -> a+1 (takes d_a years)
    // a+1 -> a+2 (takes d_{a+1} years)
    // ...
    // b-1 -> b   (takes d_{b-1} years)
    //
    // In our 0-indexed vector 'd', d_k corresponds to d[k-1].
    // So, we need to sum d[a-1], d[a], ..., d[b-2].
    // The loop iterates from index a-1 up to (but not including) b-1.
    for (int i = a - 1; i < b - 1; ++i) {
        total_years += d[i];
    }

    std::cout << total_years << std::endl;

    return 0;
}