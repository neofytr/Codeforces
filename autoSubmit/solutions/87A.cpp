#include <iostream>
#include <numeric> // For std::gcd (C++17 standard)
#include <algorithm> // For std::min, std::swap

// Custom GCD function for broader compatibility (e.g., C++11/14 environments)
// std::gcd is available in <numeric> since C++17.
// Using a custom one ensures compatibility and can be slightly faster for specific setups.
long long my_gcd(long long a, long long b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long a, b;
    std::cin >> a >> b;

    // Calculate the greatest common divisor of a and b.
    // This allows reducing the problem to smaller, coprime numbers,
    // which simplifies the simulation cycle.
    long long common_divisor = my_gcd(a, b);

    // Reduce a and b by dividing by their GCD.
    // aa and bb are now coprime.
    long long aa = a / common_divisor;
    long long bb = b / common_divisor;

    // The least common multiple (LCM) of original a and b is (a * b) / GCD(a,b).
    // In the reduced system, the LCM of aa and bb is simply aa * bb,
    // because they are coprime. This product represents the length of one full cycle
    // after which the pattern of train arrivals repeats.
    long long cycle_length = aa * bb;

    // Initialize scores for Dasha and Masha. These will accumulate the total
    // "minutes" Vasya spends favoring each girlfriend within one cycle.
    long long dasha_score = 0;
    long long masha_score = 0;

    // current_time tracks the elapsed time within the cycle, starting from 0.
    long long current_time = 0;
    // next_d_arrival and next_m_arrival track the next scheduled train arrival
    // for Dasha and Masha, respectively, in the reduced time system.
    long long next_d_arrival = aa;
    long long next_m_arrival = bb;

    // The simulation iterates through distinct "events" where a train arrives.
    // An event occurs when either a Dasha train or a Masha train (or both) are scheduled to arrive.
    // The loop continues until the entire cycle_length has been simulated.
    while (current_time < cycle_length) {
        // Determine the time of the very next train arrival (either Dasha's or Masha's).
        long long next_event_time = std::min(next_d_arrival, next_m_arrival);
        // The length of the current interval during which the decision (who arrives first) is constant.
        long long interval_length = next_event_time - current_time;

        // Apply the decision rules based on which train arrives earlier:
        if (next_d_arrival < next_m_arrival) {
            // Dasha's train arrives strictly earlier. Vasya goes to Dasha.
            dasha_score += interval_length;
        } else if (next_m_arrival < next_d_arrival) {
            // Masha's train arrives strictly earlier. Vasya goes to Masha.
            masha_score += interval_length;
        } else { // next_d_arrival == next_m_arrival; both trains arrive simultaneously
            // This is the tie-breaking condition. Vasya goes towards the direction
            // with the lower frequency of going trains (i.e., the one with the larger period).
            if (a > b) { // Dasha's trains are less frequent (larger period 'a')
                dasha_score += interval_length;
            } else { // Masha's trains are less frequent (larger period 'b', since a != b)
                masha_score += interval_length;
            }
        }

        // Advance current_time to the time of the next event.
        current_time = next_event_time;

        // Update the next arrival times for the trains that just arrived.
        // It's crucial to use independent 'if' statements here because both trains
        // can arrive simultaneously (when next_d_arrival == next_m_arrival == current_time).
        if (next_d_arrival == current_time) {
            next_d_arrival += aa; // Schedule the next Dasha train
        }
        if (next_m_arrival == current_time) {
            next_m_arrival += bb; // Schedule the next Masha train
        }
    }

    // After simulating one full cycle, compare the total scores to determine the winner.
    if (dasha_score > masha_score) {
        std::cout << "Dasha\n";
    } else if (masha_score > dasha_score) {
        std::cout << "Masha\n";
    } else {
        std::cout << "Equal\n";
    }

    return 0;
}