#include <bits/stdc++.h>

void solve() {
    std::string s;
    std::cin >> s;

    std::string normalized_path;
    bool was_slash = false; // Flag to track if the last appended character was a slash

    for (char c : s) {
        if (c == '/') {
            // Only append a slash if the previous character appended was not a slash
            // This collapses multiple slashes into one
            if (!was_slash) {
                normalized_path.push_back(c);
                was_slash = true;
            }
        } else { // c is a letter
            normalized_path.push_back(c);
            was_slash = false;
        }
    }

    // After processing all characters, handle the trailing slash rule:
    // A trailing '/' is required only for the root directory path ("/").
    // If the normalized path is longer than just "/" and ends with "/", remove that trailing slash.
    if (normalized_path.length() > 1 && normalized_path.back() == '/') {
        normalized_path.pop_back();
    }

    std::cout << normalized_path << std::endl;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}