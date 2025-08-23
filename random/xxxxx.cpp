// https://codeforces.com/problemset/problem/1364/A

#include <bits/stdc++.h>
using namespace std;

#define int long long
int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        // 1 <= x <= 10^4
        // 0 <= arr[r] <= 10^4

        // we are to find the longest subarray such that the sum of its elements isn't divisible by x

        // if every element of the array is divisible by x, the answer is -1
        // if the sum of all the elements of the array isn't divisible by x, the answer is n
        // now, the sum of all the elements of the array is divisible by x, but not all the array elements are divisible by x
        // the key idea now is removing elements that are divisible by x doesn't do us any benefits, but once we remove an element
        // that isn't, the sum won't be divisible by x
        // let the first non-multiple of x be at index l, and the last be at index r
        // we must either remove the prefix all the way upto r, or the suffix all the way up to r, and we'll clearly remove
        // whichever is shorter

        bool all = true;
        for (const int val : arr)
            if ((val % x)) {
                all = false;
                break;
            }
        if (all) {
            cout << -1 << endl;
            continue;
        }

        if (const int sum = accumulate(arr.begin(), arr.end(), 0LL); sum % x) {
            cout << n << endl;
            continue;
        }

        int first;
        bool foundFirst = false;
        int last;

        for (int index = 0; index < n; index++) {
            const int val = arr[index];
            if (val % x) {
                if (!foundFirst) {
                    foundFirst = true;
                    first = index;
                }
                last = index;
            }
        }

        int prefixLen = (first + 1);
        int suffixLen = (n - last);

        cout << n - min(prefixLen, suffixLen) << endl;
    }
}