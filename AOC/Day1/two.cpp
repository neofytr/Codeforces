#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD 100

int32_t main() {
    int val = 50;
    string str;
    int cnt = 0;

    while (cin >> str) {
        int delta = stoi(str.substr(1));

        if (str[0] == 'L') {
            if (!val) {
                val = (MOD - (delta % MOD)) % MOD;
                if (delta >= MOD) cnt += delta / MOD;
            } else if (delta < val) {
                val = (val - delta + MOD) % MOD;
            } else {
                delta -= val;       
                cnt++;             

                cnt += delta / MOD; 

                val = (MOD - (delta % MOD)) % MOD;  
            }
        }

        else { /
            int r = MOD - val;
            if (!val) {
                val = delta % MOD;
                cnt += delta / MOD;   
            } else if (delta < r) {
                val = (val + delta) % MOD;
            } else {
                delta -= r;
                cnt++;              

                cnt += delta / MOD;  
                val = delta % MOD
            }
        }
    }

    cout << cnt << endl;
    return 0;
}
