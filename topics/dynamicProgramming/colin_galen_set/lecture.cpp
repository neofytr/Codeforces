#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> theorems(n);
    for (int &val : theorems)
        cin >> val;

    vector<int> behavior(n);
    for (int &val : behavior)
        cin >> val;

    int base = 0;

    // this is the base; when we take all the already available lecture sum
    for (int i = 0; i < n; i++)
    {
        if (behavior[i] == 1)
            base += theorems[i];
    }

    // build prefix sum for asleep minutes
    // this is how much we will gain if we include all the asleep ones too in the range [0, index - 1]
    vector<int> asleep_prefix(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        asleep_prefix[i] = asleep_prefix[i - 1] + (behavior[i - 1] == 0 ? theorems[i - 1] : 0);
    }

    int max_extra = 0;
    for (int i = 0; i <= n - k; i++)
    {
        // what if we include all the asleep ones from [i, i + k - 1]
        int extra = asleep_prefix[i + k] - asleep_prefix[i];
        max_extra = max(max_extra, extra);
    }

    cout << base + max_extra << endl;
    return EXIT_SUCCESS;
}
