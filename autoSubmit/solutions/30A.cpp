#include <bits/stdc++.h>

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int A, B, n;
    std::cin >> A >> B >> n;

    // Case 1: A is 0
    if (A == 0) {
        if (B == 0) {
            // The equation becomes 0 * X^n = 0, which simplifies to 0 = 0.
            // Any integer X is a valid solution. As per problem statement, output any.
            // The example for 0 0 10 outputs 5. Outputting 0 is also a simple and valid choice.
            std::cout << 0 << std::endl;
        } else {
            // The equation becomes 0 * X^n = B where B != 0, which simplifies to 0 = B.
            // This is impossible. No solution exists.
            std::cout << "No solution" << std::endl;
        }
        return 0; // Terminate after handling A=0 cases
    }

    // Case 2: A is not 0
    // The equation is A * X^n = B. We need to find an integer X.
    // This can be rewritten as X^n = B / A.
    // For X to be an integer, B must be perfectly divisible by A.
    if (B % A != 0) {
        // If B is not divisible by A, then B/A is fractional.
        // X^n would be fractional, meaning X cannot be an integer.
        std::cout << "No solution" << std::endl;
        return 0; // Terminate as no integer solution exists
    }

    // Calculate the target value for X^n
    int target = B / A;

    // Iterate through possible integer values of X.
    // Constraints: |A|, |B| <= 1000, 1 <= n <= 10.
    // This means |target| <= 1000.
    // If a solution X exists, it won't be an extremely large number.
    // For n=1, X = target, so X can be up to 1000 or -1000.
    // For n=2, X^2 = target, |X| <= sqrt(1000) which is approximately 31.
    // For n=10, X^10 = target, |X| <= 1000^(1/10) which is approximately 1.99. So X could be -1, 0, 1.
    // Iterating X from -1000 to 1000 covers all possible integer solutions within these constraints efficiently.
    for (int X = -1000; X <= 1000; ++X) {
        long long current_X_pow_n = 1; // Stores X raised to some power. Use long long to prevent intermediate overflow.
        bool possible_match = true;    // Flag to track if X^n can still be 'target' without exceeding its magnitude

        // Handle X=0 separately, as 0^n = 0 for n >= 1 (given 1 <= n <= 10).
        if (X == 0) {
            current_X_pow_n = 0;
        } else {
            for (int i = 0; i < n; ++i) {
                // Before multiplying, check if `current_X_pow_n * X` would exceed the magnitude of 1000.
                // The target is in [-1000, 1000]. If an intermediate product goes beyond this,
                // further multiplication will only increase its magnitude (for |X|>1),
                // so it cannot be 'target'. This also implicitly prevents actual `long long` overflow.
                // Using `1001LL` as a safe upper bound for checking magnitude, since `1000` itself is a valid value.

                if (current_X_pow_n > 0) {
                    if (X > 0 && current_X_pow_n > 1001LL / X) { 
                        possible_match = false; 
                        break; 
                    }
                    if (X < 0 && current_X_pow_n > 1001LL / std::abs(X)) { // current_X_pow_n * X will be negative
                        possible_match = false; 
                        break; 
                    }
                } else { // current_X_pow_n < 0
                    if (X > 0 && current_X_pow_n < -1001LL / X) { 
                        possible_match = false; 
                        break; 
                    }
                    if (X < 0 && current_X_pow_n < -1001LL / std::abs(X)) { // current_X_pow_n * X will be positive
                        possible_match = false; 
                        break; 
                    }
                }
                // (X=0 is handled outside this loop, so no need to check X=0 in divisions above)
                
                current_X_pow_n *= X;
            }
        }

        // If 'possible_match' is still true, it means current_X_pow_n did not exceed
        // the relevant magnitude during its calculation. Now, check if it equals 'target'.
        if (possible_match && current_X_pow_n == target) {
            std::cout << X << std::endl;
            return 0; // Found a solution, print it and terminate the program.
        }
    }

    // If the loop finishes without finding any integer solution for X, output "No solution".
    std::cout << "No solution" << std::endl;

    return 0;
}