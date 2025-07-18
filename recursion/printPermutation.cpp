#include <bits/stdc++.h>
#include <ostream>
#include <vector>
using namespace std;

void printPermutations(int index, vector<int> &arr) {
    int n = (int)arr.size();
    if (index >= n) {
        // we got a permutation; print it
        for (int counter = 0; counter < n; counter++)
            cout << arr[counter] << " ";
        cout << endl;
        return;
    }

    // for the position index in the permutation, we can choose any element
    // in the array arr from index to n - 1 (we have already placed the elements at position 0 to index - 1,
    // so, we can't pick those)
    for (int position = index; position < n; position++) {
        swap(arr[position], arr[index]);
        // generate permutations with the element arr[position] at the location index
        printPermutations(index + 1, arr);
        swap(arr[position], arr[index]);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    printPermutations(0, arr);
}