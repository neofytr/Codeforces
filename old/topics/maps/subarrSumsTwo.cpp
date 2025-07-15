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
    long long x;
    cin >> n >> x;

    long long sum = 0;
    long long val;
    unordered_map<long long, long long, custom_hash> canMakeSum;
    long long count = 0;
    long long temp;
    canMakeSum[0] = 1; // we can already make 0 sum by choosing nothing as the prefix array
    for (int index = 1; index <= n; index++) {
        cin >> val;
        sum += val;
        // find if we can make the sum 'sum' - target for any prefix array before this point
        // if we can, we can make the sum target by removing this prefix array from the current one
        temp = sum - x;
        if (canMakeSum.count(temp)) {
            count += canMakeSum[sum - x];
        }

        canMakeSum[sum]++; // we can now make this sum with a prefix array
    }

    cout << count << endl;
}
