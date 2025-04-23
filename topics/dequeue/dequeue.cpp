#include <bits/stdc++.h>
using namespace std;

int main() {
    /*
     * Dequeue
     * Sequence container, supports push/pop from both ends
     *
     * Supports random access
     *
     * Elements are not stored continuously: typical implementations use a sequence of
     * individually allocated fixed-size arrays with additional bookkeeping; this is more efficient than
     * vectors since during reallocation of vectors due to being filled to capacity, data is copied into the
     * new vector; however, if a deque is filled to capacity, a new array is allocated and bookkeeping is done for it
     * and no copying occurs
     */

    deque<int> dq = {1, 2, 3, 4, 5};

    dq[0] = 10; // random access
    cout << dq.at(3) << endl; // random access

    cout << dq.empty() << endl; // returns true if empty

    // has iterators begin(), end(), rbegin() and rend()
    // insert, erase and emplace behave as they did with vectors
    // there is push_back(), pop_back(), push_front(), pop_front(), emplace_back(), and emplace_front() which do what they usually do

    return EXIT_SUCCESS;
}
