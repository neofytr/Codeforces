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
}
