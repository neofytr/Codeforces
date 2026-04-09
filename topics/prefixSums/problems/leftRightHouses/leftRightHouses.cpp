#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: leftRightHouses
// URL: https://codeforces.com/problemset/problem/1945/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string str;
        cin >> str;

        set<pair<int, int>> ans;
        vector<int> arr(n + 1);
        for (int index = 1; index <= n; index++)
            arr[index] = str[index - 1] - '0';

        int road = 0;  // road is between road and road + 1
        int left = 0;  // the number of residents on the left of the road that want to live on the left
        int right = 0; // the number of residents on the right of the road that want to live on the right

        for (int i = road + 1; i <= n; i++)
            if (arr[i])
                right++;
        while (road <= n) {
            int leftSide = road;
            int rightSide = n - leftSide;
            if ((left >= (leftSide + 1) / 2) && (right >= (rightSide + 1) / 2))
                ans.insert({abs(2 * road - n), road});
            road++;
            if (road <= n && !arr[road])
                left++;
            if (road <= n && arr[road])
                right--;
        }
        cout << ans.begin()->second << endl;
    }
    return 0;
}