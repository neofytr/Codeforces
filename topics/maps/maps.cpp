#include <bits/stdc++.h>
using namespace std;

int main() {
    // map
    /*
     *An associative container that contains key-value pairs with unique keys (sorted)
     *A user-provided compare can be supplied to change the ordering(sorting)
     *Search, removal, and insertion times are logarithmic
     *Usually implemented as RB trees
     *template<
     *class Key,
     *class T,
     *class Compare = std::less<Key>,
     *class Allocator = std::allocator<std::pair<const Key, T>>,
     *> class map;
     */

    // insert and erase are same as that for vector

    map<int, int> mapping = {{1, 2}, {3, 4}, {2, 3}, {4, 5}};

    // iterator will always point to the pair (key, value)

    cout << mapping.at(1) << endl; // will throw error if the key not present
    cout << mapping[5] << endl; // will return the default value of the value type if element not present

    // clear removes everything

    cout << mapping.count(5) << endl; // returns the number of times the key is present in map; which can be 0 or 1
    cout << mapping.find(1)->first << endl;
    // find returns the iterator to the pair (key, value) for the given key; or end() if the key does not exist

    // upper bound returns the first key greater than the given key, or end() if no such key
    // lower bound returns the first key greater than or equal to the given key, or end() if no such key

    // iterates in ascending order
    for (auto itr = mapping.begin(); itr != mapping.end(); ++itr) {
        cout << itr->first << endl;
    }
}
