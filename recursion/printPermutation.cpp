#include <bits/stdc++.h>
using namespace std;

void printPermutationsTwo(int index, vector<int> &arr, vector<int> &perm, vector<bool> chosen) {
    int n = (int)arr.size();
    if (index >= n) {
        // we got a permutation; print it
        for (int counter = 0; counter < n; counter++)
            cout << perm[counter] << " ";
        cout << endl;
        return;
    }

    // for the current position index inside perm, we choose an element that is not already chosen
    for (int counter = 0; counter < n; counter++) {
        if (!chosen[counter]) {
            perm[index] = arr[counter];
            chosen[counter] = true;
            printPermutationsTwo(index + 1, arr, perm, chosen);
            chosen[counter] = false;
        }
    }

    return;
}

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

    vector<int> perm(n);
    vector<bool> chosen(n);
    printPermutationsTwo(0, arr, perm, chosen);
}