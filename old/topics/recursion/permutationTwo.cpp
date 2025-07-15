// print all permutations of a set
#include <bits/stdc++.h>
using namespace std;

void printArray(vector<int> &arr)
{
    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
}

void helper(vector<int> &arr, vector<bool> &chosen, vector<int> &current, int num)
{
    int length = arr.size();
    if (num >= length)
    {
        printArray(current);
        return;
    }

    // choose an element at the current level
    for (int curr = 0; curr < length; curr++)
    {
        if (!chosen[curr])
        {
            chosen[curr] = true;
            current[num] = arr[curr];
            helper(arr, chosen, current, num + 1);
            chosen[curr] = false;
        }
    }
}

void printPermutations(vector<int> &arr)
{
    vector<bool> chosen(arr.size(), false);
    vector<int> current(arr.size());
    helper(arr, chosen, current, 0);
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

    printPermutations(arr);
    return EXIT_SUCCESS;
}