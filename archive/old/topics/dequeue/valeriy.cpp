#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    deque<long long> dq;
    long long max_elem = -1;
    int max_index = -1;

    long long element;
    for (int index = 0; index < n; index++) {
        cin >> element;
        dq.push_back(element);
        if (element > max_elem) {
            max_elem = element;
            max_index = index;
        }
    }

    // the maximum element will come in the front after exactly max_index operations
    // after that, the 2nd element repeats in a cycle of n - 1

    vector<pair<long long, long long> > operations(max_index + 1); // for 1-based indexing
    for (int index = 0; index < max_index; index++) {
        operations[index + 1] = make_pair(dq[0], dq[1]);
        const long long first = dq.front();
        dq.pop_front();
        const long long second = dq.front();
        dq.pop_front();

        if (first > second) {
            dq.push_front(first);
            dq.push_back(second);
        } else {
            dq.push_front(second);
            dq.push_back(first);
        }
    }

    // if operations are in the range 1 <= op <= max_index, we return operations[op]
    // after that the second element goes into a cycle of n - 1

    uint64_t m;
    while (q--) {
        cin >> m;

        if (m <= max_index) {
            cout << operations[m].first << " " << operations[m].second << endl;
        } else {
            uint64_t op = m - max_index; // operation number into the cycle part
            uint64_t act = op % (n - 1);
            uint64_t index_in_deque;
            if (!act) {
                index_in_deque = n - 1;
            } else {
                index_in_deque = act;
            }

            cout << max_elem << " " << dq[index_in_deque] << endl;
        }
    }

    return EXIT_SUCCESS;
}
