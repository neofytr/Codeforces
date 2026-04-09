#include <bits/stdc++.h>
using namespace std;

// this function performs merge sort on the array and counts inversions
void mergeSort(vector<int> &arr, int left, int right, int &count)
{
    // base case: one or zero elements means no inversions
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    // recursively sort the left half and count inversions within it
    mergeSort(arr, left, mid, count);

    // recursively sort the right half and count inversions within it
    mergeSort(arr, mid + 1, right, count);

    // now count the inversions that occur across the left and right halves
    // at this point, the left and right halves are sorted, but we can still count
    // the original inversions that existed *between* the halves before sorting
    // this is valid because:
    //
    // - merge sort doesn't change the relative order of elements between the two halves;
    // - it only changes order *within* the halves;
    // - so if an element from the left half ends up after an element from the right half,
    //   it would have also done so in the original array;
    // - hence, the number of cross inversions is preserved.

    vector<int> temp(right - left + 1); // temporary array to store the merged subarray

    int i = left;    // pointer for the left half
    int j = mid + 1; // pointer for the right half
    int k = 0;       // pointer for the temp array

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            // no inversion: place arr[i] in the merged array
            temp[k++] = arr[i++];
        }
        else
        {
            // inversion: all remaining elements in the left half from i to mid
            // are greater than arr[j], so they form inversions with arr[j]
            count += (mid - i + 1);

            // place arr[j] in the merged array
            temp[k++] = arr[j++];
        }
    }

    // copy any remaining elements from the left half
    while (i <= mid)
        temp[k++] = arr[i++];

    // copy any remaining elements from the right half
    while (j <= right)
        temp[k++] = arr[j++];

    // copy the merged and sorted subarray back into the original array
    for (int index = left; index <= right; index++)
        arr[index] = temp[index - left];
}

// wrapper function to initialize inversion count and start merge sort
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

    // read the input array
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // output the total number of inversions
    cout << countInversions(arr) << endl;

    return 0;
}
