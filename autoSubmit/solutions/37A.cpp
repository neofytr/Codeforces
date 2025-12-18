#include <bits/stdc++.h>

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    // A frequency array (or vector) is suitable here because bar lengths are
    // positive integers and do not exceed 1000.
    // counts[i] will store the number of bars of length i.
    // Initialize all counts to 0. Array size 1001 covers lengths from 0 to 1000.
    std::vector<int> counts(1001, 0); 
    
    // Read all bar lengths and update their counts.
    for (int i = 0; i < N; ++i) {
        int length;
        std::cin >> length;
        counts[length]++;
    }

    int max_height = 0;   // This will store the height of the tallest tower.
                          // The height of a tower is the number of bars it contains.
    int total_towers = 0; // This will store the total number of towers.
                          // To minimize the number of towers, each distinct bar length
                          // must form exactly one tower.

    // Iterate through possible bar lengths (from 1 to 1000, as lengths are natural numbers).
    for (int i = 1; i <= 1000; ++i) {
        if (counts[i] > 0) {
            // If there are bars of length 'i' (counts[i] > 0), they form one tower.
            total_towers++;
            
            // Update max_height if the current tower is taller.
            if (counts[i] > max_height) {
                max_height = counts[i];
            }
        }
    }

    // Output the height of the largest tower and the total number of towers.
    std::cout << max_height << " " << total_towers << std::endl;

    return 0;
}