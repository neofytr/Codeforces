#include <iostream>

using namespace std;
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T, n, i, t, flag;
    for (cin >> T; T > 0; T--)
    {
        cin >> n;
        flag = 0;
        for (i = 0; i < n; i++)
        {
            cin >> t;
            if (t <= i * 2 || t <= (n - i - 1) * 2)
                flag = 1;
        }
        if (flag)
            cout << "NO\n";
        else
            cout << "YES\n";
    }
    return 0;
}