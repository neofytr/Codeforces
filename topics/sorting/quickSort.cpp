#include <bits/stdc++.h>
using namespace std;

void quickSort(vector<int> &arr, int low, int high)
{
    if (low >= high)
    {
        // nothing to do, return
        return;
    }

    // get a random pivot
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[low], arr[pivotIndex]);
    int pivot = arr[low];

    int i = low, j = high;
    while (true)
    {
        // find next index which is larger than pivot
        while (i <= high && arr[i] <= pivot)
        {
            i++;
        }

        // find the next index (from the back) which is smaller (or equal) than pivot
        while (j >= low && arr[j] > pivot)
        {
            j--;
        }

        if (i >= j)
        {
            break;
        }
        else
        {
            swap(arr[i], arr[j]);
        }
    }

    // put pivot into the correct place
    // j now points to the end of the smaller than pivot array portion
    swap(arr[low], arr[j]);

    // sort recursively
    quickSort(arr, low, j - 1);
    quickSort(arr, j + 1, high);
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
