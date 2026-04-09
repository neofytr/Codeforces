#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> camels(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> camels[i].first >> camels[i].second;
    }

    bool found_pair = false;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // A camel cannot spit at itself
            if (i == j) {
                continue;
            }

            int xA = camels[i].first;
            int dA = camels[i].second;
            int xB = camels[j].first;
            int dB = camels[j].second;

            // Check if camel A (at xA) spits and hits camel B (at xB)
            // AND if camel B (at xB) spits and hits camel A (at xA)
            if ((xA + dA == xB) && (xB + dB == xA)) {
                found_pair = true;
                break; // Found a pair, no need to check further
            }
        }
        if (found_pair) {
            break; // Found a pair, no need to check further in outer loop
        }
    }

    if (found_pair) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    solve();

    return 0;
}