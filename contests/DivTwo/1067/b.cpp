#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#define all(x) x.begin(), x.end()

void solve_da_problem() {
    int nnn_val;
    cin >> nnn_val;
    
    int limit_thingy = 2 * nnn_val;
    
    map<int, int> stuff_storage;
    
    for(int i = 0; i < limit_thingy; i++) {
        int temp_trash;
        cin >> temp_trash;
        stuff_storage[temp_trash]++;
    }

    int odd_freak_cnt = 0;
    int even_freak_cnt = 0;

    for(auto const& [key_val, count_val] : stuff_storage) {
        if(count_val % 2 != 0) {
            odd_freak_cnt++;
        } else {
            even_freak_cnt++;
        }
    }

    int aaahebbds = odd_freak_cnt + 2 * even_freak_cnt;

    if(odd_freak_cnt == 0) {
        int p1 = even_freak_cnt % 2;
        int p2 = nnn_val % 2;
        
        if(p1 != p2) {
            aaahebbds -= 2;
        }
    }

    cout << aaahebbds << "\n";
}

signed main() {
    fastio;
    int t_cases;
    cin >> t_cases;
    while(t_cases--) {
        solve_da_problem();
    }
    return 0;
}