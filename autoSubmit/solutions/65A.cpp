#include <bits/stdc++.h>

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long a, b, c, d, e, f;
    std::cin >> a >> b >> c >> d >> e >> f;

    bool is_ron = false;

    // Rule 1: If no gold can ever be produced (d=0), then Hermione.
    if (d == 0) {
        is_ron = false; // Cannot produce any gold
    } else { // d > 0, so gold can potentially be produced.

        // Rule 2: Gold from nothing (0 lead -> d gold)
        // If c is 0, we can produce d grams of gold from 0 grams of lead.
        // Since d > 0, this means infinite gold.
        if (c == 0) {
            is_ron = true;
        }

        // Rule 3: Lead from nothing (0 sand -> b lead), then convert to gold
        // If a is 0 and b > 0, we can produce b grams of lead from 0 grams of sand.
        // This gives infinite lead. Since d > 0, we can convert this infinite lead to infinite gold.
        // This condition is checked only if Rule 2 (c == 0) did not already make it Ron.
        if (!is_ron && a == 0 && b > 0) {
            is_ron = true;
        }
        
        // Rule 4: Sand from nothing (0 gold -> f sand), then convert to lead, then to gold
        // If e is 0 and f > 0, we can produce f grams of sand from 0 grams of gold.
        // This gives infinite sand.
        // From infinite sand, we need to be able to make lead (requires b > 0).
        // From infinite lead, we need to be able to make gold (requires d > 0, which is covered by the outer 'else' block).
        // This condition is checked only if Rule 2 or 3 did not already make it Ron.
        if (!is_ron && e == 0 && f > 0 && b > 0) {
            is_ron = true;
        }

        // Rule 5: Cycle provides a net gain (Sand -> Lead -> Gold -> Sand)
        // This applies only if all conversion steps require input and produce output,
        // and if none of the "from nothing" conditions (Rules 2, 3, 4) are met.
        // At this point, if `is_ron` is still false, it implies:
        //   a > 0 (otherwise Rule 3 would apply)
        //   c > 0 (otherwise Rule 2 would apply)
        //   e > 0 (otherwise Rule 4 would apply)
        //   b > 0 (otherwise `b*d*f` would be 0, leading to Hermione, or Rule 3 would not apply)
        //   f > 0 (otherwise `b*d*f` would be 0, leading to Hermione, or Rule 4 would not apply)
        //   d > 0 (already handled by the outer 'else' block)
        if (!is_ron && a > 0 && b > 0 && c > 0 && e > 0 && f > 0) {
            // The condition for infinite gain through a cycle is (b/a) * (d/c) * (f/e) > 1.
            // To avoid floating-point issues and work with integers, we can rewrite this as:
            // b * d * f > a * c * e
            // We use long long for the product to prevent overflow, as max values for a,b,c,d,e,f are 1000,
            // so their product can be up to 1000^3 = 10^9, which fits in long long.
            if (b * d * f > a * c * e) {
                is_ron = true;
            }
        }
    }

    if (is_ron) {
        std::cout << "Ron\n";
    } else {
        std::cout << "Hermione\n";
    }

    return 0;
}