#include <bits/stdc++.h>

// Function to check if s1 followed by s2 can be found in text sequentially and non-overlapping
bool check(const std::string& text, const std::string& s1, const std::string& s2) {
    size_t pos1 = 0;
    // Iterate through all possible starting positions of s1 in text
    while ((pos1 = text.find(s1, pos1)) != std::string::npos) {
        // s1 is found at pos1.
        // Now, we need to search for s2 starting strictly after s1 ends.
        // The earliest s2 can start is pos1 + s1.length().
        size_t search_start_for_s2 = pos1 + s1.length();
        
        // Attempt to find s2 in the 'text' starting from 'search_start_for_s2'.
        // std::string::find handles cases where search_start_for_s2 is too large
        // (i.e., past the end of the string or not enough room for s2) by returning std::string::npos.
        if (text.find(s2, search_start_for_s2) != std::string::npos) {
            return true; // Found s1 followed by s2 non-overlappingly
        }
        
        // Move pos1 forward by one to continue searching for the next occurrence of s1.
        // This is important for cases like text="aaaa", s1="a", s2="a" to find
        // (s1 at index 0, s2 at index 1), then (s1 at index 1, s2 at index 2), etc.
        // If we incremented by s1.length(), we might miss valid starting positions for s1.
        pos1++; 
    }
    return false; // No such pair of sequences found
}

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s_full_path, s1_first_wake, s2_second_wake;
    
    // Read the main path string (A to B)
    std::cin >> s_full_path;
    // Read the two sequences Peter saw
    std::cin >> s1_first_wake >> s2_second_wake;

    // Check if sequences can be seen in forward direction (A to B)
    bool can_forward = check(s_full_path, s1_first_wake, s2_second_wake);

    // Create the reversed path string for backward direction (B to A)
    std::string s_reversed_path = s_full_path;
    std::reverse(s_reversed_path.begin(), s_reversed_path.end());
    
    // Check if sequences can be seen in backward direction (B to A)
    bool can_backward = check(s_reversed_path, s1_first_wake, s2_second_wake);

    // Determine the output based on the findings
    if (can_forward && can_backward) {
        std::cout << "both\n";
    } else if (can_forward) {
        std::cout << "forward\n";
    } else if (can_backward) {
        std::cout << "backward\n";
    } else {
        std::cout << "fantasy\n";
    }

    return 0;
}