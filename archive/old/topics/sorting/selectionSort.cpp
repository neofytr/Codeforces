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

    int smallest;
    for (int index = 0; index < n; index++)
    {
        smallest = index;
        for (int counter = index; counter < n; counter++)
        {
            if (arr[counter] < arr[smallest])
            {
                smallest = counter;
            }
        }

        swap(arr[index], arr[smallest]);
    }

    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}