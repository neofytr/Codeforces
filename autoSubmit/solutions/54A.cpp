#include <bits/stdc++.h>

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, K;
    std::cin >> N >> K;

    int C;
    std::cin >> C;

    // Use a boolean vector to mark holiday days.
    // Days are 1-indexed, so size N+1.
    std::vector<bool> is_holiday(N + 1, false);
    for (int i = 0; i < C; ++i) {
        int day;
        std::cin >> day;
        is_holiday[day] = true;
    }

    int presents_count = 0;
    // 'last_present_day' stores the day the last present was received.
    // According to the problem, "today's day is zero, and you should regard today's present as
    // already given (i.e., you shouldn't count it in the answer)."
    // So, we initialize last_present_day to 0 to reflect a present being received on day 0.
    int last_present_day = 0; 

    // Iterate through each day from 1 to N to count presents.
    for (int day = 1; day <= N; ++day) {
        // Principle 1: On each holiday day, the Hedgehog will necessarily receive a present.
        if (is_holiday[day]) {
            presents_count++;
            last_present_day = day; // Update the day a present was last received
        } 
        // Principle 2: He receives presents at least every K days.
        // This means if a present was received on day 'i' (last_present_day),
        // the next present must be received no later than on day 'i + K'.
        // To minimize the total number of presents, we take a present on day 'i + K'
        // ONLY if we haven't already taken one between day 'i+1' and 'i+K-1'
        // (which would be covered by Principle 1).
        // This condition is checked only if 'day' is NOT a holiday (due to 'else if').
        else if (day == last_present_day + K) {
            presents_count++;
            last_present_day = day; // Update the day a present was last received
        }
    }

    std::cout << presents_count << std::endl;

    return 0;
}