#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    unordered_map<int, int> freq;

    int count = 0;
    for (int j = 0; j < n; j++) {
        int target = j - arr[j];
        if (target < 0)
            continue;
        count += freq[target];
        freq[j + arr[j]]++; // updating frequency after each iteration guarantees that the frequencies we find during the iteration have indexes < j
        // which is what we want for i
    }
    return 0;
}
