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

    for (int index = 1; index < n; index++)
    {
        int counter = index - 1;
        while (counter >= 0 && arr[counter] > arr[counter + 1])
        {
            swap(arr[counter], arr[counter + 1]);
            counter--;
        }
    }

    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}