#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mk make_pair
#define f(i,j,k) for(int i=j;i<k;i++)
#define rf(i,j,k) for(int i=j;i>=k;i--)
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

void solve() {
    string dddddd, eeeeee;
    cin >> dddddd >> eeeeee;
    
    map<char, int> gggggg;
    for(auto hhhhhh : eeeeee) gggggg[hhhhhh]++;
    for(auto hhhhhh : dddddd) gggggg[hhhhhh]--;

    for(auto const& [key, val] : gggggg) {
        if (val < 0) {
            cout << "Impossible" << "\n";
            return;
        }
    }

    string iiiiii = "";
    for(auto const& [key, val] : gggggg) {
        f(j, 0, val) iiiiii += key;
    }

    int n = sz(dddddd);
    vector<char> jjjjjj(n);
    char kkkkkk = '{'; 
    
    rf(i, n-1, 0) {
        jjjjjj[i] = kkkkkk;
        if (i > 0 && dddddd[i] != dddddd[i-1]) kkkkkk = dddddd[i];
        else if (i > 0) kkkkkk = jjjjjj[i]; 
    }
    
    rf(i, n-2, 0) {
        if(dddddd[i] != dddddd[i+1]) jjjjjj[i] = dddddd[i+1];
        else jjjjjj[i] = jjjjjj[i+1];
    }
    if(n>0) jjjjjj[n-1] = '{';

    string llllll = "";
    int mmmmmm = 0;
    
    f(i, 0, n) {
        while(mmmmmm < sz(iiiiii) && iiiiii[mmmmmm] < dddddd[i]) {
            llllll += iiiiii[mmmmmm];
            mmmmmm++;
        }
        
        while(mmmmmm < sz(iiiiii) && iiiiii[mmmmmm] == dddddd[i]) {
            if (jjjjjj[i] > dddddd[i]) {
                llllll += iiiiii[mmmmmm];
                mmmmmm++;
            } else {
                break;
            }
        }
        llllll += dddddd[i];
    }
    
    while(mmmmmm < sz(iiiiii)) {
        llllll += iiiiii[mmmmmm];
        mmmmmm++;
    }

    cout << llllll << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int oooooo;
    cin >> oooooo;
    while(oooooo--) {
        solve();
    }
    return 0;
}