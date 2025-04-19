#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> points(m);
    for (int index = 0; index < m; index++)
    {
        cin >> points[index].first >> points[index].second;
    }

    int count = 0;

    for (int index = 0; index < m; index++)
    {
        int x1 = points[index].first;
        int y1 = points[index].second;
        for (int counter = index + 1; counter < m; counter++)
        {
            int x2 = points[counter].first;
            int y2 = points[counter].second;
            if ((x1 - x2) * (y1 - y2) < 0 && abs(x1 - x2) == abs(y1 - y2))
            {
                count++;
            }
        }
    }

    cout << (m * (m - 1)) / 2 - count << endl;
}