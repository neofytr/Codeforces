#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    deque<int> list;

    int num;
    while (n--) {
        cin >> num;
        if (list.empty()) {
            list.push_back(num);
        } else {
            if (num < list.front()) {
                list.push_front(num);
            } else {
                list.push_back(num);
            }
        }
    }

    for (int val: list) {
        cout << val << " ";
    }

    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return EXIT_SUCCESS;
}
