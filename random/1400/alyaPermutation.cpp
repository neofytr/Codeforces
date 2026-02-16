#include <bits/stdc++.h>
using namespace std;

bool isPowerOfTwo(int n) {
    return (n & (n - 1)) == 0;
}

int main() {
	int t; cin >> t;
	while (t--) {

    int n;
    cin >> n;

    vector<int> perm;
    vector<bool> used(n + 1, false);

    if (n % 2 == 1) {
        int l = n & -n;

        int a = l;
        int b = l + (l == 1 ? 2 : 1);
        int c = n - l;
        int d = n;

        vector<int> tail = {a, b, c, d};
        for (int x : tail) used[x] = true;

        for (int i = 1; i <= n; i++)
            if (!used[i]) perm.push_back(i);

        for (int x : tail) perm.push_back(x);
    }
    else {
        if (!isPowerOfTwo(n)) {
            int h = 1 << (31 - __builtin_clz(n));

            vector<int> tail = {n, n - 1, h - 1};
            for (int x : tail) used[x] = true;

            for (int i = 1; i <= n; i++)
                if (!used[i]) perm.push_back(i);

            for (int x : tail) perm.push_back(x);
        }
        else {
            vector<int> tail = {1, 3, n - 2, n - 1, n};
            for (int x : tail) used[x] = true;

            for (int i = 1; i <= n; i++)
                if (!used[i]) perm.push_back(i);

            for (int x : tail) perm.push_back(x);
        }
    }

    int res = 0;
    for (int r = 0; r < n; r++)
    	if ((r + 1) & 1) res &= perm[r];
    	else res |= perm[r];
    cout << res << endl;
    for (int x : perm)
        cout << x << " ";
    cout << "\n";
}

    return 0;
}
