#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int w;
    std::cin >> w;

    // The watermelon can be divided into two parts, each weighing an even number of kilos,
    // and each part having a positive weight, if and only if:
    // 1. The total weight 'w' must be an even number. (Because sum of two even numbers is even).
    // 2. Each part must have a positive weight.
    // If w is even, we can try to divide it into 2 and (w-2).
    // Both 2 and (w-2) are even.
    // 2 is positive. For (w-2) to be positive, w must be greater than 2.
    // So, if w is even AND w > 2, it's possible.
    // Example: w=8 -> (2,6) or (4,4). Both YES.
    // Example: w=4 -> (2,2). YES.
    // Example: w=2 -> Cannot divide into two positive even parts. (1,1) are odd. (2,0) means one part is not positive. NO.
    // Example: w=3 -> Odd. NO.
    
    if (w % 2 == 0 && w > 2) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}