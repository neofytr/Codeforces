#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> p(n + 1), a(n + 1), b(n + 1);
    int p_max = 0;
    int a_max = 0;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i] >> a[i] >> b[i];
        p_max = max(p_max, p[i]);
        a_max = max(a_max, a[i]);
    }

    int k_bound = p_max + a_max;

    vector<long long> csb(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        csb[i] = csb[i - 1] + b[i];
    }

    vector<vector<long long>> final_mood(n + 2, vector<long long>(k_bound + 1));
    for (int m = 0; m <= k_bound; ++m) {
        final_mood[n + 1][m] = m;
    }

    for (int i = n; i >= 1; --i) {
        for (int m = 0; m <= k_bound; ++m) {
            long long next_mood;
            if (p[i] >= m) {
                next_mood = m + a[i];
            } else {
                next_mood = m - b[i];
                if (next_mood < 0) {
                    next_mood = 0;
                }
            }
            final_mood[i][m] = final_mood[i + 1][next_mood];
        }
    }

    int q;
    cin >> q;
    while (q--) {
        long long x;
        cin >> x;

        if (x <= k_bound) {
            cout << final_mood[1][x] << "\n";
        } else {

            long long target_k_csb = x - k_bound;
            auto it_k = lower_bound(csb.begin(), csb.end(), target_k_csb);
            int k_minus_1_idx = distance(csb.begin(), it_k);
            int k = k_minus_1_idx + 1;

            auto it_z = upper_bound(csb.begin(), csb.end(), x);
            int z = distance(csb.begin(), it_z);

            bool hits_k_bound = (it_k != csb.end());
            bool hits_zero = (it_z != csb.end());

            if (hits_zero && (!hits_k_bound || z < k)) {
                cout << final_mood[z + 1][0] << "\n";
            } else {
                if (!hits_k_bound) {
                    cout << x - csb[n] << "\n";
                } else {
                    long long mood_at_k = x - csb[k_minus_1_idx];
                    cout << final_mood[k][mood_at_k] << "\n";
                }
            }
        }
    }

    return 0;
}