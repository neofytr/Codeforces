#include <bits/stdc++.h>
using namespace std;

bool canCopy(const long long time, const long long n, const long long x, const long long y) {
    long long first_copy_time = min(x, y);
    if (time < first_copy_time) return false;
    long long remaining_time = time - first_copy_time;
    long long copies = 1 + (remaining_time / x) + (remaining_time / y);
    return copies >= n;
}

int main() {
    long long n, x, y;
    cin >> n >> x >> y;

    // if they can copy in t time, they can copy in t+1 too
    // in zero seconds, they can't copy anything
    long long left = 0;
    // in n * max(x, y) seconds, they can copy everything
    long long right = n * max(x, y);

    while (right != left + 1) {
        long long mid = left + (right - left) / 2;
        if (canCopy(mid, n, x, y)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << right << endl;
}
