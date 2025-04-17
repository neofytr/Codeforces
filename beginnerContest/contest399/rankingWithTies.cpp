#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> scores(n); // {index, score}

    for (int i = 0; i < n; ++i)
    {
        int score;
        cin >> score;
        scores[i] = {i, score};
    }

    sort(scores.begin(), scores.end(), [](auto &a, auto &b)
         {
             return a.second > b.second; // sort by score descending
         });

    vector<int> rank(n);
    int curr_rank = 1;
    int curr_count = 0;
    int curr = scores[0].second;

    for (int index = 0; index < n; index++)
    {
        if (curr == scores[index].second)
        {
            curr_count++;
        }
        else
        {
            curr_rank += curr_count;
            curr_count = 1;
            curr = scores[index].second;
        }

        rank[scores[index].first] = curr_rank;
    }

    for (int val : rank)
    {
        cout << val << "\n";
    }

    return EXIT_SUCCESS;
}
