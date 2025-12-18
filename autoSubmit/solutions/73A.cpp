#include <bits/stdc++.h>

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long x, y, z, k;
    std::cin >> x >> y >> z >> k;

    // Store dimensions in a vector and sort them to process in increasing order.
    // This helps in the greedy strategy to balance piece counts.
    std::vector<long long> dims = {x, y, z};
    std::sort(dims.begin(), dims.end());

    // current_pieces[i] stores (cuts_made_for_dim_i + 1). Initially 1 piece per dimension (0 cuts).
    std::vector<long long> current_pieces = {1, 1, 1};

    // Phase 1: Try to maximize cuts for the smallest dimension (dims[0])
    // We can increase current_pieces[0] up to dims[0].
    // cuts_needed = (dims[0] - current_pieces[0]) is the number of cuts to reach dims[0] pieces.
    long long cuts_to_apply = std::min(k, dims[0] - current_pieces[0]);
    current_pieces[0] += cuts_to_apply;
    k -= cuts_to_apply;
    if (k == 0) {
        std::cout << current_pieces[0] * current_pieces[1] * current_pieces[2] << std::endl;
        return 0;
    }

    // Phase 2: Try to bring current_pieces[1] up to current_pieces[0] (but not exceeding dims[1])
    // current_pieces[0] is now the highest among the current piece counts.
    // We want to make current_pieces[1] as close to current_pieces[0] as possible,
    // without exceeding its maximum original dimension dims[1].
    long long target_for_dim1 = std::min(current_pieces[0], dims[1]);
    cuts_to_apply = std::min(k, target_for_dim1 - current_pieces[1]);
    current_pieces[1] += cuts_to_apply;
    k -= cuts_to_apply;
    if (k == 0) {
        std::cout << current_pieces[0] * current_pieces[1] * current_pieces[2] << std::endl;
        return 0;
    }
    
    // Phase 3: Try to bring current_pieces[2] up to current_pieces[1] (but not exceeding dims[2])
    // Similar to Phase 2, but for the third dimension.
    long long target_for_dim2 = std::min(current_pieces[1], dims[2]);
    cuts_to_apply = std::min(k, target_for_dim2 - current_pieces[2]);
    current_pieces[2] += cuts_to_apply;
    k -= cuts_to_apply;
    if (k == 0) {
        std::cout << current_pieces[0] * current_pieces[1] * current_pieces[2] << std::endl;
        return 0;
    }

    // Phase 4: Distribute remaining cuts as evenly as possible among all available dimensions.
    // At this point, it's guaranteed that current_pieces[0] >= current_pieces[1] >= current_pieces[2].
    // Each current_pieces[i] is also less than or equal to its corresponding dims[i].
    // We distribute remaining 'k' cuts by applying (k / num_available_dims) to each,
    // and then (k % num_available_dims) as one extra cut to available dimensions.
    // This loop runs efficiently because each iteration either reduces 'k' or saturates one or more dimensions.
    while (k > 0) {
        long long num_available_dims = 0;
        for (int i = 0; i < 3; ++i) {
            if (current_pieces[i] < dims[i]) {
                num_available_dims++;
            }
        }

        if (num_available_dims == 0) {
            break; // All dimensions are at their maximum possible pieces. No more cuts can be made.
        }

        long long cuts_per_dim_base = k / num_available_dims;
        long long remainder_cuts = k % num_available_dims;

        // If no base cuts and no remainder cuts, we are done.
        // This condition is mostly a safeguard, as k > 0 implies something to distribute.
        if (cuts_per_dim_base == 0 && remainder_cuts == 0) {
            break; 
        }

        // Apply base cuts to all available dimensions
        for (int i = 0; i < 3; ++i) {
            if (current_pieces[i] < dims[i]) {
                long long actual_add = std::min(cuts_per_dim_base, dims[i] - current_pieces[i]);
                current_pieces[i] += actual_add;
                k -= actual_add;
            }
        }

        // Apply remainder cuts one by one to the available dimensions
        for (int i = 0; i < 3; ++i) {
            if (remainder_cuts > 0 && current_pieces[i] < dims[i]) {
                current_pieces[i]++;
                remainder_cuts--;
                k--;
            }
        }
        
        // Loop terminates when k becomes 0, or when no dimensions are available for cuts.
        if (k <= 0) {
            break;
        }
    }

    // The final product of pieces
    std::cout << current_pieces[0] * current_pieces[1] * current_pieces[2] << std::endl;

    return 0;
}