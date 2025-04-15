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

void helper(int index, vector<int> &arr, vector<int> &current)
{
    if (index == arr.size())
    {
        printVector(current);
        return;
    }

    // include the current index
    current.push_back(arr[index]);
    helper(index + 1, arr, current);

    // exclude the current element
    current.pop_back();
    helper(index + 1, arr, current);
}

void subsequence(vector<int> &arr)
{
    vector<int> current;
    helper(0, arr, current);
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
}