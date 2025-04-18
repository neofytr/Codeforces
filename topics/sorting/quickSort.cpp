#include <bits/stdc++.h>
using namespace std;

void quickSort(vector<int> &arr, int low, int high)
{
    if (low >= high)
        return;

    int pivot = arr[low];
    int i = low - 1, j = high + 1;

    while (true)
    {
        // move i to the right until arr[i] >= pivot
        do
        {
            i++;
        } while (arr[i] < pivot);

        // move j to the left until arr[j] <= pivot
        do
        {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            break;

        swap(arr[i], arr[j]);
    }

    quickSort(arr, low, j);      // j is the last index of left partition
    quickSort(arr, j + 1, high); // right partition
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    quickSort(arr, 0, n - 1);

    for (int val : arr)
        cout << val << " ";
    cout << endl;

    return EXIT_SUCCESS;
}
