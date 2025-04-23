#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    deque<long long> dq;
    long long max_elem = -1;
    int max_index = -1;

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        dq.push_back(x);
        if (x > max_elem) {
            max_elem = x;
            max_index = i;
        }
    }

    vector<pair<long long, long long> > operations;
    while (dq.front() != max_elem) {
        long long a = dq.front();
        dq.pop_front();
        long long b = dq.front();
        dq.pop_front();
        operations.push_back({a, b});

        if (a > b) {
            dq.push_front(a);
            dq.push_back(b);
        } else {
            dq.push_front(b);
            dq.push_back(a);
        }
    }
}
