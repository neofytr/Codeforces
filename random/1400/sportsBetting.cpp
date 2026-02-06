#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    for (int i = 0; i + 3 < n; ++i) {
        if (a[i] == a[i+3]) {
            cout << "Yes" << "\n";
            return;
        }
    }

 
    
    vector<pair<int, int>> counts;
    if (n > 0) {
        int current_val = a[0];
        int current_count = 1;
        for (int i = 1; i < n; ++i) {
            if (a[i] == current_val) {
                current_count++;
            } else {
                counts.push_back({current_val, current_count});
                current_val = a[i];
                current_count = 1;
            }
        }
        counts.push_back({current_val, current_count});
    }

    bool active_chain = false;
    
    for (size_t i = 0; i < counts.size(); ++i) {
        int day = counts[i].first;
        int count = counts[i].second;
        
        if (i > 0 && day != counts[i-1].first + 1) {
            active_chain = false;
        }

        if (count >= 2) {
            if (active_chain) {
                cout << "Yes" << "\n";
                return;
            }
            active_chain = true;
        } else {
           
        }
    }

    cout << "No" << "\n";
}

int main() {
    // Optimize I/O operations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}