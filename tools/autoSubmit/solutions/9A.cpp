#include <bits/stdc++.h>

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin from cout and disables synchronization with C's stdio library,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int Y, W;
    // Read the points Yakko and Wakko got from their die rolls.
    std::cin >> Y >> W;

    // Dot wins if her roll is greater than or equal to the maximum roll of Yakko and Wakko.
    // This is because Yakko and Wakko are gentlemen and will let Dot win in case of a tie.
    // We find the maximum points rolled by Yakko or Wakko.
    int max_roll_from_others = std::max(Y, W);

    // A standard six-sided die has faces 1, 2, 3, 4, 5, 6.
    // Dot needs to roll a number 'D' such that D >= max_roll_from_others.
    // The favorable outcomes for Dot are the numbers from max_roll_from_others up to 6.
    // For example, if max_roll_from_others is 4, Dot can roll 4, 5, or 6 to win.
    // The number of favorable outcomes is (6 - max_roll_from_others + 1).
    int favorable_outcomes = (6 - max_roll_from_others + 1);

    // The total possible outcomes when rolling a six-sided die is 6.
    int total_outcomes = 6;

    // To output the probability as an irreducible fraction (A/B),
    // we need to find the greatest common divisor (GCD) of the numerator (favorable_outcomes)
    // and the denominator (total_outcomes).
    // The std::gcd function is available in <numeric> (included by <bits/stdc++.h>).
    int common_divisor = std::gcd(favorable_outcomes, total_outcomes);

    // Divide both the favorable outcomes and total outcomes by their GCD
    // to get the irreducible fraction.
    int numerator = favorable_outcomes / common_divisor;
    int denominator = total_outcomes / common_divisor;

    // Print the result in the specified format "A/B".
    std::cout << numerator << "/" << denominator << std::endl;

    return 0;
}