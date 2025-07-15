#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_map<int, int> map; // number to index
    int element;
    for (int index = 0; index < n; index++) {
        cin >> element;
        map[element] = index + 1; // 1-based indexing
    }

    int curr = 0;
    int rounds = 0;
    while (curr < n) {
        rounds++;
        curr++; // take the next element whose index was behind (start the next round from here)
        while (map[curr + 1] > map[curr]) {
            curr++;
        }
    }

    cout << rounds << endl;
}
