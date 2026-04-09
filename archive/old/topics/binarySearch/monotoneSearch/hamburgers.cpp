#include <bits/stdc++.h>
using namespace std;

string recipie;
int bread, sausage, cheese;
int price_bread, price_sausage, price_cheese;
long long r;
long long need_b = 0, need_s = 0, need_c = 0;

bool func(long long x) {
    long long total_b = need_b * x;
    long long total_s = need_s * x;
    long long total_c = need_c * x;

    long long buy_b = max(0LL, total_b - bread);
    long long buy_s = max(0LL, total_s - sausage);
    long long buy_c = max(0LL, total_c - cheese);

    long long cost = buy_b * price_bread + buy_s * price_sausage + buy_c * price_cheese;

    return cost <= r;
}

int main() {
    cin >> recipie;
    for (char ch: recipie) {
        if (ch == 'B') need_b++;
        if (ch == 'S') need_s++;
        if (ch == 'C') need_c++;
    }

    cin >> bread >> sausage >> cheese;
    cin >> price_bread >> price_sausage >> price_cheese;
    cin >> r;

    long long left = 0, right = 1e13; // 1e13 is enough
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (func(mid)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << right << endl;
    return 0;
}
