#include <bits/stdc++.h>
using namespace std;

int main() {
    // set is an unordered collection of unique elements
    // used when we simply care about whether an element exists or not, regardless of its order and frequency
    // finding whether an element exists are not in a set happens in log(n)

    set<int> setOne = {1, 2, 3, 3}; // initialize the set; the duplicate will be ignored

    setOne.insert(10); // 10 has been inserted
    setOne.erase(3); // erase 3 from the set

    if (setOne.find(2) == setOne.end()) {
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
}
