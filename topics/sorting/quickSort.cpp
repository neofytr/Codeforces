#include <bits/stdc++.h>
using namespace std;

int partition(vector<int> &arr, int low, int high)
{
    // randomly select the pivot
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[high]); // move pivot to the end
    int pivot = arr[high];

    int currLow = low - 1;
    for (int index = low; index <= high; index++)
    {
        if (arr[index] <= pivot)
        {
            swap(arr[++currLow], arr[index]);
        }
    }

    // pivot is also now in it's correct place (at currLow)
    return currLow;
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int partitionIndex = partition(arr, low, high);
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
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
