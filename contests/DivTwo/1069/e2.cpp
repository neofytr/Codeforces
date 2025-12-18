#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast_n_furious ios_base::sync_with_stdio(false); cin.tie(NULL);

int power_puff(int base, int exp, int mod) {
    int res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int modular_inverse(int n, int mod) {
    return power_puff(n, mod - 2, mod);
}

void chaos_emerald() {
    int n_pebbles, m_colors, mod_master;
    cin >> n_pebbles >> m_colors >> mod_master;

    int prob_fail = modular_inverse(m_colors, mod_master);
    
    int total_expect_sum = 0;
    int total_var_sum = 0;

    int inv_one_minus_p = 0;
    int inv_sq_one_minus_p = 0;
    
    if (m_colors != 1) {
        int denom = (1 - prob_fail + mod_master) % mod_master;
        inv_one_minus_p = modular_inverse(denom, mod_master);
        inv_sq_one_minus_p = (inv_one_minus_p * inv_one_minus_p) % mod_master;
    }

    int bounds = 2 * n_pebbles - 2;

    for (int k = 0; k <= bounds; ++k) {
        int max_rad = 0;
        bool is_gap = (k % 2 != 0);
        int idx = k / 2;

        if (!is_gap) {
            max_rad = min(idx, n_pebbles - 1 - idx);
        } else {
            max_rad = min(idx + 1, n_pebbles - 1 - idx);
        }

        int s1 = 0;
        int s2 = 0;

        if (max_rad > 0) {
            if (m_colors == 1) {
                s1 = max_rad % mod_master;
                int term = (max_rad * (max_rad + 1)) % mod_master;
                s2 = (max_rad * max_rad) % mod_master;
            } else {
                int p_pow_L = power_puff(prob_fail, max_rad, mod_master);
                
                int num_geo = (1 - p_pow_L + mod_master) % mod_master;
                s1 = (prob_fail * num_geo) % mod_master;
                s1 = (s1 * inv_one_minus_p) % mod_master;

                int termA = (max_rad + 1) % mod_master;
                termA = (termA * p_pow_L) % mod_master;
                
                int next_pow = (p_pow_L * prob_fail) % mod_master;
                int termB = (max_rad * next_pow) % mod_master;
                
                int num_arith = (1 - termA + termB + mod_master) % mod_master; // Add mod_master before mod
                num_arith = (num_arith + mod_master) % mod_master;
                
                int sum_k_pk = (prob_fail * num_arith) % mod_master;
                sum_k_pk = (sum_k_pk * inv_sq_one_minus_p) % mod_master;

                s2 = (2 * sum_k_pk) % mod_master;
                s2 = (s2 - s1 + mod_master) % mod_master;
            }
        }

        int expect_curr = 0;
        int sq_expect_curr = 0;

        if (!is_gap) {
            expect_curr = (1 + s1) % mod_master;
            sq_expect_curr = (1 + 2 * s1) % mod_master;
            sq_expect_curr = (sq_expect_curr + s2) % mod_master;
        } else {
            expect_curr = s1;
            sq_expect_curr = s2;
        }

        total_expect_sum = (total_expect_sum + expect_curr) % mod_master;
        
        int term_sq = (expect_curr * expect_curr) % mod_master;
        int variance = (sq_expect_curr - term_sq + mod_master) % mod_master;
        
        total_var_sum = (total_var_sum + variance) % mod_master;
    }

    int grand_sq = (total_expect_sum * total_expect_sum) % mod_master;
    int final_ans = (grand_sq + total_var_sum) % mod_master;

    cout << final_ans << "\n";
}

signed main() {
    fast_n_furious;
    int t_bone;
    cin >> t_bone;
    while (t_bone--) {
        chaos_emerald();
    }
    return 0;
}