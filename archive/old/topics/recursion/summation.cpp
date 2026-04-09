#include <bits/stdc++.h>
using namespace std;

int summation(vector<int> &arr, int start, int end)
{
    if (start == end)
    {
        return arr[start];
    }

    return (arr[start] + summation(arr, start + 1, end));
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

    cout << summation(arr, 0, n - 1) << endl;
}