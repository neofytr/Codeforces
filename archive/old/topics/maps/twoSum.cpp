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
    long long n, x;
    cin >> n >> x;

    vector<long long> arr(n + 1); // for 1-based indexing
    unordered_map<long long, long long, custom_hash> list;
    for (long long index = 1; index <= n; index++) {
        cin >> arr[index];
        if (list.count(x - arr[index])) {
            // exists
            cout << list[x - arr[index]] << " " << index << endl;
            return EXIT_SUCCESS;
        }
        list[arr[index]] = index;
    }

    for (long long index = 1; index <= n; index++) {
        if (list.count(x - arr[index]) && list[x - arr[index]] != index) {
            // exists
            cout << list[x - arr[index]] << " " << index << endl;
            return EXIT_SUCCESS;
        }
    }

    cout << "IMPOSSIBLE\n";
    return EXIT_SUCCESS;
}
