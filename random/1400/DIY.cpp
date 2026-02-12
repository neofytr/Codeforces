#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n; 
    if (!(cin >> n)) return;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());    
    vector<int> pairs;
    for(int i = 0; i < n - 1; i++) {
        if(a[i] == a[i+1]) {
            pairs.push_back(a[i]);
            i++;
        }
    }

    if(pairs.size() < 4) {
        cout << "NO" << endl;
        return;
    }

    int k = pairs.size();
    vector<int> p = {pairs[0], pairs[1], pairs[k-2], pairs[k-1]};
    
    int max_area = -1;
    int x1, x2, y1, y2;

    int area1 = (p[1] - p[0]) * (p[3] - p[2]);
    if (area1 > max_area) {
        max_area = area1;
        x1 = p[0]; x2 = p[1]; y1 = p[2]; y2 = p[3];
    }

    int area2 = (p[2] - p[0]) * (p[3] - p[1]);
    if (area2 > max_area) {
        max_area = area2;
        x1 = p[0]; x2 = p[2]; y1 = p[1]; y2 = p[3];
    }

    int area3 = (p[3] - p[0]) * (p[2] - p[1]);
    if (area3 > max_area) {
        max_area = area3;
        x1 = p[0]; x2 = p[3]; y1 = p[1]; y2 = p[2];
    }

    cout << "YES" << endl;
    cout << x1 << " " << y1 << " " << x1 << " " << y2 << " " 
         << x2 << " " << y1 << " " << x2 << " " << y2 << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; 
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}