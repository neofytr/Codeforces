#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    double V; // V is the maximum pan capacity, using double to prevent integer division issues

    // Read n and V
    std::cin >> n >> V;

    std::vector<double> a(n); // Recipe proportions (a_i)
    double sum_a = 0.0;       // Sum of all a_i, used to calculate total volume for a given x
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        sum_a += a[i]; // Accumulate sum of a_i
    }

    std::vector<double> b(n); // Available ingredient amounts (b_i)
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    // Calculate the maximum 'x' allowed by available ingredients
    // For each ingredient i, a_i * x <= b_i, which implies x <= b_i / a_i.
    // To satisfy this for all ingredients, x must be less than or equal to the minimum of all (b_i / a_i).
    double max_x_from_ingredients = std::numeric_limits<double>::max(); // Initialize with a very large number (effectively infinity)
    for (int i = 0; i < n; ++i) {
        // b[i] / a[i] gives the maximum x allowed by ingredient i
        max_x_from_ingredients = std::min(max_x_from_ingredients, b[i] / a[i]);
    }

    // Calculate the maximum 'x' allowed by the pan capacity
    // The total volume of soup is (sum of all a_i) * x, which is sum_a * x.
    // This total volume must be <= V.
    // So, sum_a * x <= V, which implies x <= V / sum_a.
    double max_x_from_pan_capacity = V / sum_a;

    // The actual maximum 'x' is limited by both the available ingredients and the pan capacity.
    double actual_x = std::min(max_x_from_ingredients, max_x_from_pan_capacity);

    // The total volume of soup cooked is (sum of all a_i) * actual_x.
    double total_volume_cooked = sum_a * actual_x;

    // Output the result with sufficient precision (e.g., 10 decimal places)
    std::cout << std::fixed << std::setprecision(10) << total_volume_cooked << std::endl;

    return 0;
}