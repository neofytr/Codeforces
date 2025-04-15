#include <bits/stdc++.h>
using namespace std;

void mergeSort(vector<int> &arr, int left, int right, int &count)
{
    if (left >= right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid, count);
    mergeSort(arr, mid + 1, right, count);

    vector<int> temp(right - left + 1);
    // merge the two sorted arrays

    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            count += (mid - i + 1);
            temp[k++] = arr[j++];
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

int countInversions(vector<int> &arr)
{
    int count = 0;
    mergeSort(arr, 0, arr.size() - 1, count);
    return count;
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    cout << countInversions(arr) << endl;
    return 0;
}
