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

bool helper(int index, vector<int> &arr, vector<int> &current, int target)
{
    if (index == arr.size()) // the empty subsequence won't be printed now
    {
        if (getSum(current) == target)
        {
            printVector(current);
            return true;
        }
        return false;
    }

    // include the current index
    current.push_back(arr[index]);
    if (helper(index + 1, arr, current, target))
    {
        current.pop_back();
        return true;
    }

    // exclude the current element
    current.pop_back();
    if (helper(index + 1, arr, current, target))
    {
        return true;
    }

    return false;
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