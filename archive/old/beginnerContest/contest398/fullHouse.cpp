#include <bits/stdc++.h>
using namespace std;

bool is_full_house(vector<int> &cards)
{
    map<int, int> freq;
    for (int card : cards)
        freq[card]++;

    if (freq.size() != 2)
        return false;

    auto it = freq.begin();
    int count1 = it->second;
    ++it;
    int count2 = it->second;

    return (count1 == 3 && count2 == 2) || (count1 == 2 && count2 == 3);
}

int main()
{
    vector<int> a(7);
    for (int i = 0; i < 7; ++i)
        cin >> a[i];

    for (int i = 0; i < 7; ++i)
    {
        for (int j = i + 1; j < 7; ++j)
        {
            vector<int> temp;
            for (int k = 0; k < 7; ++k)
            {
                if (k != i && k != j)
                    temp.push_back(a[k]);
            }
            if (is_full_house(temp))
            {
                cout << "Yes\n";
                return 0;
            }
        }
    }

    cout << "No\n";
    return 0;
}
