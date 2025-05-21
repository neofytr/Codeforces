// https://cses.fi/problemset/task/1094

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    long long moves = 0;

    for (int index = 1; index < n; index++)
    {
        if (arr[index - 1] <= arr[index])
        {
            continue;
        }
        else
        {
            moves += (arr[index - 1] - arr[index]);
            arr[index] = arr[index - 1];
        }
    }

    cout << moves << endl;
    return EXIT_SUCCESS;
}