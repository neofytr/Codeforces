// https://www.codechef.com/problems/SHAIKHGN

#include <bits/stdc++.h>
using namespace std;

#define MAX 500

int main()
{
    int n;
    cin >> n;

    bitset<MAX + 1> got_message;

    vector<vector<int>> gnome(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> gnome[i][j];
        }
    }

    int m;
    cin >> m;

    while (m--)
    {
    }
}