#include <bits/stdc++.h>

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // The problem states that 1 <= a_i <= 3000.
    // This means the maximum possible index that can be provided is 3000.
    // If all numbers from 1 to 3000 are present in the input,
    // the smallest missing positive integer would be 3001.
    // Therefore, we need a boolean array to keep track of numbers up to 3001.
    // A size of 3002 is sufficient to cover indices 0 through 3001.
    const int MAX_POSSIBLE_INDEX_VALUE = 3001; 
    std::vector<bool> seen(MAX_POSSIBLE_INDEX_VALUE + 1, false);

    // Read the n distinct integers and mark their presence in the 'seen' array.
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        // Since 1 <= val <= 3000, val will always be within the bounds of our vector (1 to 3001).
        seen[val] = true;
    }

    // Iterate from 1 upwards to find the smallest positive integer
    // that has not been seen.
    // We are guaranteed to find such an integer because n <= 3000,
    // meaning at least one number in the range [1, 3001] must be missing.
    for (int i = 1; i <= MAX_POSSIBLE_INDEX_VALUE; ++i) {
        if (!seen[i]) {
            std::cout << i << std::endl;
            return 0; // Found the answer, exit the program.
        }
    }

    // This part of the code should logically be unreachable given the constraints.
    // If we reach here, it implies all numbers from 1 to MAX_POSSIBLE_INDEX_VALUE (3001)
    // were present, which would require n to be 3001, but n <= 3000.
    return 0; 
}