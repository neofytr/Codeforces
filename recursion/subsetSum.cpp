#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

void getSubsets(int index, int currSum, vector<int> &arr, set<int> &sums) {
    if (index >= (int)arr.size()) {
        sums.insert(currSum);
        return;
    }

    // we can either pick the current element to be included in the subset, or not
    getSubsets(index + 1, currSum + arr[index], arr, sums);
    getSubsets(index + 1, currSum, arr, sums);
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // arr is an array of distinct integers
    set<int> sums;
    getSubsets(0, 0, arr, sums);
    for (int sum : sums)
        cout << sum << " ";
    cout << endl;
    return EXIT_SUCCESS;
}