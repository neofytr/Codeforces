#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    multiset<long long> arr;

    long long element;
    while (n--) {
        cin >> element;
        arr.insert(element);
    }

    long long willing;
    for (int index = 0; index < m; index++) {
        cin >> willing; // the max price the customer is willing to pay

        if (arr.empty()) {
            cout << -1 << "\n";
            continue;
        }

        // the customer is willing to pay at max the least ticket price

        auto itr = arr.upper_bound(willing);
        // this will give the iterator to the first element greater than willing
        // decrementing it, we will either get equal to willing or first less than it
        // this is what we want

        if (itr == arr.begin()) {
            // no suitable ticket
            cout << -1 << "\n";
        } else {
            cout << *(--itr) << endl;
            arr.erase(itr);
        }
    }
    return EXIT_SUCCESS;
}
