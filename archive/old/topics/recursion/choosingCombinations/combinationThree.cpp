// subset of a multiset

#include <bits/stdc++.h>
using namespace std;

int helper(vector<int> &arr, vector<int> &current, int remaining, int index)
{
    if (!remaining)
    {
        return 1;
    }

    int length = arr.size();
    int sum = 0;
    for (int curr_index = index; curr_index < length; curr_index++)
    {
        // skip the duplicate elements at the current level
        if (curr_index > index && arr[curr_index] == arr[curr_index - 1])
        {
            continue;
        }

        if (arr[curr_index] > remaining) // no need to continue further
        {
            break;
        }

        // choose an element at the current level to be in the subset
        current.push_back(arr[curr_index]);
        sum += helper(arr, current, remaining - arr[curr_index], curr_index + 1);
        current.pop_back();
    }

    return sum;
}

int getCount(vector<int> &arr, int target)
{
    vector<int> current;
    return helper(arr, current, target, 0);
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
    cout << getCount(arr, target) << endl;
    return EXIT_SUCCESS;
}