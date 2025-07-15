#include <bits/stdc++.h>
using namespace std;

void reverse(vector<int> &arr, int start, int end)
{
    if (start >= end)
    {
        return;
    }

    swap(arr[start], arr[end]);
    reverse(arr, start + 1, end - 1);
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

    reverse(arr, 0, n - 1);

    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}