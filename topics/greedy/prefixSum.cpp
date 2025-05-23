#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<long long> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
    }

    vector<long long> prefix(n + 1, 0);

    int ops = 0;
    for (int index = 1; index <= n; index++)
    {
        prefix[index] = prefix[index - 1] + arr[index];
    }

    priority_queue<long long> max_heap;
    for (int index = m; index >= 1; index--)
    {
        if (prefix[index] < prefix[m])
        {
            // we can reduce from index + 1 until m
            while (prefix[index] < prefix[m] && !max_heap.empty())
            {
                prefix[m] -= 2 * max_heap.top();
                max_heap.pop();
                ops++;
            }
        }

        if (arr[index] > 0)
        {
            max_heap.push(arr[index]);
        }
    }

    priority_queue<long long, vector<long long>, greater<long long>> min_heap;
    long long sum = prefix[m];

    for (int index = m + 1; index <= n; index++)
    {
        sum += arr[index];
        if (arr[index] < 0)
        {
            // we can change starting from m + 1, so we include that index first
            min_heap.push(arr[index]);
        }
        if (sum < prefix[m])
        {
            // change from m + 1 to index
            while (sum < prefix[m] && !min_heap.empty())
            {
                sum -= 2 * min_heap.top();
                min_heap.pop();
                ++ops;
            }
        }
    }

    cout << ops << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
