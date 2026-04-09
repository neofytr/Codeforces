#include <bits/stdc++.h>

void solve() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::map<std::string, int> note_to_semitone;
    note_to_semitone["C"] = 0;
    note_to_semitone["C#"] = 1;
    note_to_semitone["D"] = 2;
    note_to_semitone["D#"] = 3;
    note_to_semitone["E"] = 4;
    note_to_semitone["F"] = 5;
    note_to_semitone["F#"] = 6;
    note_to_semitone["G"] = 7;
    note_to_semitone["G#"] = 8;
    note_to_semitone["A"] = 9;
    note_to_semitone["B"] = 10;
    note_to_semitone["H"] = 11;

    std::string s1, s2, s3;
    std::cin >> s1 >> s2 >> s3;

    std::vector<int> p(3);
    p[0] = note_to_semitone[s1];
    p[1] = note_to_semitone[s2];
    p[2] = note_to_semitone[s3];

    bool is_major = false;
    bool is_minor = false;

    // To use std::next_permutation, the vector must be sorted initially.
    std::sort(p.begin(), p.end());

    do {
        int X = p[0];
        int Y = p[1];
        int Z = p[2];

        // Calculate distances cyclically (modulo 12)
        // (Y - X + 12) % 12 ensures positive result for (Y - X)
        int distXY = (Y - X + 12) % 12;
        int distYZ = (Z - Y + 12) % 12;

        // Check for major triad condition: X->Y = 4 semitones, Y->Z = 3 semitones
        if (distXY == 4 && distYZ == 3) {
            is_major = true;
            break; // Found a major arrangement, no need to check further
        }

        // Check for minor triad condition: X->Y = 3 semitones, Y->Z = 4 semitones
        if (distXY == 3 && distYZ == 4) {
            is_minor = true;
            break; // Found a minor arrangement, no need to check further
        }

    } while (std::next_permutation(p.begin(), p.end()));

    if (is_major) {
        std::cout << "major\n";
    } else if (is_minor) {
        std::cout << "minor\n";
    } else {
        std::cout << "strange\n";
    }
}

int main() {
    solve();
    return 0;
}