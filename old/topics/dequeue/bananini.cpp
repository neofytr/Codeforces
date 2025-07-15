#include <bits/stdc++.h>
using namespace std;

void solve() {
    int q;
    cin >> q;

    deque<int> arr;
    long long curr_rizziness = 0;
    long long element_sum = 0;
    bool reversed = false;

    while (q--) {
        int s;
        cin >> s;

        if (s == 1) {
            if (!arr.empty()) {
                if (!reversed) {
                    int last = arr.back();
                    arr.pop_back();
                    arr.push_front(last);
                    curr_rizziness = curr_rizziness + element_sum - 1LL * last * arr.size();
                } else {
                    int first = arr.front();
                    arr.pop_front();
                    arr.push_back(first);
                    curr_rizziness = curr_rizziness + element_sum - 1LL * first * arr.size();
                }
            }
            cout << curr_rizziness << '\n';
        } else if (s == 2) {
            reversed = !reversed;
            curr_rizziness = element_sum * (arr.size() + 1) - curr_rizziness;
            cout << curr_rizziness << '\n';
        } else if (s == 3) {
            int k;
            cin >> k;
            if (!reversed) {
                arr.push_back(k);
            } else {
                arr.push_front(k);
            }
            element_sum += k;
            curr_rizziness += 1LL * k * arr.size();
            cout << curr_rizziness << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
