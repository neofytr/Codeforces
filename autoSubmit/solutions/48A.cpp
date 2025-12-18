#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Not strictly needed, but common in bits/stdc++.h

// Function to determine if gesture1 beats gesture2
bool beats(const std::string& g1, const std::string& g2) {
    if (g1 == "rock" && g2 == "scissors") return true;
    if (g1 == "scissors" && g2 == "paper") return true;
    if (g1 == "paper" && g2 == "rock") return true;
    return false;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string f_gesture, m_gesture, s_gesture;

    // Read the gestures for Uncle Fyodor (F), Matroskin (M), and Sharic (S)
    std::cin >> f_gesture >> m_gesture >> s_gesture;

    // Determine if Uncle Fyodor wins
    // F wins if F's gesture beats M's gesture AND F's gesture beats S's gesture
    bool f_wins = beats(f_gesture, m_gesture) && beats(f_gesture, s_gesture);

    // Determine if Matroskin wins
    // M wins if M's gesture beats F's gesture AND M's gesture beats S's gesture
    bool m_wins = beats(m_gesture, f_gesture) && beats(m_gesture, s_gesture);

    // Determine if Sharic wins
    // S wins if S's gesture beats F's gesture AND S's gesture beats M's gesture
    bool s_wins = beats(s_gesture, f_gesture) && beats(s_gesture, m_gesture);

    // Print the result
    if (f_wins) {
        std::cout << "F\n";
    } else if (m_wins) {
        std::cout << "M\n";
    } else if (s_wins) {
        std::cout << "S\n";
    } else {
        // If no one satisfies the winning condition, another round is required
        std::cout << "?\n";
    }

    return 0;
}