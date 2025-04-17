#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, r, c;
    cin >> n >> r >> c;
    string str;
    cin >> str;

    set<pair<int, int>> smokes;
    smokes.insert({0, 0});

    for (int i = 0; i < n; ++i)
    {
        set<pair<int, int>> new_smokes;

        for (auto &[x, y] : smokes)
        {
            switch (str[i])
            {
            case 'N':
                new_smokes.insert({x - 1, y});
                break;
            case 'S':
                new_smokes.insert({x + 1, y});
                break;
            case 'W':
                new_smokes.insert({x, y - 1});
                break;
            case 'E':
                new_smokes.insert({x, y + 1});
                break;
            }
        }

        if (!new_smokes.count({0, 0}))
            new_smokes.insert({0, 0});

        smokes = move(new_smokes);

        if (smokes.count({r, c}))
            cout << 1;
        else
            cout << 0;
    }
    cout << '\n';
    return 0;
}
