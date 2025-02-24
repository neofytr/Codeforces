#include <bits/stdc++.h>
using namespace std;

int factorial(int x)
{
    return (x <= 1) ? 1 : x * factorial(x - 1);
}

int count_permutations(string s)
{
    int freq[26] = {0};
    for (char c : s)
        freq[c - 'a']++;

    int n = s.size();
    int denom = 1;
    for (int f : freq)
        denom *= factorial(f);

    return factorial(n) / denom;
}

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    string best_s = s;
    int min_perms = count_permutations(s);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            string temp = s;
            temp[i] = temp[j];
            int perms = count_permutations(temp);
            if (perms < min_perms)
            {
                min_perms = perms;
                best_s = temp;
            }
        }
    }

    cout << best_s << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
