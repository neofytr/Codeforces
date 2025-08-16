#include <algorithm>
#include <iostream>
#include <vector>

void solve() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int q;

    std::cin >> q;

    std::vector<int> bag;

    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int x;
            std::cin >> x;
            bag.push_back(x);
        } else if (type == 2) {
            auto min_it = std::min_element(bag.begin(), bag.end());

            std::cout << *min_it << "\n";

            bag.erase(min_it);
        }
    }
}

int main() {
    solve();
    return 0;
}