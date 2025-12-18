#include <bits/stdc++.h>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();

    int n;
    std::cin >> n;

    std::string leader_handle;
    int max_total_points = std::numeric_limits<int>::min(); // Initialize with the smallest possible int value

    for (int i = 0; i < n; ++i) {
        std::string handle;
        int plus_hacks, minus_hacks;
        int points_a, points_b, points_c, points_d, points_e;
        
        std::cin >> handle >> plus_hacks >> minus_hacks >> points_a >> points_b >> points_c >> points_d >> points_e;

        int current_total_points = points_a + points_b + points_c + points_d + points_e;
        current_total_points += (plus_hacks * 100);
        current_total_points -= (minus_hacks * 50);

        if (current_total_points > max_total_points) {
            max_total_points = current_total_points;
            leader_handle = handle;
        }
    }

    std::cout << leader_handle << std::endl;

    return 0;
}