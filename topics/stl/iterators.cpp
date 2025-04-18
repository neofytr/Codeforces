#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    vector<int>::iterator starting = arr.begin(); // points to the beginning of the array

    // iterator to the element following the last element of the array
    // this acts as a placeholder; attempting to access it results in undefined behavior
    vector<int>::iterator ending = arr.end();

    // container is empty iff arr.begin() == arr.end()

    cout << *starting << endl; // dereferencing the iterator

    vector<int>::reverse_iterator last = arr.rbegin(); // reverse iterator; points to the last element of the container
    // incrementing a reverse iterator increments it in reverse

    cout << *(last + 1) << endl;
}