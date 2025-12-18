#include <bits/stdc++.h>

// Function to get the last boarding time for a group of students
// students_count: number of students in the group
// offset: 0 for red (arrives at 0, 3, 6,...), 1 for green (arrives at 1, 4, 7,...), 2 for blue (arrives at 2, 5, 8,...)
long long get_last_boarding_time(int students_count, int offset) {
    if (students_count == 0) {
        return -1; // Indicate no students of this type, will be ignored by max logic
    }
    // Calculate the number of cablecars needed for this group.
    // (students_count + 1) / 2 is an integer division equivalent to ceil(students_count / 2.0) for positive integers.
    long long num_cars_needed = (students_count + 1) / 2;
    
    // The k-th cablecar (0-indexed) of a specific color arrives at time (k * 3 + offset).
    // The (num_cars_needed - 1)-th cablecar will be the one that carries the last student(s) of this group.
    return (num_cars_needed - 1) * 3 + offset;
}

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int r, g, b;
    std::cin >> r >> g >> b;

    // Initialize max_boarding_time to 0. Since r+g+b > 0, at least one student will board
    // at time 0 or later, so 0 is a safe initial value for the maximum boarding time.
    long long max_boarding_time = 0;

    // Calculate the boarding time for the last red student
    long long red_last_board_time = get_last_boarding_time(r, 0);
    if (red_last_board_time != -1) {
        max_boarding_time = std::max(max_boarding_time, red_last_board_time);
    }

    // Calculate the boarding time for the last green student
    long long green_last_board_time = get_last_boarding_time(g, 1);
    if (green_last_board_time != -1) {
        max_boarding_time = std::max(max_boarding_time, green_last_board_time);
    }

    // Calculate the boarding time for the last blue student
    long long blue_last_board_time = get_last_boarding_time(b, 2);
    if (blue_last_board_time != -1) {
        max_boarding_time = std::max(max_boarding_time, blue_last_board_time);
    }
    
    // The total time required is the latest time any student boarded a cablecar,
    // plus the fixed 30 minutes it takes for any cablecar to reach the top.
    long long total_time = max_boarding_time + 30;

    std::cout << total_time << std::endl;

    return 0;
}