#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> arr(n);
    for (int index = 0; index < n; index++) {
        cin >> arr[index].first;
        arr[index].second = index + 1;
    }

    sort(arr.begin(), arr.end());
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int sum = arr[left].first + arr[right].first;
        if (sum < x)
            left++;
        else if (sum > x)
            right--;
        else {
            cout << arr[left].second << " " << arr[right].second << endl;
            return EXIT_SUCCESS;
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
