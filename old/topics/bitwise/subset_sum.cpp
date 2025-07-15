#include <bits/stdc++.h>
using namespace std;

int main()
{
    size_t n;
    int target;
    cin >> n >> target;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    long long sum;

    // iterate over all subsets of arr to see if any subset sum is equal to the target
    // there is a bijection between a subset of arr and the binary string of check from bit position 0 to n - 1
    for (uint32_t check = 0; check < 1UL << n; check++)
    {
        sum = 0;
        for (size_t test = 0; test < n; test++)
        {
            if (check & (1UL << test))
            {
                sum += arr[test];
            }
        }

        if (sum == target)
        {
            cout << "yes" << endl;
            return EXIT_SUCCESS;
        }
    }

    cout << "no" << endl;
    return EXIT_SUCCESS;
}