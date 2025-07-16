#include <bits/stdc++.h>
using namespace std;

void printSubsequenceWithSum(int index, int k, int currSum, vector<int> &arr, vector<int> &sub) {
    int size = (int)arr.size();
    if (index >= size) {
        // we have a subsequence now
        if (currSum == k) {
            // print the subsequence
            if (!sub.size())
                cout << "{}";
            else
                for (int val : sub)
                    cout << val << " ";
            cout << endl;
        }
        return;
    }

    // we can either choose this index or not
    sub.push_back(arr[index]);
    printSubsequenceWithSum(index + 1, k, currSum + arr[index], arr, sub);
    sub.pop_back();
    printSubsequenceWithSum(index + 1, k, currSum, arr, sub);
    return;
}

void printSubsequence(int index, vector<int> &arr, vector<int> &sub) {
    int size = (int)arr.size();
    if (index >= size) {
        // the subsequence has been built now
        // it can be empty too
        if (!sub.size())
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
    return;
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n), sub;
    for (int &val : arr)
        cin >> val;

    // printSubsequence(0, arr, sub);
    printSubsequenceWithSum(0, 10, 0, arr, sub);
    return EXIT_SUCCESS;
}