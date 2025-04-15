#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    // prefix[r] is the sum of first r elements of arr
    vector<int> prefix(n + 1, 0);

    for (int index = 1; index <= n; index++)
    {
        prefix[index] = prefix[index - 1] + arr[index - 1];
    }

    // sum of values from index l to index r in arr is: (l and r are in 0-based indexing)
    cout << prefix[r + 1] - prefix[l] << endl;
}