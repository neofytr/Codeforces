#include <bits/stdc++.h>
using namespace std;

int main() {
    // set is an unordered collection of unique elements
    // used when we simply care about whether an element exists or not, regardless of its order and frequency
    // finding whether an element exists are not in a set happens in log(n)

    set<int> setOne = {1, 2, 3, 3}; // initialize the set; the duplicate will be ignored

    // they work the same way as in vectors
    setOne.insert(10);
    // 10 has been inserted; returns a pair (itr, bool); itr is the iterator to the element inserted (or element present)
    // and bool indicates the success/failure of insertion
    setOne.erase(3); // erase 3 from the set

    if (setOne.find(2) == setOne.end()) {
        // find returns the iterator to the element of end() if it doesn't find it
        // element doesn't exist
        cout << "Couldn't find 2\n";
    } else {
        cout << "Found 2!\n";
    }

    // we don't know in what order are we going to get the elements
    // 3 will be iterated over only one time
    for (const int val: setOne) {
        cout << val << endl;
    }

    // no two elements in a set can be equal
    // we can add or remove elements from a set, but we can't change the values of existing elements.
    // elements in a set are sorted following a specific strict weak ordering.
    // by default, c++ sets are sorted in ascending order, but we have the option to change that
    // elements of a set are referenced by using their key, not by their position in the container

    // to get the elements of a set sorted in descending order:
    set<int, greater<int> > setTwo = {9, 10, 4, 8, 2, 5, 0, 12};

    for (int val: setTwo) {
        cout << val << endl;
    }

    // this clears all the elements from the set
    setOne.clear();

    cout << setOne.empty() << endl; // returns true if the set is empty
    cout << setTwo.size() << endl; //  returns the size of the set

    // check if an element exists in a set
    if (setTwo.count(10) == 1) {
        // 10 exists
        cout << "10 exists\n";
    } else {
        cout << "10 does not exist\n";
    }

    /*
     *An associative container that contains a sorted set of unique objects of type Key
     *A user provided Compare can be supplied to change the ordering (sorting)
     *Search, removal, and insertion times are logarithmic
     *Usually implemented as Red-Black trees
     * template <
     * class Key,
     * class Compare = std::less<Key>,
     * class Allocator = std::allocator<key>,
     * > class set;
     */

    auto itr = setTwo.upper_bound(10); // returns the iterator to the first element greater than 10
    auto itr_two = setTwo.lower_bound(4); // returns the iterator to the first element greater than or equal to 4

    cout << *itr << endl;
    cout << *itr_two << endl;

    // insert all elements of a vector into a set
    vector<int> arr = {1, 6, 144, 69, 100};
    setOne.insert(arr.begin(), arr.end()); // inserts from beginning to end - 1; returns nothing

    setOne.erase(setOne.begin());
    // erases the first element; returns the iterator to the element following the deleted element
    setOne.erase(setOne.begin(), setOne.end()); // erases all the elements in the set from beginning to end - 1;
    // returns iterator following the last element removed

    setTwo.erase(10); // removed element 10 if present; returns the number of elements removed

    // unordered sets

    /*
     *An associative container that contains a set of unique objects of type Key
     *Search, removal, and insertion times are constant
     *Implemented as Hash Table.
     *template<
     *class Key,
     *class Hash = std::hash<Key>,
     *class KeyEqual = std::equal_to<Key>,
     *class Allocator = std:allocator<Key>,
     *> class unordered_set;
     */

    return EXIT_SUCCESS;
}
