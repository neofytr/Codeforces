#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void solve() {
    long long n, c;
    cin >> n >> c;

    vector<long long> arr(n);
    for (long long &val : arr)
        cin >> val;

    long long cost = 0;

    while (true) {
        vector<long long> valid;
        for (auto val : arr) {
            if (val != -1)
                valid.push_back(val);
        }

        if (valid.empty())
            break;

        sort(valid.begin(), valid.end());

        auto itr = upper_bound(valid.begin(), valid.end(), c);

        if (itr == valid.begin()) {
            cost += valid.size();
            break;
        } else {
            long long target = *(--itr);

            for (int i = 0; i < n; ++i) {
                if (arr[i] == target) {
                    arr[i] = -1;
                    break;
                }
            }

            for (int i = 0; i < n; ++i) {
                if (arr[i] != -1)
                    arr[i] *= 2;
            }
        }
    }

    cout << cost << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
