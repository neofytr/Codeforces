#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    deque<int> first;
    deque<int> second;

    int k;
    cin >> k;
    for (int index = 0; index < k; index++) {
        cin >> first[index];
    }

    cin >> k;
    for (int index = 0; index < k; index++) {
        cin >> second[index];
    }

    long long count = 0;

    while (true) {
        int first_front = first.front();
        int second_front = second.front();
        count++;
        if (first_front > second_front) {
            first.push_front(second_front);
            second.pop_front();

            if (second.empty()) {
                cout << count << " 1";
                return EXIT_SUCCESS;
            }
        } else {
            second.push_front(first_front);
            first.pop_front();

            if (first.empty()) {
                cout << count << " 2";
                return EXIT_SUCCESS;
            }
        }
    }
}
