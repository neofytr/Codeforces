// https://codeforces.com/problemset/problem/1924/A
#include <bits/stdc++.h>
using namespace std;

#define ALPHABET 26

// checks if substr is a subsequence of str using the precomputed jump table
bool check(vector<char> &str, vector<char> &substr, vector<vector<int>> &table)
{
    // start from the beginning of str
    int next = 0;

    // go through each character in the substr
    for (char c : substr)
    {
        // if we've gone past the end of str, it's not a subsequence
        if (next >= m)
        {
            return false;
        }

        // jump to the next occurrence of c in str at or after index 'next'
        next = table[c][next];

        // move to the next character position in str
        next++;
    }

    // all characters in substr were found in order in str
    return true;
}

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