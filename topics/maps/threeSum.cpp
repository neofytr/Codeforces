#include <bits/stdc++.h>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t fixed_random = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + fixed_random);
    }
};

int main() {
    int n;
    cin >> n;
    long long x;
    cin >> x;

    vector<long long> arr(n + 1); // 1-based indexing
    unordered_map<long long, int, custom_hash> elementToIndex;

    for (int index = 1; index <= n; index++) {
        cin >> arr[index];
        elementToIndex[arr[index]] = index;
    }

    for (int index = 1; index <= n; index++) {
        for (int counter = index + 1; counter <= n; counter++) {
            long long target = x - arr[index] - arr[counter];
            if (elementToIndex.count(target) && elementToIndex[target] != index && elementToIndex[target] != counter) {
                cout << index << " " << counter << " " << elementToIndex[target] << endl;
                return EXIT_SUCCESS;
            }
        }
    }

    cout << "IMPOSSIBLE\n";
    return EXIT_SUCCESS;
}
