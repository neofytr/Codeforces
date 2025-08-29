#include <bits/stdc++.h>
using namespace std;

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long inv(long long n, long long m) {
    return power(n, m - 2, m);
}

void go() {
    int sz;
    long long kk;
    cin >> sz >> kk;
    vector<long long> arr(sz);
    for (int i = 0; i < sz; i++)
        cin >> arr[i];

    long long modpick = 0;
    vector<int> check = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
    for (int v : check) {
        if (kk % v) {
            modpick = v;
            break;
        }
    }

    long long invk = inv(kk, modpick);

    for (int i = 0; i < sz; i++) {
        long long r = arr[i] % modpick;
        long long need = (modpick - r) % modpick;
        long long c = (need * invk) % modpick;
        long long out = arr[i] + c * kk;
        cout << out << (i + 1 == sz ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
        go();
}
