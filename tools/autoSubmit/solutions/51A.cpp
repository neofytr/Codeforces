#include <bits/stdc++.h>

// Function to calculate the canonical form of an amulet
// An amulet is represented as:
// a b
// c d
// The canonical form is the smallest integer representation among its four rotations.
int get_canonical_form(int a, int b, int c, int d) {
    // Original orientation: a b c d
    int s0 = a * 1000 + b * 100 + c * 10 + d;

    // 90 degrees clockwise rotation:
    // c a
    // d b
    // Sequence: c a d b
    int s90 = c * 1000 + a * 100 + d * 10 + b;

    // 180 degrees clockwise rotation:
    // d c
    // b a
    // Sequence: d c b a
    int s180 = d * 1000 + c * 100 + b * 10 + a;

    // 270 degrees clockwise rotation:
    // b d
    // a c
    // Sequence: b d a c
    int s270 = b * 1000 + d * 100 + a * 10 + c;

    // Return the minimum of all four rotations
    return std::min({s0, s90, s180, s270});
}

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // A set to store the canonical forms of unique amulets
    std::set<int> unique_amulets;

    for (int i = 0; i < n; ++i) {
        std::string s1, s2;
        std::cin >> s1 >> s2; // Read the two lines describing the amulet

        // Extract the four digits from the input strings
        int a = s1[0] - '0';
        int b = s1[1] - '0';
        int c = s2[0] - '0';
        int d = s2[1] - '0';

        // Calculate the canonical form and insert it into the set
        unique_amulets.insert(get_canonical_form(a, b, c, d));

        // Read the separator string "**" if it's not the last amulet
        if (i < n - 1) {
            std::string separator;
            std::cin >> separator;
        }
    }

    // The number of unique amulets (piles) is the size of the set
    std::cout << unique_amulets.size() << std::endl;

    return 0;
}