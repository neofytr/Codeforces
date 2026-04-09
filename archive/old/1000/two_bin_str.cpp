#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string a, b;
    cin >> a >> b;

    int len = a.length(); // len >= 2 (given)

    for (int index = 0; index < len; index++)
    {
        if (index < len - 1 && a[index] == b[index])
        {
            if (a[index] == '0')
            {
                if (a[index + 1] == b[index + 1] && a[index + 1] == '1')
                {
                    cout << "yes\n";
                    return;
                }
            }
        }
    }

    cout << "no\n";
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return EXIT_SUCCESS;
}