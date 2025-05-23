// https://codeforces.com/problemset/problem/1924/A
#include <bits/stdc++.h>
using namespace std;

#define ALPHABET 26

// checks if substr is a subsequence of str using the precomputed jump table
bool check(int len, vector<char> &str, vector<char> &substr, vector<vector<int>> &table)
{
    // start from the beginning of str
    int next = 0;

    // go through each character in the substr
    for (int index = 0; index < len; index++)
    {
        // if we've gone past the end of str, it's not a subsequence
        if (next >= str.size())
        {
            return false;
        }

        // jump to the next occurrence of c in str at or after index 'next'
        next = table[substr[index]][next];

        // if character not found, return false
        if (next >= str.size())
        {
            return false;
        }

        // move to the next character position in str
        next++;
    }

    // all characters in substr were found in order in str
    return true;
}

bool backtrack(int pos, int n, int k, vector<char> &current, vector<char> &str, vector<vector<int>> &table)
{
    if (pos >= n)
    {
        return true;
    }

    for (int index = 0; index < k; index++)
    {
        current[pos] = index;
        if (!check(pos + 1, str, current, table))
        {
            cout << "NO\n";
            for (int i = 0; i <= pos; i++)
            {
                cout << (char)(current[i] + 'a'); // Convert back to character
            }
            cout << endl;
            return false;
        }

        if (!backtrack(pos + 1, n, k, current, str, table))
        {
            return false;
        }
    }

    return true;
}

void solve()
{
    int n, k, m;
    cin >> n >> k >> m;

    string input;
    cin >> input;

    vector<char> str(m);
    for (int i = 0; i < m; i++)
    {
        str[i] = input[i] - 'a';
    }

    // create a jump table to efficiently check whether a string x is a subsequence
    // of str
    vector<vector<int>> table(ALPHABET, vector<int>(m));
    // table[c][r] gives the next index of character c in str on and after r; 0 <= r < m; 0 <= c < 26

    for (int c = 0; c < ALPHABET; ++c)
    {
        int next = m; // start with m, meaning "not found"
        for (int i = m - 1; i >= 0; --i)
        {
            if (str[i] == c)
                next = i;
            table[c][i] = next;
        }
    }

    vector<char> current(n);
    if (backtrack(0, n, k, current, str, table))
    {
        cout << "YES\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}