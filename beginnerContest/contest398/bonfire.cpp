#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, r, c;
    cin >> n >> r >> c;
    string str;
    cin >> str;

    vector<vector<int>> grid(2 * n + 1, vector<int>(2 * n + 1));
#define GRID(i, j) grid[i + n][j + n]

    vector<pair<int, int>> smokes;
    smokes.push_back(pair(0, 0)); // initially only one smoke

    for (int index = 1; index <= n; index++)
    {
        switch (str[index - 1])
        {
        case 'N':
        {
            for (auto &smoke : smokes)
            {
                smoke.first--;
            }
            break;
        }
        case 'W':
        {
            for (auto &smoke : smokes)
            {
                smoke.second--;
            }
            break;
        }
        case 'S':
        {
            for (auto &smoke : smokes)
            {
                smoke.first++;
            }
            break;
        }
        case 'E':
        {
            for (auto &smoke : smokes)
            {
                smoke.second++;
            }
            break;
        }
        }

        bool found = false;
        for (auto &smoke : smokes)
        {
            if (smoke.first == 0 && smoke.second == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            smokes.push_back(pair(0, 0));
        }

        found = false;

        for (auto &smoke : smokes)
        {
            if (smoke.first == r && smoke.second == c)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            cout << 1;
        }
        else
        {
            cout << 0;
        }
    }

    cout << endl;
    return EXIT_SUCCESS;
}