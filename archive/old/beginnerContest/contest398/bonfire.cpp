#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, r, c;
    cin >> n >> r >> c;
    string str;
    cin >> str;

    // change the perspective to moving all the smoke points to shifting the origin and
    // takahasi itself

    pair<int, int> origin(0, 0);
    pair<int, int> takahashi(r, c);
    set<pair<int, int>> smoke;
    smoke.insert(origin);

    for (int index = 0; index < n; index++)
    {
        if (str[index] == 'N')
        {
            origin.first++;
            takahashi.first++;
        }
        else if (str[index] == 'W')
        {
            origin.second++;
            takahashi.second++;
        }
        else if (str[index] == 'S')
        {
            origin.first--;
            takahashi.first--;
        }
        else
        {
            origin.second--;
            takahashi.second--;
        }

        smoke.insert(origin);
        if (smoke.find(takahashi) == smoke.end())
        {
            cout << 0;
        }
        else
        {
            cout << 1;
        }
    }

    cout << endl;
    return EXIT_SUCCESS;
}