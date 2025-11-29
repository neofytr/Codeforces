#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define int long long
#define pb push_back
#define mkp make_pair
#define all(x) x.begin(), x.end()
#define f first
#define s second
#define sz(x) (int)(x.size())

const int INF_THINGY = 1e18;
int n_val, k_turns;
vector<int> arr_a_soup;
vector<int> arr_b_soup;
int gimme_max_sub(const vector<int>& vvv) {
    int cur_cur = -INF_THINGY;
    int max_max = -INF_THINGY;
    for (auto val : vvv) {
        if (cur_cur < 0) cur_cur = val;
        else cur_cur += val;
        max_max = max(max_max, cur_cur);
    }
    return max_max;
}

int divide_and_conquer_madness(int l_idx, int r_idx) {
    if (l_idx == r_idx) {
        return arr_a_soup[l_idx] + arr_b_soup[l_idx];
    }

    int mid_mid = (l_idx + r_idx) >> 1;
    
    int l_res = divide_and_conquer_madness(l_idx, mid_mid);
    int r_res = divide_and_conquer_madness(mid_mid + 1, r_idx);
    int best_of_sides = max(l_res, r_res);

    vector<pair<int, int>> l_vec_stuff;
    int run_sum = 0; 
    int run_mx_b = -1;
    
    for (int i = mid_mid; i >= l_idx; --i) {
        run_sum += arr_a_soup[i];
        run_mx_b = max(run_mx_b, arr_b_soup[i]);
        l_vec_stuff.pb({run_sum, run_mx_b});
    }

    vector<pair<int, int>> r_vec_stuff;
    run_sum = 0; 
    run_mx_b = -1;
    
    for (int i = mid_mid + 1; i <= r_idx; ++i) {
        run_sum += arr_a_soup[i];
        run_mx_b = max(run_mx_b, arr_b_soup[i]);
        r_vec_stuff.pb({run_sum, run_mx_b});
    }

    int l_sz = sz(l_vec_stuff);
    vector<int> suff_max_weird(l_sz + 1, -INF_THINGY);
    
    for(int i = l_sz - 1; i >= 0; --i) {
        suff_max_weird[i] = max(suff_max_weird[i+1], l_vec_stuff[i].f + l_vec_stuff[i].s);
    }

    int ptr_ptr = 0;
    int cur_l_max_sum_only = -INF_THINGY;
    int cross_res = -INF_THINGY;

    
    for (auto& r_item : r_vec_stuff) {
        int r_sum = r_item.f;
        int r_mx = r_item.s;

        while(ptr_ptr < l_sz && l_vec_stuff[ptr_ptr].s <= r_mx) {
            cur_l_max_sum_only = max(cur_l_max_sum_only, l_vec_stuff[ptr_ptr].f);
            ptr_ptr++;
        }

        if (cur_l_max_sum_only != -INF_THINGY) {
            cross_res = max(cross_res, cur_l_max_sum_only + r_sum + r_mx);
        }

        if (ptr_ptr < l_sz) {
            int best_remain = suff_max_weird[ptr_ptr];
            if (best_remain != -INF_THINGY) {
                cross_res = max(cross_res, best_remain + r_sum);
            }
        }
    }

    return max(best_of_sides, cross_res);
}

void do_the_thing() {
    cin >> n_val >> k_turns;
    arr_a_soup.resize(n_val);
    arr_b_soup.resize(n_val);
    
    for(int& x : arr_a_soup) cin >> x;
    for(int& x : arr_b_soup) cin >> x;

    
    if (k_turns % 2 == 0) {
        cout << gimme_max_sub(arr_a_soup) << "\n";
    } else {
        cout << divide_and_conquer_madness(0, n_val - 1) << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    int t_cases; 
    cin >> t_cases;
    while(t_cases--) {
        do_the_thing();
    }
    return 0;
}