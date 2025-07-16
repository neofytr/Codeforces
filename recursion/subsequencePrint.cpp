#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

void printSubsequence(int index, vector<int> &arr, vector<int> &sub) {
    int size = (int)sub.size();
    if (index >= size) {
        // the subsequence has been built now
        // it can be empty too
        if (!size)
            cout << "{}";
        else
            for (int val : sub)
                cout << val << " ";
        cout << "\n";
        return;
    }

    // we can either select the element at the current index to be in the
    // subsequence or we don't select it
    sub.push_back(arr[index]);
    printSubsequence(index + 1, arr, sub);
    sub.pop_back();
    printSubsequence(index + 1, arr, sub);
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n), sub;
    for (int &val : arr)
        cin >> val;

    printSubsequence(0, arr, sub);
    return EXIT_SUCCESS;
}