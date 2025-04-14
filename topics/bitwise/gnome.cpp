// https://www.codechef.com/problems/SHAIKHGN

#include <bits/stdc++.h>
using namespace std;

#define MAX 500

void send_message(bitset<MAX + 1> &got_message, vector<vector<int>> &gnome, int x)
{
    for (int index = 0; index < gnome[0].size(); index++)
    {
        if (gnome[x][index])
        {
            got_message[index] = true;
        }
    }
}

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

    int k, x;

    while (m--)
    {
        cin >> k >> x;
        for (int minute = 1; minute <= k; minute++)
        {
        }
    }
}