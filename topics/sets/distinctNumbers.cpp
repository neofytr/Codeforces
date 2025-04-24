#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<long long> arr;

    long long element;
    while (n--) {
        cin >> element;
        arr.insert(element);
    }

    cout << arr.size() << endl;
    return EXIT_SUCCESS;
}
