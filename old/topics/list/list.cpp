#include <bits/stdc++.h>
using namespace std;

int main() {
    // list
    /* Sequence containers, optimized for rapid insert and delete operations
     * Elements are stored non-contiguously
     * Doesn't support random access (so can't do itr + 2 or some shit, but can do itr++/--)
     * Bi-directional iterations(for single direction, use std::forward_list)
     */

    list<int> arr = {1, 2, 3, 4};
    // functions perform the same as that on vectors (mostly)

    cout << arr.size() << endl;
    cout << arr.front() << endl;
    cout << arr.back() << endl;

    arr.push_back(10);
    arr.push_front(200);
    arr.pop_back();
    arr.pop_front();

    arr.insert(next(arr.begin(), 2), 100); // insert at index 2, 100
    arr.erase(next(arr.begin(), 2)); // deletes the element at index 2
    // we can use ranged erase

    arr.erase(arr.begin(), ++arr.begin()); // removes the first element; includes the first itr and not the next

    arr.remove(10); // removes the first occurrence of 10 in the list, from the start

    for (auto itr = arr.begin(); itr != arr.end(); ++itr) {
        cout << *itr << endl;
    }

    // the STL list implements the doubly linked list

    return EXIT_SUCCESS;
}
