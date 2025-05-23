// https://codeforces.com/problemset/problem/1924/A
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k, m;
    cin >> n >> k >> m;

    if (n > m)
    {
        cout << "NO\n";
        cout << string(n, "a") << "\n";
    }

    vector<char> first;
    unordered_map<char, int> freq;
    first.reserve(m);

    vector<char> str(m);
    char num;
    for (char &val : str)
    {
        cin >> val;
        char num = val - 'a'; // 0 to 25
        if (num < k)
        {
            freq[num]++;
            first.push_back(num);
        }
    }

    if (freq.size() < k)
    {
        for (int num = 0; num < 26; num++)
        {
            if (!freq[num])
            {
                cout << "NO\n";
                cout << num + 'a' << "\n";
                return EXIT_SUCCESS;
            }
        }
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
}