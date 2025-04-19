#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> ingredientToDishes(n + 1);

    vector<int> dislikedCount(m + 1, 0);

    for (int dish = 1; dish <= m; dish++)
    {
        int k;
        cin >> k;
        dislikedCount[dish] = k;

        for (int j = 0; j < k; j++)
        {
            int ingredient;
            cin >> ingredient;
            ingredientToDishes[ingredient].push_back(dish);
        }
    }

    set<int> availableDishes;

    vector<int> result(n);
    for (int day = 0; day < n; day++)
    {
        int b;
        cin >> b;

        for (int dish : ingredientToDishes[b])
        {
            dislikedCount[dish]--;
            if (dislikedCount[dish] == 0)
            {
                availableDishes.insert(dish);
            }
        }

        result[day] = availableDishes.size();
    }

    for (int count : result)
    {
        cout << count << endl;
    }

    return 0;
}