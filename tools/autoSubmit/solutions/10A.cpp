#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    // P1, P2, P3 are power consumption rates in watts per minute.
    // T1, T2 are time thresholds in minutes.
    // These values fit within 'int' based on constraints (0-100 for P, 1-60 for T).
    int P1, P2, P3, T1, T2; 
    std::cin >> n >> P1 >> P2 >> P3 >> T1 >> T2;

    // Store the start and end times for each work period.
    // L[i] and R[i] represent [li, ri].
    // Times are up to 1440 minutes, fitting in 'int'.
    std::vector<int> L(n);
    std::vector<int> R(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> L[i] >> R[i];
    }

    // total_power can accumulate to a large value (up to 1440 * 100 * (approx 100 segments)),
    // so using 'long long' is safer to prevent overflow, although 'int' might just barely suffice.
    long long total_power = 0;

    // Calculate power consumed during each work interval [Li, Ri].
    // During work intervals, Tom continuously interacts, so the laptop is always in Normal mode (P1).
    for (int i = 0; i < n; ++i) {
        long long duration_work = R[i] - L[i];
        total_power += duration_work * P1;
    }

    // Calculate power consumed during idle intervals between work periods [Ri, L(i+1)].
    // This loop runs for n-1 idle periods.
    for (int i = 0; i < n - 1; ++i) {
        long long idle_duration = L[i+1] - R[i]; // Duration Tom is away from the laptop.

        if (idle_duration <= T1) {
            // Case 1: Idle duration is short (<= T1 minutes).
            // Laptop stays in Normal mode (P1) for the entire idle duration.
            total_power += idle_duration * P1;
        } else if (idle_duration <= T1 + T2) {
            // Case 2: Idle duration is medium (T1 < idle_duration <= T1 + T2 minutes).
            // Laptop is in Normal mode (P1) for T1 minutes.
            // Then switches to Screensaver mode (P2) for the remaining (idle_duration - T1) minutes.
            total_power += (long long)T1 * P1; // T1 cast to long long to ensure product is long long
            total_power += (idle_duration - T1) * P2;
        } else {
            // Case 3: Idle duration is long (idle_duration > T1 + T2 minutes).
            // Laptop is in Normal mode (P1) for T1 minutes.
            // Then switches to Screensaver mode (P2) for T2 minutes.
            // Finally, switches to Sleep mode (P3) for the remaining (idle_duration - T1 - T2) minutes.
            total_power += (long long)T1 * P1; // T1 cast to long long to ensure product is long long
            total_power += (long long)T2 * P2; // T2 cast to long long
            total_power += (idle_duration - T1 - T2) * P3;
        }
    }

    std::cout << total_power << std::endl;

    return 0;
}