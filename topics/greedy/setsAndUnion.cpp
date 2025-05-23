// https://codeforces.com/contest/1882/problem/B

#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &first, vector<int> &second)
{
    vector<int> result;
    int i = 0, j = 0;
    while (i < first.size() && j < second.size())
    {
        if (first[i] < second[j])
        {
            result.push_back(first[i++]);
        }
        else
        {
            result.push_back(second[j++]);
        }
    }
    while (i < first.size())
        result.push_back(first[i++]);
    while (j < second.size())
        result.push_back(second[j++]);
    first = move(result);
}

int dounion(vector<int> &first, vector<int> &second)
{
    // first and second are already sorted and each contain all elements different

    int count = 0;
    int i = 0, j = 0;

    while (i < first.size() && j < second.size())
    {
        if (first[i] < second[j])
        {
            i++;
        }
        else if (first[i] > second[j])
        {
            j++;
        }
        else
        {
            i++, j++;
        }
        count++;
    }

    while (i < first.size())
    {
        count++;
        i++;
    }

    while (j < second.size())
    {
        count++;
        j++;
    }

    return count;
}

void solve()
{
    int n;
    cin >> n;

    vector<vector<int>> sets(n, vector<int>());
    unordered_map<int, int> freq;
    int k, temp;
    for (int index = 0; index < n; index++)
    {
        cin >> k;
        while (k--)
        {
            cin >> temp;
            freq[temp]++;
            sets[index].push_back(temp); // all the sets are already sorted
        }
    }

    int unique = freq.size();

    vector<bool> chosen(n, false);
    vector<int> first;

    while (true)
    {
        int max_index = -1;
        int max_count = INT_MIN;
        for (int index = 0; index < n; index++)
        {
            if (!chosen[index])
            {
                int ans = dounion(first, sets[index]);
                if (ans > max_count)
                {
                    max_count = ans;
                    max_index = index;
                }
            }
        }

        if (max_count >= unique)
        {
            cout << first.size() << endl;
            return;
        }

        chosen[max_index] = true;
        merge(first, sets[max_index]);
    }
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }
}