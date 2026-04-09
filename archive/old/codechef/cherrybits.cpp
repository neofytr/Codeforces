// https://www.codechef.com/CENS2020/problems/CENS20A

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m;

    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m)); // n rows, m columns

    for (vector<int> &row : matrix)
    {
        for (int &elt : row)
        {
            cin >> elt;
        }
    }

    int q;
    cin >> q;

    vector<vector<int>> prefix(n + 1, vector<int>(m, 0));

    int x_one, x_two, y_one, y_two;

    // compute the prefix array
    while (q--)
    {
        cin >> x_one >> x_two >> y_one >> y_two;

        // convert to zero based indexing
        x_one--, x_two--, y_one--, y_two--;
        for (int y = y_one; y <= y_two; y++)
        {
            prefix[y][x_one] = (prefix[y][x_one] + 1) & 1;
            prefix[y][x_two + 1] = prefix[y][x_one];
        }
    }

    // propagate
    for (int y = 0; y < )
}

int main()
{

    solve();

    return 0;
}