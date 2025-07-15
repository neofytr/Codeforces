// choosing combinations from set of unique elements

#include <bits/stdc++.h>
using namespace std;

int helper(vector<int> &arr, vector<int> &current, int remaining, int index)
{
    if (!remaining)
    {
        return 1;
    }

    if (remaining < 0 || index >= arr.size())
    {
        return 0;
    }

    int sum = 0;

    // i have to choose an element at the current level
    for (int curr_index = index; curr_index < arr.size(); curr_index++)
    {
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