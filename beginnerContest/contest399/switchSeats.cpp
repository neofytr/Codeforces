#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> arr(n + 1, vector<int>(2)); // 1-based indexing
    // arr[r] denotes the indexes where r appears in the sequence

    int val;
    for (int index = 1; index <= n; index++)
    {
        cin >> val; // val is in the range 1 to n
        arr[val].push_back(index);
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