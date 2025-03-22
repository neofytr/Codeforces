#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string a, b;
    cin >> a >> b;

    int len = a.length(); // len >= 2 (given)

    vector<pair<int, int>> eq; // number, index

    for (int index = 0; index < len; index++)
    {
        if (a[index] == b[index])
        {
            if (a[index] == '0')
            {
                eq.push_back(pair(0, index));
            }
            else
            {
                eq.push_back(pair(1, index));
            }
        }
    }

    auto curr = pair(0, 0);
    int eq_len = eq.size();

    for (int index = 0; index < eq_len; index++)
    {
        auto temp = eq[index];
        if (temp.first == curr.first)
        {
            for (int counter = curr.second; counter <= temp.second; counter++)
            {
                a[counter] = temp.first ? '1' : '0';
                b[counter] = temp.first ? '1' : '0';
            }
        }

        curr = temp;
    }

    for (int index = 0; index < len; index++)
    {
        if (a[index] != b[index])
        {
            cout << "no\n";
            return;
        }
    }

    cout << "yes\n";
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