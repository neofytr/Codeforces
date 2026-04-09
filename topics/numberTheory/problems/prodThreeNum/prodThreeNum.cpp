#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: prodThreeNum
// URL: https://codeforces.com/problemset/problem/1294/C
// Difficulty: medium
// Tags: 
// Strategy: 

vector<int> solve(int n) {
    for (int a = 2; a * a <= n; a++) 
            if (!(n % a)) {
                int div = n / a;
                for (int b = 2; b * b <= div; b++)
                    if (!(div % b)) {
                        int c = div / b;
                        if (a != b && b != c && c != a)
                            return {a, b, c};
                    }
            }
    return {-1};
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        vector<int> ans = solve(n);
        if (ans[0] == -1)
            cout << "No\n";
        else {
            cout << "Yes\n";
            for (int num : ans)
                cout << num << " ";
            cout << "\n";
        }
    }    
    return 0;
}