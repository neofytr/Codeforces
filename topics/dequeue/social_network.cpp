#include <bits/stdc++.h>
using namespace std;

// read this article on custom hashing
// https://codeforces.com/blog/entry/62393
struct CustomHash {
    size_t operator()(long long x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        x += FIXED_RANDOM;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    deque<long long> screen;
    unordered_set<long long, CustomHash> on_screen;

    for (long long i = 0; i < n; ++i) {
        long long id;
        cin >> id;

        if (on_screen.count(id)) continue;

        if ((long long) screen.size() == k) {
            on_screen.erase(screen.back());
            screen.pop_back();
        }

        screen.push_front(id);
        on_screen.insert(id);
    }

    cout << screen.size() << '\n';
    for (long long id: screen)
        cout << id << ' ';
    cout << '\n';

    return 0;
}
