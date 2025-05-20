#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    long long left = 0;
    long long right = 0;
    long long count = 0;

    multiset<long long> window;

    while (left < n)
    {
        // expand the window to the right
        while (right < n)
        {
            window.insert(arr[right]);
            long long current_max = *window.rbegin();
            long long current_min = *window.begin();

            if (current_max - current_min > k)
            {
                // undo the insert that made it invalid
                window.erase(window.find(arr[right]));
                break;
            }
            right++;
        }

        count += (right - left);

        // remove the current left element from the window
        window.erase(window.find(arr[left]));
        left++;
    }

    cout << count << endl;
    return 0;
}
