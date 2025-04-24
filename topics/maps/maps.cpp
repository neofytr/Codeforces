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

    // maps are associative containers that store data in the form of key value pairs sorted on the basis of keys
    // no two mapped values can have the same keys. by default, it stores the data in ascending order of keys

    // if the element with the given already exists, the insert() method skips the insertion but
    // [] operator updates the associated value to the new value

    // map elements can be accessed by using the corresponding key inside operator[]
    // if the key exists, it will return the associated value but if the key doesn't exist, it will
    // create a new element with the given key and the default value (of the value type for the map)
    // to avoid this, we can use .at() which returns error if key not present

    // the iterator of a map stores pointer to pairs (key, value)

    // unordered maps are hash tables
    // their functions behave the same way as maps
    // however, they don't store their elements in any particular order

    return EXIT_SUCCESS;
}
