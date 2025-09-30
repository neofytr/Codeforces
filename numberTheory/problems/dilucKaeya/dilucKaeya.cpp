#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: dilucKaeya
// URL: https://codeforces.com/contest/1536/problem/C
// Difficulty: hard
// Tags: 
// Strategy: 

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        string str;
        cin >> str;

        int numK = 0, numD = 0;
        map<pair<int, int>, int> freq;

        for(int i = 0; i < n; i++) {
            if(str[i] == 'K') numK++;
            else numD++;

            int g = gcd(numK, numD);
            pair<int, int> ratio = {numD/g, numK/g};
            freq[ratio]++;
            cout << freq[ratio] << " ";
        }
        cout << endl;
    }
    return 0;
}