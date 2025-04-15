// print the target-th permutation of a set
#include <bits/stdc++.h>
using namespace std;

// prints the array
void printArray(const vector<int> &arr)
{
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

// recursively generates permutations and stops when the target-th is reached
void helper(vector<int> &arr, int index, int &count, int target, bool &found)
{
    int length = arr.size();

    // base case: full permutation formed
    if (index >= length)
    {
        count++; // we've formed one permutation

        if (count == target)
        {
            printArray(arr);
            found = true; // mark that we've found the desired permutation
        }
        return;
    }

    for (int curr = index; curr < length; curr++)
    {
        swap(arr[curr], arr[index]); // fix one element
        helper(arr, index + 1, count, target, found);
        swap(arr[curr], arr[index]); // backtrack

        if (found)
            return; // stop further recursion once target is printed
    }
}

// initiates permutation generation
void printPermutations(vector<int> &arr, int target)
{
    int count = 0;
    bool found = false;
    helper(arr, 0, count, target, found);

    if (!found)
        cout << "target-th permutation does not exist\n";
}

int main()
{
    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    sort(arr.begin(), arr.end()); // sort to start with lexicographically smallest
    printPermutations(arr, target);
    return 0;
}
