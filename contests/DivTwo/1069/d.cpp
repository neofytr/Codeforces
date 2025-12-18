#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fastio ios::sync_with_stdio(0);cin.tie(0);
#define vvv vector
#define ppp pair<int, int>
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(), x.end()

ppp ddd[365][365];
vvv<int> ppppos[365];

void run_tc() {
    int nn, kk;
    cin >> nn >> kk;

    for(int i=0; i<=kk; ++i) ppppos[i].clear();

    for(int i=1; i<=nn; ++i) {
        int val;
        cin >> val;
        for(int j=0; j<=val; ++j) {
            ppppos[j].pb(i);
        }
    }

    for(int i=0; i<=kk; ++i) 
        for(int j=0; j<=kk; ++j) 
            ddd[i][j] = {-1, 1e18};

    ddd[0][0] = {0, 0};
    int ans = 0;

    for(int i=1; i<=kk; ++i) {
        for(int j=0; j<i; ++j) {
            for(int c=0; c<=kk-i; ++c) {
                if(ddd[j][c].ff == -1) continue;

                int p_idx = ddd[j][c].ss;
                
                auto it = upper_bound(all(ppppos[i]), p_idx);
                
                if(it != ppppos[i].end()) {
                    int idx = *it;
                    int gain = (i - j) * (nn - idx + 1);
                    int n_hap = ddd[j][c].ff + gain;
                    int n_cost = c + i;

                    if(n_hap > ddd[i][n_cost].ff) {
                        ddd[i][n_cost] = {n_hap, idx};
                    } else if(n_hap == ddd[i][n_cost].ff) {
                        if(idx < ddd[i][n_cost].ss) ddd[i][n_cost].ss = idx;
                    }
                }
            }
        }
    }

    for(int i=1; i<=kk; ++i)
        for(int j=0; j<=kk; ++j)
            ans = max(ans, ddd[i][j].ff);
            
    cout << ans << "\n";
}

signed main() {
    fastio
    int t;
    cin >> t;
    while(t--) run_tc();
    return 0;
}