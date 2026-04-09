#include <algorithm>
#include <iostream>
using ll = long long;

ll min_R, max_R, min_C, max_C;

bool check(ll t) {
    bool possible_in_R = (max_R - min_R <= 2 * t);

    bool possible_in_C = (max_C - min_C <= 2 * t);

    return possible_in_R && possible_in_C;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        ll r, c;
        std::cin >> r >> c;
        if (i == 0) {
            min_R = max_R = r;
            min_C = max_C = c;
        } else {
            min_R = std::min(min_R, r);
            max_R = std::max(max_R, r);
            min_C = std::min(min_C, c);
            max_C = std::max(max_C, c);
        }
    }

    ll low = 0;
    ll high = 2e9;
    ll ans = high;

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}