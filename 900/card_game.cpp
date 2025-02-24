#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

int64_t find(vector<int64_t> &cards, int64_t element)
{
    int64_t size = cards.size();
    for (int64_t counter = 0; counter < size; counter++)
    {
        if (cards[counter] == element)
        {
            return counter;
        }
    }
    return -1;
}

int main()
{
    int64_t t, n, m;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        vector<int64_t> cards(n * m);
        for (size_t counter = 0; counter < n; counter++)
        {
            for (size_t index = 0; index < m; index++)
            {
                cin >> cards[counter * m + index];
            }
        }

        vector<int64_t> cards_sorted = cards;
        sort(cards_sorted.begin(), cards_sorted.end());

        vector<int64_t> permutation;
        bool valid = true;
        unordered_set<int64_t> used_cows;

        for (int64_t i = 0; i < n * m; i++)
        {
            int64_t pos = find(cards, cards_sorted[i]);
            int64_t cow = pos / m;

            if (i < n)
            {
                if (used_cows.count(cow))
                {
                    valid = false;
                    break;
                }
                used_cows.insert(cow);
                permutation.push_back(cow + 1);
            }
            else
            {
                if (cow != permutation[i % n] - 1)
                {
                    valid = false;
                    break;
                }
            }
        }

        if (!valid)
        {
            cout << -1 << endl;
        }
        else
        {
            for (size_t i = 0; i < n; i++)
            {
                cout << permutation[i] << (i == n - 1 ? "\n" : " ");
            }
        }
    }
    return 0;
}