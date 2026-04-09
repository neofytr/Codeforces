#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    int left = 0;
    int right = 0;
    long long count = 0;

    multiset<long long> num;

    while (left < n)
    {
        while (right < n)
        {
            num.insert(arr[right]);

            long long max_val = *num.rbegin();
            long long min_val = *num.begin();

            if (max_val - min_val > k)
            {
                num.erase(num.find(arr[right]));
                break;
            }

            right++;
        }

        count += (right - left);

        num.erase(num.find(arr[left++]));
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}