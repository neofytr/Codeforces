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

void helper(vector<int> &arr, int index)
{
    int length = arr.size();
    if (index >= length)
    {
        printArray(arr);
        return;
    }

    for (int curr = index; curr < length; curr++)
    {
        swap(arr[curr], arr[index]);
        helper(arr, index + 1);
        swap(arr[curr], arr[index]);
    }
}

void printPermutations(vector<int> &arr)
{
    helper(arr, 0);
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