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

    // returns a reverse iterator pointing to the theoretical element
    // right before the first element in the container
    vector<int>::reverse_iterator first = arr.rend();

    cout << *(first - 1) << endl;

    /*

    Iterator invalidation

    Due to update(insert/delete) of container that is using iterators

    No runtime error but iterator no longer guaranteed to have access to the same
    element after the update

    Well documented rules

    Depends on container implementation

    */

    auto it = arr.begin() + 3;
    cout << "*it -> " << *it << endl;

    /*

    arr.insert(it, 100); // it now points to some garbage
    cout << "*it -> " << *it << endl;

    */

    // to fix this, dohttps://en.cppreference.com/w/cpp/container

    it = arr.insert(it, 100);

    cout << "*it -> " << *it << endl; // it now points to 100

    // iterator invalidation rules at:

    // https://en.cppreference.com/w/cpp/container

    /*

    An iterator is a pointer-like object representing an
    element's pisition in a container. Its used to iterate over
    elements in a container

    arr.begin() + i points to arr[i];

    */

    return EXIT_SUCCESS;
}