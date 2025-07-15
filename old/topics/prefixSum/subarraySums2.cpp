#include <bits/stdc++.h>
using namespace std;

struct CustomHash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long n, x;
    cin >> n >> x;

    unordered_map<long long, long long, CustomHash> map;
    map[0] = 1;
    long long count = 0;
    long long val;
    long long sum = 0;

    for (int index = 1; index <= n; index++)
    {
        cin >> val;
        sum += val;
        count += map[sum - x];
        map[sum]++;
    }

    cout << count << '\n';
}
