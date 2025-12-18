#include <bits/stdc++.h>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main() {
    fast_io();

    int p1, p2, p3, p4, a, b;
    std::cin >> p1 >> p2 >> p3 >> p4 >> a >> b;

    // The function f(x) is defined as a sequence of remainder operations.
    // If (q1, q2, q3, q4) is a permutation of (p1, p2, p3, p4), then
    // f(x) = (((x % q1) % q2) % q3) % q4.
    //
    // For f(x) = x to hold, we need the following conditions:
    // 1. x % q1 = x  => x < q1
    // 2. (x % q1) % q2 = x % q2. For this to be x, we need x < q2.
    // 3. And so on for q3 and q4.
    //
    // Therefore, f(x) = x if and only if x < q1, x < q2, x < q3, AND x < q4.
    // This simplifies to x < min(q1, q2, q3, q4).
    //
    // Since (q1, q2, q3, q4) is a permutation of (p1, p2, p3, p4),
    // min(q1, q2, q3, q4) is always equal to min(p1, p2, p3, p4).
    // Let P_min = min(p1, p2, p3, p4).
    //
    // So, the condition f(x) = x is equivalent to x < P_min, regardless of the permutation.
    //
    // If x < P_min, then f(x) = x for ALL 24 permutations.
    // If x >= P_min, then f(x) != x for ALL 24 permutations (specifically, x % P_min != x).
    //
    // The problem states Petya picks x if there exist at least 7 permutations for which f(x) = x.
    // Based on our deduction:
    // - If x < P_min, there are 24 such permutations (24 >= 7), so Petya picks x.
    // - If x >= P_min, there are 0 such permutations (0 < 7), so Petya does not pick x.
    //
    // Thus, Petya picks x if and only if x < P_min.

    // Find the minimum of p1, p2, p3, p4
    int p_min = std::min({p1, p2, p3, p4});

    // We need to count integers x in the range [a, b] such that x < P_min.
    // This is equivalent to counting x such that a <= x <= b AND x <= P_min - 1.
    // So, we are looking for x in the range [a, min(b, P_min - 1)].

    int effective_upper_bound = std::min(b, p_min - 1);

    int count = 0;
    if (effective_upper_bound >= a) {
        count = effective_upper_bound - a + 1;
    }

    std::cout << count << std::endl;

    return 0;
}