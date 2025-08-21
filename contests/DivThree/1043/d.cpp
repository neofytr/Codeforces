#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using ll = long long;
using namespace std;

ll p10[17];
ll sum_up_to_10_pow[17];

ll sum_digits_up_to(ll n) {
    if (n < 0)
        return 0;
    if (n < 10) {
        return n * (n + 1) / 2;
    }

    string s = to_string(n);
    int d = s.length();

    ll p = p10[d - 1];
    ll msd = n / p;
    ll rem = n % p;

    ll ans = 0;

    ans += sum_up_to_10_pow[d - 1];
    ans += (msd * (msd - 1) / 2) * p;
    ans += msd * (rem + 1);

    ans += (msd - 1) * sum_up_to_10_pow[d - 1];
    ans += sum_digits_up_to(rem);

    return ans;
}

void precompute() {
    p10[0] = 1;
    for (int i = 1; i <= 16; ++i) {
        p10[i] = p10[i - 1] * 10;
    }

    sum_up_to_10_pow[0] = 0;
    for (int i = 1; i <= 16; ++i) {
        sum_up_to_10_pow[i] = i * 45 * p10[i - 1];
    }
}

void solve_test_case() {
    ll k;
    cin >> k;

    ll total_sum = 0;
    ll d = 1;
    ll power_of_10 = 1;

    while (true) {
        ll count_of_numbers = 9 * power_of_10;
        ll digits_in_block = d * count_of_numbers;

        if (k > digits_in_block) {
            total_sum += sum_up_to_10_pow[d] - sum_up_to_10_pow[d - 1];
            k -= digits_in_block;
            d++;
            power_of_10 *= 10;
        } else {
            ll start_num = power_of_10;

            ll num_full_integers = k / d;
            if (num_full_integers > 0) {
                ll end_num = start_num + num_full_integers - 1;
                total_sum += sum_digits_up_to(end_num) - sum_digits_up_to(start_num - 1);
            }

            ll remaining_digits = k % d;
            if (remaining_digits > 0) {
                ll next_num = start_num + num_full_integers;
                string s = to_string(next_num);
                for (int i = 0; i < remaining_digits; ++i) {
                    total_sum += s[i] - '0';
                }
            }
            break;
        }
    }
    cout << total_sum << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int t;
    cin >> t;
    while (t--) {
        solve_test_case();
    }

    return 0;
}