#include <bits/stdc++.h>
using namespace std;

#define int long long

int pw(int base, int exp, int mod) {
    int res = 1;
    base = base % mod;
    while(exp) {
        if (exp & 1)
            res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x, y, n;
    while(cin >> x >> y >> n) 
        cout << pw(x, y, n) << endl;
    return 0;
}