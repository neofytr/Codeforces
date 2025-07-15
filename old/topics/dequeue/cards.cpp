#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int k1;
    cin >> k1;
    deque<int> first;
    for (int i = 0; i < k1; i++) {
        int card;
        cin >> card;
        first.push_back(card);
    }

    int k2;
    cin >> k2;
    deque<int> second;
    for (int i = 0; i < k2; i++) {
        int card;
        cin >> card;
        second.push_back(card);
    }

    set<pair<deque<int>, deque<int>>> seen;
    int turns = 0;

    while (!first.empty() && !second.empty()) {
        if (seen.count({first, second})) {
            cout << -1 << endl;
            return 0;
        }

        seen.insert({first, second});

        int f_card = first.front();
        int s_card = second.front();
        first.pop_front();
        second.pop_front();

        turns++;

        if (f_card > s_card) {
            first.push_back(s_card);
            first.push_back(f_card);
        } else {
            second.push_back(f_card);
            second.push_back(s_card);
        }
    }

    if (first.empty()) {
        cout << turns << " 2" << endl;
    } else {
        cout << turns << " 1" << endl;
    }

    return 0;
}
