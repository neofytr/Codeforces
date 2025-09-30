#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: commonDivisors
// URL: https://vjudge.net/problem/CodeForces-1203C
// Difficulty: easy
// Tags: 
// Strategy: 

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#define MAX (1000000)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    int mini = LLONG_MAX;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val, mini = min(val, mini);


    unordered_map<int, int> primes;
    for (int r = 2; r * r <= mini; r++)
        while(!(mini % r))
            primes[r]++, mini /= r;
    if (mini > 1) primes[mini]++;

    for (int val : arr)
        for (auto &[p, cnt] : primes) {
            int ncnt = 0;
            while (!(val % p))
                ncnt++, val /= p;
            cnt = min(cnt, ncnt);
        }

    int res = 1;
    for (auto &[p, cnt] : primes)
        res *= (cnt + 1);
    cout << res << endl;
    return 0;
}