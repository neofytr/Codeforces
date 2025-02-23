#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    unordered_map<int, int> freq;
    for (int num : arr)
    {
        freq[num]++;
    }

    int score = 0;

    for (int num : arr)
    {
        if (freq[num] > 0 && freq[k - num] > 0)
        {
            // ensure that we're not pairing a number with itself unless there are two of them
            if (num != k - num || freq[num] > 1)
            {
                score++;
                freq[num]--;
                freq[k - num]--;
            }
        }
    }

    cout << score << "\n";
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

    return 0;
}
