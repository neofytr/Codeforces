#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> movies(n); // (start, end)

    for (int i = 0; i < n; i++)
        cin >> movies[i].first >> movies[i].second;

    // sort by ending time
    sort(movies.begin(), movies.end(), [](auto &a, auto &b)
         { return a.second < b.second; });

    int count = 0;
    int current_end_time = 0;

    for (auto elt : movies)
    {
        long long start = elt.first;

        if (start >= current_end_time)
        {
            count++;
            current_end_time = elt.second;
        }
    }

    cout << count << "\n";
}
