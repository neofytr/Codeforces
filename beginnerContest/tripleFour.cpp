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

    for (int index = 0; index < n - 2; index++)
    {
        if (arr[index] == arr[index + 1] && arr[index + 1] == arr[index + 2])
        {
            cout << "Yes\n";
            return EXIT_SUCCESS;
        }
    }

    cout << "No\n";
    return EXIT_SUCCESS;
}