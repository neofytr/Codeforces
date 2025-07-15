#include <bits/stdc++.h>
using namespace std;

void printArr(vector<int> &arr)
{
    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
}

void helper(vector<int> &arr, vector<int> &curr, int index)
{
    int length = arr.size();
    if (index >= length)
    {
        printArr(curr);
        return;
    }

    // choose an element at the current level
    for (int curr_index = index; curr_index < length; curr_index++)
    {
        if (curr_index > index && arr[curr_index] == arr[curr_index - 1])
        {
            continue; // skip duplicates
        }

        curr.push_back(arr[curr_index]);
        helper(arr, curr, curr_index + 1);
        curr.pop_back();
    }
}

void printSubsets(vector<int> &arr)
{
    vector<int> curr;
    curr.reserve(arr.size());
    helper(arr, curr, 0);
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

    sort(arr.begin(), arr.end());

    printSubsets(arr);
    return EXIT_SUCCESS;
}