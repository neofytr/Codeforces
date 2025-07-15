#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

void solve()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    if (n == 1)
    {
        cout << 0 << endl;
        return;
    }

    int left = 0, right = n - 1;

    if (arr[left] == arr[right])
    {
        int eq = arr[left];
        while (left <= right && arr[left] == eq)
        {
            left++;
        }
        while (right >= left && arr[right] == eq)
        {
            right--;
        }

        cout << max(0, right - left + 1) << endl;
    }
    else
    {
        int left_num = arr[left];
        int right_num = arr[right];

        int left_ptr = 0, right_ptr = n - 1;

        while (left_ptr < n && arr[left_ptr] == left_num)
        {
            left_ptr++;
        }

        while (right_ptr >= 0 && arr[right_ptr] == right_num)
        {
            right_ptr--;
        }

        cout << min(n - left_ptr, right_ptr + 1) << endl;
    }
}

int main()
{
    FAST_IO;
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }
    return 0;
}
