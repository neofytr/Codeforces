#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, a, b;
    string str;
    cin >> n >> a >> b >> str;

    if (b >= 0)
    {
        cout << a * n + b * n << endl;
        return;
    }

    int zero_segments = 0, one_segments = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0 || str[i] != str[i - 1])
        {
            if (str[i] == '0')
                zero_segments++;
            else
                one_segments++;
        }
    }

    int min_segments = min(zero_segments, one_segments);
    int ans = a * n + b * (min_segments + 1);
    cout << ans << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
