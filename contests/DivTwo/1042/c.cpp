#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

void solve_it() {
    int n_portals;
    std::cin >> n_portals;

    std::map<int, std::vector<int>> groups;

    for (int i = 1; i <= n_portals; ++i) {
        std::cout << "? " << i << " " << n_portals;
        for (int j = 1; j <= n_portals; ++j) {
            std::cout << " " << j;
        }
        std::cout << std::endl;
        int len;
        std::cin >> len;
        if (len == -1)
            return;
        groups[len].push_back(i);
    }

    int max_l = 0;
    if (!groups.empty()) {
        max_l = groups.rbegin()->first;
    }

    std::vector<int> result_path;
    int last_v = groups[max_l][0];
    result_path.push_back(last_v);

    for (int target_len = max_l - 1; target_len >= 1; --target_len) {
        std::vector<int> &potential_next = groups[target_len];

        int l = 0;
        int r = potential_next.size() - 1;
        int next_v = -1;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            int set_size = mid + 2;
            std::cout << "? " << last_v << " " << set_size;
            std::cout << " " << last_v;
            for (int i = 0; i <= mid; ++i) {
                std::cout << " " << potential_next[i];
            }
            std::cout << std::endl;

            int res;
            std::cin >> res;
            if (res == -1)
                return;

            if (res > 1) {
                next_v = potential_next[mid];
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        last_v = next_v;
        result_path.push_back(last_v);
    }

    std::cout << "! " << result_path.size();
    for (int node : result_path) {
        std::cout << " " << node;
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve_it();
    }
    return 0;
}