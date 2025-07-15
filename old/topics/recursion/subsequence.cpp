#include <bits/stdc++.h>
using namespace std;

void printVector(vector<int> &arr)
{
    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
}

int getSum(vector<int> &arr)
{
    int sum = 0;
    for (int val : arr)
    {
        sum += val;
    }

    return sum;
}

void helper(int index, vector<int> &arr, vector<int> &current, int target)
{
    if (index == arr.size()) // the empty subsequence won't be printed now
    {
        if (current.size())
        {
            if (getSum(current) == target)
            {
                printVector(current);
            }
        }
        return;
    }

    // include the current index
    current.push_back(arr[index]);
    helper(index + 1, arr, current, target);

    // exclude the current element
    current.pop_back();
    helper(index + 1, arr, current, target);
}

void subsequence(vector<int> &arr, int target)
{
    vector<int> current;
    helper(0, arr, current, target);
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

    subsequence(arr, 10);
}