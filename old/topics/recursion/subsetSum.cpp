#include <bits/stdc++.h>
using namespace std;

set<int> sums;

void helper(vector<int> &arr, int curr_sum, int index)
{
    if (index >= arr.size())
    {
        sums.insert(curr_sum);
        return;
    }

    // either select the current element or not
    helper(arr, curr_sum + arr[index], index + 1);
    helper(arr, curr_sum, index + 1);
}

void getSums(vector<int> &arr)
{
    helper(arr, 0, 0);
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    getSums(arr);

    for (int val : sums)
    {
        cout << val << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}