#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

void solve()
{
    string str;
    cin >> str;

    long long n = str.length();

    long long cost = 0, index = 0, substr_len = 0;
    while (index < n)
    {
        if (str[index] == '1')
        {
            substr_len++;
        }
        else if (str[index] == '0' && substr_len)
        {
            long long count = 0;
            while (index < n)
            {
                if (str[index] == '0')
                {
                    count++;
                }
                else
                {
                    break;
                }

                index++;
            }

            cost += (substr_len + 1) * count;
            continue;
        }

        index++;
    }

    cout << cost << endl;
}

int main()
{
    FAST_IO;
    long long t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
