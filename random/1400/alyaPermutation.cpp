#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n % 2 != 0) {
        cout << n << endl;
        vector<int> p;
        for (int i = 1; i <= n; ++i) {
            if (i != 1 && i != 3 && i != n - 1 && i != n) {
                p.push_back(i);
            }
        }
        p.push_back(1);
        p.push_back(3);
        p.push_back(n - 1);
        p.push_back(n);

        for (int i = 0; i < n; ++i) cout << p[i] << (i == n - 1 ? "" : " ");
        cout << endl;

    } else {
        bool powerOfTwo = (n & (n - 1)) == 0;
        
        int msb = 0;
        while ((1 << (msb + 1)) <= n) {
            msb++;
        }
        int M = (1 << (msb + 1)) - 1;

        if (powerOfTwo) {
            cout << M - 1 << endl;
            vector<int> p;
            for (int i = 1; i <= n; ++i) {
                if (i != n - 2 && i != n - 1 && i != n) {
                    p.push_back(i);
                }
            }
            p.push_back(n - 2);
            p.push_back(n - 1);
            p.push_back(n);
            
            for (int i = 0; i < n; ++i) cout << p[i] << (i == n - 1 ? "" : " ");
            cout << endl;
        } else {
            cout << M << endl;
            
            int X = M ^ n; 
            int LB = n & -n; 
            int Y = X | LB;
            
            vector<int> p;
            for (int i = 1; i <= n; ++i) {
                if (i != X && i != Y && i != n) {
                    p.push_back(i);
                }
            }
            p.push_back(X);
            p.push_back(Y);
            p.push_back(n);

            for (int i = 0; i < n; ++i) cout << p[i] << (i == n - 1 ? "" : " ");
            cout << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}