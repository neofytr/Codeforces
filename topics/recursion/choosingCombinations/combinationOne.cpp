// choosing combinations from set of unique elements

#include <bits/stdc++.h>
using namespace std;

int helper(vector<int> &arr, vector<int> &current, int remaining, int index)
{
    if (!remaining)
    {
        return 1;
    }

    if (remaining < 0)
    {
        return 0;
    }

    current.push_back(arr[index]);
    int include = helper(arr, current, remaining - arr[index], index + 1);
    current.pop_back();

    int exclude = helper(arr, current, remaining, index + 1);

    return include + exclude;
}

int main()
{
    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    // get number of subsets with sum = target
}