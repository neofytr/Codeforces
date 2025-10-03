#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: commonDiv
// URL: https://cses.fi/problemset/task/1081
// Difficulty: hard
// Tags: 
// Strategy: 

#include <bits/stdc++.h>
using namespace std;

#define MAX (1000000)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    int val;
    vector<int> freq(MAX + 1, 0);
    for (int r = 1; r <= n; r++) {
        cin >> val;
        freq[val]++;
    }

    // divisor -> count
    int maxi; 
    for (int r = MAX; r >= 1; r--) {
        int cnt = 0;
        for (int j = r; j <= MAX; j += r) 
            cnt += freq[j];
        if (cnt >= 2) {
            cout << r << endl;
            return 0;
        }
    }
            
    cout << maxi << endl;
    return 0;
}