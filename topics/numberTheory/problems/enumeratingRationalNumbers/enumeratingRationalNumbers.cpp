#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXI (10000000)

// Problem: enumeratingRationalNumbers
// URL: https://onlinejudge.org/index.php?option=com_onlinejudge
// Difficulty: medium
// Tags: 
// Strategy: 

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> phi(MAXI + 1);
    for (int r = 1; r <= MAXI; r++)
        phi[r] = r;

    for (int r = 2; r <= MAXI; r++)
        if (phi[r] == r)
            for (int j = r; j <= MAXI; j += r)
                phi[j] -= phi[j] / r;
    
    int x;
    while(cin >> x, x) {
        if (x == 1) {
            cout << "0/1" << endl;
            continue;
        }
        if (x == 2) {
            cout << "1/1" << endl;
            continue;
        }

        int num = 2;
        x -= 2;
        while(x - phi[num] > 0) {
            x -= phi[num];
            num++;
        }

        int cnt = 0;
        for (int k = 1; k < num; k++)
            if (gcd(k, num) == 1) {
                cnt++;
                if (cnt == x) {
                    cout << k << "/" << num << endl;
                    break;
                }
            }
    }    
    return 0;
}