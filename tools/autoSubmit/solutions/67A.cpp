#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Required for std::max

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s; // s will contain n-1 characters

    // Initialize toffees for all students to 1, as each student receives at least one.
    std::vector<int> toffees(n, 1);

    // First pass: Left to Right
    // This pass ensures that for relations 'R' (right student higher) and '=' (equal marks),
    // the current student's toffees (toffees[i+1]) are at least the minimum required
    // based on the previous student's toffees (toffees[i]).
    // 'L' relations (left student higher) cannot be fully resolved in this pass for toffees[i]
    // because toffees[i+1] might not yet have its final minimum value.
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == 'R') {
            // Right student has higher marks, so toffees[i+1] must be greater than toffees[i].
            // To minimize, we set toffees[i+1] to be at least toffees[i] + 1.
            // Use std::max to ensure we don't decrease a value that might have been
            // set higher by another condition (though not strictly necessary in a pure L->R pass
            // for 'R' conditions, it's safer for '=' conditions and general robustness).
            toffees[i+1] = std::max(toffees[i+1], toffees[i] + 1);
        } else if (s[i] == '=') {
            // Marks are equal, so toffees[i+1] must be equal to toffees[i].
            // toffees[i+1] must be at least toffees[i].
            toffees[i+1] = std::max(toffees[i+1], toffees[i]);
        }
    }

    // Second pass: Right to Left
    // This pass handles 'L' relations (left student higher) and ensures '=' conditions
    // are met when propagating from right to left. It ensures that toffees[i]
    // is at least the minimum required based on toffees[i+1].
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] == 'L') {
            // Left student has higher marks, so toffees[i] must be greater than toffees[i+1].
            // To minimize, we set toffees[i] to be at least toffees[i+1] + 1.
            toffees[i] = std::max(toffees[i], toffees[i+1] + 1);
        } else if (s[i] == '=') {
            // Marks are equal, so toffees[i] must be equal to toffees[i+1].
            // toffees[i] must be at least toffees[i+1].
            toffees[i] = std::max(toffees[i], toffees[i+1]);
        }
    }

    // Print the final distribution of toffees
    for (int i = 0; i < n; ++i) {
        std::cout << toffees[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;

    return 0;
}