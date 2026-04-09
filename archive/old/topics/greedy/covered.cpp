// https://codeforces.com/problemset/problem/1924/A

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k, m;
    cin >> n >> k >> m;

    vector<char> str(m);
    char temp;
    for (char &val : str)
    {
        cin >> temp;
        val = temp - 'a';
    }

    // if all possible strings of length n, using the first k small letters
    // of the alphabet are the subsequences of the string str, print yes

    // if there is some string of length n, constructed using the first k small
    // letters of the alphabet that is not a subsequence of the string str, print no
    // and that string too

    // all possible strings of length n, using the first k small letters of the
    // alphabet are subsequences of the string str if and only if
    // there are atleast n sets containing at least one of each of the first k characters of the alphabet in str, one after the other

    // in general consider a sequence x of some symbols from universe S
    // consider a subset s of S
    // we want to check if all the sequences that can be made from s of at most length k are subsequences of x
    // this is possible if and only if
    // there are atleast k sets containing at least one of each of the symbols in s, in the sequence x, one after the other

    int sets = 0;
    int count = 0;
    vector<bool> found(k, false);

    string res = "";
    for (char c : str)
    {
        if (sets >= n)
        {
            break;
        }

        if (c < k)
        {
            if (!found[c])
            {
                count++;
            }
            found[c] = true;
        }

        if (count == k)
        {
            fill(found.begin(), found.end(), false);
            sets++;
            count = 0;
            res += 'a' + c;
        }
    }

    if (sets >= n)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
        for (int ch = 0; ch < k; ch++)
        {
            if (!found[ch])
            {
                while (res.size() < n)
                {
                    res += 'a' + ch;
                }
            }
        }
        cout << res << "\n";
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