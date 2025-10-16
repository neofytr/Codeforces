#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int p;
    cin >> p;

    for (int r = 1; r < p; r++) {
        int num = p - r;
        vector<int> facts;

        for (int a = 1; a * a <= num; a++) {
            if (!(num % a)) {
                facts.push_back(a);
                if (a != num / a)
                    facts.push_back(num / a);
            }
            if (facts.size() >= 3) break;
        }

        if (facts.size() >= 3) {
            sort(facts.begin(), facts.end());
            cout << facts[1] << " " << facts[2] << endl;
            return;
        }
    }

}

int32_t main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
