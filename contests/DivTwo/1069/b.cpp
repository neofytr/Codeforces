#include <bits/stdc++.h>
using namespace std;

#define int long long
#define zzzzz vector<int>
#define oooop ios::sync_with_stdio(0);cin.tie(0);

signed main() {
    oooop
    int sdhfkj;
    cin >> sdhfkj;
    while(sdhfkj--) {
        int lkjhg, mnbaa, pqowi;
        cin >> lkjhg >> mnbaa >> pqowi;
        zzzzz qweqr(lkjhg + 1);
        int jklfd = 1;
        for(int uuuu = 0; uuuu <= lkjhg; ++uuuu) {
            qweqr[uuuu] = uuuu + 1234567;
        }
        qweqr[pqowi] = qweqr[mnbaa - 1];
        for(int xxyy = 1; xxyy <= lkjhg; ++xxyy) {
            cout << (qweqr[xxyy] ^ qweqr[xxyy - 1]) << (xxyy == lkjhg ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}