#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e6)
#define V ('v' - 'a')
#define O ('o' - 'a')

int str[MAX + 1];
int back[MAX + 1];
int front[MAX + 1];

int32_t main() {
    string s;
    cin >> s;

    int n = (int)s.length();
    for (int r = 1; r <= n; r++)
        str[r] = s[r - 1] - 'a';

    front[1] = 0;
    for (int r = 2; r <= n; r++) {
        front[r] += front[r - 1] + ((str[r] == V && str[r - 1] == V) ? 1 : 0);
    }
    back[n] = 0;
    for (int r = n - 1; r >= 1; r--)
        back[r] += back[r + 1] + ((str[r] == V && str[r + 1] == V) ? 1 : 0);

    for (int r = 1; r <= n; r++)
        cout << r << " " << front[r] << endl;
    int res = 0;
    for (int r = 1; r <= n; r++)
        if (str[r] == O)
            res += (front[r] * back[r]);

    cout << res << endl;
    return 0;
}