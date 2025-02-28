#include <bits/stdc++.h>
using namespace std;

void generate_permutations(vector<int> &arr, int start, int end)
{
    if (start == end) // got a permutation
    {
        for (int val : arr)
        {
            cout << val << " ";
        }
        cout << endl;
        return;
    }

    for (int index = start; index <= end; index++)
    {
        swap(arr[start], arr[index]);
        generate_permutations(arr, start + 1, end);
        swap(arr[start], arr[index]);
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

    generate_permutations(arr, 0, n - 1);
    return EXIT_SUCCESS;
}