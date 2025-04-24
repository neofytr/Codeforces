#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    multiset<long long> arr;
    long long element;

    long long towers = 0;

    while (n--) {
        cin >> element;
        if (arr.empty()) {
            towers++;
            arr.insert(element);
        } else {
            auto itr = arr.upper_bound(element);
            if (itr == arr.end()) {
                towers++;
                // we need a new tower, all the elements that are currently on top are less than the current element
                arr.insert(element);
            } else {
                // there is an element which is just greater than element
                // place this cube on top of that
                arr.erase(itr);
                arr.insert(element);
            }
        }
    }

    cout << towers << endl;
    return EXIT_SUCCESS;
}
