#include <bits/stdc++.h>
using namespace std;

#define int long long

// problem: subarraydiv
// url: https://cses.fi/problemset/task/1662
// difficulty: hard
// tags:
// strategy:

#include <bits/stdc++.h>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are to count the number of subarrays where the sum of values is divisible by n
    // a subarray [l, r] is good iff the sum of it values is divisible by n
    // a subarray [l, r] is good iff rem(prefix[r + 1] - prefix[l], n) = 0
    //                           iff rem(prefix[r + 1], n) - rem(prefix[l], n) = 0
    //                           iff rem(prefix[r + 1], n) = prefix(l, n)

    vector<int> prefix(n + 1, 0);
    for (int index = 1; index <= n; index++)
        prefix[index] = ((prefix[index - 1] + arr[index - 1]) % n + n) % n;

    unordered_map<int, int, custom_hash> freq; // freq[r] is the number of subarrays until the current iteration which have the remainder r from n
    freq[0] = 1;
    int count = 0;
    for (int index = 0; index < n; index++) {
        int rem = prefix[index + 1];
        count += freq[rem];
        freq[rem]++;
    }
    cout << count << endl;
    return 0;
}