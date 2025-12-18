#include <bits/stdc++.h>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();

    long long initial_a;
    std::cin >> initial_a;

    std::string expr;
    std::cin >> expr;

    // s_times_C_values will store (sign * coefficient) for each summand.
    // Example: "5*a++" -> 5; "-3*++a" -> -3; "+a++" -> 1.
    std::vector<long long> s_times_C_values;
    
    // fixed_offset_sum stores the sum of (s*C) for all '++a' terms.
    // This part of the contribution (s*C*1) is fixed regardless of processing order.
    long long fixed_offset_sum = 0; 

    int current_idx = 0; // Current position in the expression string
    long long current_global_sign = 1; // Tracks the sign (+1 or -1) of the current summand

    while (current_idx < expr.length()) {
        long long coeff = 1; // Default coefficient is 1 if omitted
        
        // Parse coefficient if present (e.g., "5*", "123*")
        if (std::isdigit(expr[current_idx])) {
            coeff = 0;
            while (current_idx < expr.length() && std::isdigit(expr[current_idx])) {
                coeff = coeff * 10 + (expr[current_idx] - '0');
                current_idx++;
            }
            // After a coefficient, there must be a '*' according to the grammar
            current_idx++; // Skip '*'
        }

        // Calculate the (sign * coefficient) for the current summand
        long long s_times_C = current_global_sign * coeff;
        s_times_C_values.push_back(s_times_C);

        // Determine the increment type (a++ or ++a)
        if (expr[current_idx] == 'a') { // It's "a++"
            // For "a++", the value taken is `current_a`. The contribution to the variable
            // part is `s*C * k_j`, where `k_j` is increments before this term.
            current_idx += 3; // Skip "a++"
        } else { // It's "++a"
            // For "++a", the value taken is `current_a + 1`. The contribution to the variable
            // part is `s*C * (k_j + 1)`. The `+1` part contributes `s*C` to fixed_offset_sum.
            fixed_offset_sum += s_times_C;
            current_idx += 3; // Skip "++a"
        }

        // Check for the next operator (+ or -) to determine the sign for the next summand
        if (current_idx < expr.length()) {
            if (expr[current_idx] == '+') {
                current_global_sign = 1;
                current_idx++;
            } else if (expr[current_idx] == '-') {
                current_global_sign = -1;
                current_idx++;
            }
            // If current_idx points to anything else, it means the expression has ended.
            // Problem guarantees valid input.
        }
    }

    // --- Calculation of Total Maximum Sum ---
    // The total sum can be decomposed into three parts:
    // 1. base_sum: (initial_a * Sum(s*C for all terms)). This part is constant.
    // 2. fixed_offset_sum: Sum(s*C for all ++a terms). This part is constant.
    // 3. variable_offset_sum: Sum(s*C * k_j) where k_j is the count of increments
    //    that occurred before this term. k_j takes values 0, 1, ..., N-1 in some order.
    //    This part needs to be maximized by choosing the optimal processing order.

    // 1. Calculate base_sum
    long long sum_of_s_times_C_overall = 0;
    for (long long val : s_times_C_values) {
        sum_of_s_times_C_overall += val;
    }
    long long base_sum = initial_a * sum_of_s_times_C_overall;

    // 2. fixed_offset_sum is already calculated during parsing.

    // 3. Calculate variable_offset_sum
    // To maximize Sum(A_i * B_i) where A_i are (s*C) values and B_i are k_j values (0 to N-1),
    // we sort both sets in the same order (e.g., ascending) and multiply corresponding elements.
    std::sort(s_times_C_values.begin(), s_times_C_values.end());

    long long variable_offset_sum = 0;
    for (int i = 0; i < s_times_C_values.size(); ++i) {
        variable_offset_sum += s_times_C_values[i] * i;
    }

    // The total maximum sum is the sum of these three parts.
    long long total_max_sum = base_sum + fixed_offset_sum + variable_offset_sum;

    std::cout << total_max_sum << std::endl;

    return 0;
}