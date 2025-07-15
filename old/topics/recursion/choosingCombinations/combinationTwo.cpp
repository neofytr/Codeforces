// we can choose any element from a set, any number of times
// the set contains unique elements

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

    current.push_back(arr[index]); // choose the same at the current level
    int chooseAgain = helper(arr, current, remaining - arr[index], index);
    current.pop_back();

    int dontChooseAgain = helper(arr, current, remaining, index + 1);

    return chooseAgain + dontChooseAgain;
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