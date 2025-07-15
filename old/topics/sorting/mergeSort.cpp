#include <bits/stdc++.h>
using namespace std;

void mergeSort(vector<int> &arr, int left, int right)
{
    if (left == right)
    {
        // already sorted
        return;
    }

    int mid = left + (right - left) / 2;

    // recursively sort the left and right subarrays
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // merge the sorted subarrays
    vector<int> temp(right - left + 1);

    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        if (arr[i] > arr[j])
        {
            temp[k++] = arr[j++];
        }
        else
        {
            temp[k++] = arr[i++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }

    while (j <= right)
    {
        temp[k++] = arr[j++];
    }

    for (int index = left; index <= right; index++)
    {
        arr[index] = temp[index - left];
    }
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

    mergeSort(arr, 0, n - 1);
    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}