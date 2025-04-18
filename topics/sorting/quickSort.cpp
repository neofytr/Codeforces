#include <bits/stdc++.h>
using namespace std;

void quickSort(vector<int> &arr, int left, int right)
{
    
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

    quickSort(arr, 0, n - 1);
    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}