#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    for (int index = 0; index < n; index++)
    {
        for (int index = 0; index < n - 1; index++)
        {
            if (arr[index] > arr[index + 1])
            {
                swap(arr[index], arr[index + 1]);
            }
        }
    }

    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}