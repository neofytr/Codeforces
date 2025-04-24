#include <bits/stdc++.h>
using namespace std;

// use this hash function when using unordered maps
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t fixed_random = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + fixed_random);
    }
};


int main() {
    // map
    /*
     *an associative container that contains key-value pairs with unique keys (sorted)
     *a user-provided compare can be supplied to change the ordering(sorting)
     *search, removal, and insertion times are logarithmic
     *usually implemented as rb trees
     *template<
     *class key,
     *class t,
     *class compare = std::less<key>,
     *class allocator = std::allocator<std::pair<const key, t>>,
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

    // itr++ is allowed but not itr + 1, + 2, etc.
    // similar for --itr

    return exit_success;
}
