#include <bits/stdc++.h>

int main() {
    // Optimize C++ standard streams for competitive programming.
    // Unties cin from cout and disables synchronization with C stdio.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of words

    // Loop n times to process each word
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word; // Read the current word

        int len = word.length(); // Get the length of the word

        // Check if the word's length is strictly greater than 10 characters
        if (len > 10) {
            // If it's too long, print the abbreviation:
            // First character + (length - 2) + last character
            std::cout << word[0];             // Print the first character
            std::cout << (len - 2);           // Print the count of characters in between
            std::cout << word[len - 1];       // Print the last character
            std::cout << "\n";                // Print a newline
        } else {
            // If the word is not too long (length <= 10), print it as is
            std::cout << word << "\n";        // Print the original word followed by a newline
        }
    }

    return 0; // Indicate successful execution
}