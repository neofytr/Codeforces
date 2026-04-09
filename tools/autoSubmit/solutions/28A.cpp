#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility> // For std::pair

// Function to calculate Manhattan distance between two points
int manhattan_distance(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
}

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m; // n: number of nails, m: number of rods
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> nails(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> nails[i].first >> nails[i].second;
    }

    // Store rod lengths along with their original 1-indexed numbers
    // This allows us to sort rods by length and still retrieve original indices.
    std::vector<std::pair<int, int>> rods(m); // Stores {length, original_index}
    for (int i = 0; i < m; ++i) {
        std::cin >> rods[i].first;
        rods[i].second = i + 1; // 1-indexed rod number
    }

    // Sort rods by length in ascending order
    std::sort(rods.begin(), rods.end());

    // Calculate the required rod length for each nail if it were chosen as a fold point.
    // The required length is the sum of distances from (P_prev, P_current) and (P_current, P_next).
    std::vector<int> req_len(n);
    for (int i = 0; i < n; ++i) {
        int prev_idx = (i - 1 + n) % n; // Circular previous nail index
        int next_idx = (i + 1) % n;     // Circular next nail index
        req_len[i] = manhattan_distance(nails[prev_idx], nails[i]) +
                     manhattan_distance(nails[i], nails[next_idx]);
    }

    // If there aren't enough rods to cover n/2 nails, it's impossible.
    // Since n is even, at most n/2 nails can be selected as fold points due to the non-adjacency constraint.
    if (m < n / 2) {
        std::cout << "NO\n";
        return 0;
    }

    // According to the problem constraints (n is even, "unoccupied" definition implies non-adjacent fold points),
    // there are two potential maximal sets of fold points that can be chosen:
    // 1. Set A: {P_0, P_2, ..., P_{n-2}} - all even-indexed nails
    // 2. Set B: {P_1, P_3, ..., P_{n-1}} - all odd-indexed nails
    // We try to satisfy the requirements for each set.

    // --- Attempt to solve using Set A (even-indexed nails as fold points) ---
    std::vector<std::pair<int, int>> req_A; // Stores {required_length, nail_index} for Set A
    for (int i = 0; i < n; i += 2) {
        req_A.push_back({req_len[i], i});
    }
    // Sort required lengths for Set A in ascending order
    std::sort(req_A.begin(), req_A.end());

    bool possible_A = true;
    std::vector<int> ans_A(n, -1); // Array to store results for Set A; -1 means no rod
    // Greedily match the smallest required lengths with the smallest available rods
    for (int i = 0; i < n / 2; ++i) {
        if (req_A[i].first > rods[i].first) { // If smallest required length is larger than smallest available rod
            possible_A = false;               // This set cannot be satisfied
            break;
        }
        ans_A[req_A[i].second] = rods[i].second; // Assign the rod to the nail
    }

    if (possible_A) {
        std::cout << "YES\n";
        for (int i = 0; i < n; ++i) {
            std::cout << ans_A[i] << (i == n - 1 ? "" : " ");
        }
        std::cout << "\n";
        return 0; // Solution found, exit
    }

    // --- Attempt to solve using Set B (odd-indexed nails as fold points) ---
    std::vector<std::pair<int, int>> req_B; // Stores {required_length, nail_index} for Set B
    for (int i = 1; i < n; i += 2) {
        req_B.push_back({req_len[i], i});
    }
    // Sort required lengths for Set B in ascending order
    std::sort(req_B.begin(), req_B.end());

    bool possible_B = true;
    std::vector<int> ans_B(n, -1); // Array to store results for Set B; -1 means no rod
    // Greedily match the smallest required lengths with the smallest available rods
    for (int i = 0; i < n / 2; ++i) {
        if (req_B[i].first > rods[i].first) { // If smallest required length is larger than smallest available rod
            possible_B = false;               // This set cannot be satisfied
            break;
        }
        ans_B[req_B[i].second] = rods[i].second; // Assign the rod to the nail
    }

    if (possible_B) {
        std::cout << "YES\n";
        for (int i = 0; i < n; ++i) {
            std::cout << ans_B[i] << (i == n - 1 ? "" : " ");
        }
        std::cout << "\n";
        return 0; // Solution found, exit
    }

    // If neither of the two maximal sets could be satisfied, then it's impossible.
    std::cout << "NO\n";

    return 0;
}