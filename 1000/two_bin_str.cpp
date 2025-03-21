#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string a, b;
    cin >> a >> b;

    int len = a.length(); // len >= 2 (given)

    int max_common_zero = 0;
    for (int index = 1; index < len; index++)
    {
        if (a[index] == '0' && b[index] == '0')
        {
            max_common_zero = index;
        }
    }

    int min_common_one = len - 1;
    for (int index = len - 2; index >= 0; index--)
    {
        if (a[index] == '1' && b[index] == '1')
        {
            min_common_one = index;
        }
    }

    if ((min_common_one - max_common_zero >= 2))
    {
        cout << "no" << endl;
    }
    else
    {
        cout << "yes" << endl;
    }
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