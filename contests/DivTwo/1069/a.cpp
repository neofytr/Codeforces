#include <bits/stdc++.h>
using namespace std;

#define int long long

void run_case() {
    int owo;
    cin >> owo;
    vector<int> baka(owo);
    set<int> distinct_stuff;
    
    for(int i = 0; i < owo; ++i) {
        cin >> baka[i];
        distinct_stuff.insert(baka[i]);
    }

    int current_cnt = distinct_stuff.size();
    int final_res = -1;

    for(int k = current_cnt; k <= 2005; ++k) {
        if(distinct_stuff.count(k)) {
            final_res = k;
            goto done;
        }
    }

done:
    if(final_res != -1) {
        cout << final_res << "\n";
    } else {
        int big_chungus = 1000000000000000000;
        int diff = big_chungus - 1 - owo;
        cout << current_cnt + diff << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int ttt;
    cin >> ttt;
    while(ttt--) {
        run_case();
    }
    return 0;
}