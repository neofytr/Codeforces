#include <bits/stdc++.h>
using namespace std;

void quickSort(vector<int> &arr, int start, int len)
{
    if (len <= 0 || len == 1)
    {
        // do nothing; already sorted
        return;
    }

    int pivot = arr[start]; // choose first element as the pivot

    // first find the correct place of the pivot in the array
    int placeOfPivot = start;
    for (int index = start; index < start + len; index++)
    {
        if (arr[index] < pivot)
        {
            placeOfPivot++;
        }
    }

    // place smaller elements (smaller than pivot) before the pivot and larger elements (>= pivot) after it
    int smallerCurr = start;
    int largerCurr = placeOfPivot + 1;
    for (int index = start; index < start + len; index++)
    {
        if (arr[index] < pivot)
        {
            swap(arr[smallerCurr++], arr[index]);
        }
        else
        {
            swap(arr[largerCurr++], arr[index]);
        }
    }

    arr[placeOfPivot] = pivot;

    // do recursion
    quickSort(arr, start, placeOfPivot - start);
    quickSort(arr, placeOfPivot + 1, largerCurr - placeOfPivot);
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

    quickSort(arr, 0, n);
    for (int val : arr)
    {
        cout << val << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}