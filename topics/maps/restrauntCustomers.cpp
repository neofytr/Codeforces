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

    long long a, b;
    map<long long, long long> timeToPersonChange;
    while (n--) {
        cin >> a >> b;
        timeToPersonChange[a] += 1;
        timeToPersonChange[b] -= 1;
    }

    long long count = 0;
    long long max = -1;

    for (auto change: timeToPersonChange) {
        count += change.second;
        if (count > max) {
            max = count;
        }
    }

    cout << max << endl;
    return EXIT_SUCCESS;
}
