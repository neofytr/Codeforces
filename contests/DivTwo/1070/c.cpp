#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x.size())

void run_tc() {
    int n_n; 
    cin >> n_n;
    vector<int> vvv(n_n);
    vector<int> ooo, eee;
    for(int i=0; i<n_n; ++i) {
        cin >> vvv[i];
        if(vvv[i] % 2 != 0) ooo.pb(vvv[i]);
        else eee.pb(vvv[i]);
    }

    sort(all(ooo), greater<int>());
    sort(all(eee), greater<int>());

    int c_o = sz(ooo);
    int c_e = sz(eee);

    vector<int> p_e(c_e + 1, 0);
    for(int i=0; i<c_e; ++i) p_e[i+1] = p_e[i] + eee[i];

    for(int kkk=1; kkk<=n_n; ++kkk) {
        if(c_o == 0) {
            cout << 0 << " ";
            continue;
        }

        int mx_waste_e = c_e;
        int mx_waste_o = (c_o - 1) / 2 * 2;
        int gl_limit = 1 + mx_waste_e + mx_waste_o;

        if(kkk > gl_limit) {
            cout << 0 << " ";
            continue;
        }

        int target_e = kkk - 1;
        
        if(target_e <= c_e) {
            int cur = ooo[0] + p_e[target_e];
            cout << cur << " ";
        } else {
            int rem = target_e - c_e;
            if(rem % 2 == 0) {
                int cur = ooo[0] + p_e[c_e];
                cout << cur << " ";
            } else {
                if(c_e > 0) {
                    int cur = ooo[0] + p_e[c_e - 1];
                    cout << cur << " ";
                } else {
                    cout << 0 << " ";
                }
            }
        }
    }
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ttt; cin >> ttt;
    while(ttt--) {
        run_tc();
    }
    return 0;
}