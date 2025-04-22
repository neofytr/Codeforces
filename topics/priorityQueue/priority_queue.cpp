#include <bits/stdc++.h>
using namespace std;

int main() {
    // the stl priority_queue provides the functionality of a priority queue data structure

    // a priority queue is a special type of queue in which each element is associated with a
    // priority value and elements are served in descending order of priority

    // provides constant time lookup of the element with the highest priority
    // at the expense of logarithmic insertion and deletion

    // by default, the stl priority queue gives the largest element the highest priority
    // thus, by default, the stl priority queue is a max heap

    priority_queue<int> line;

    line.push(10); // insert the element into the queue
    line.push(20);

    cout << line.top() << endl; // gets the element with the highest priority from the queue
    line.pop(); // removes the element with the highest priority from the queue

    cout << line.size() << endl; // returns the number of elements in the queue
    cout << line.empty() << endl; // return true if the queue is empty

    // to iterate over all the elements of the queue, in descending order of priority
    while (!line.empty()) {
        cout << line.top() << endl;
        line.pop();
    }

    // to create a min heap priority queue, that gives off elements in ascending order of priority
    // priority_queue<type, vector<type>, greater<type>> name;
    priority_queue<int, vector<int>, greater<> > minLine;

    // in this type of priority queue, the smallest element gets the highest priority

    // a user provided compare can be supplied to calculate the priority
    // ask chatgpt when this is required

    /*
     * template<
     *  class T,
     *  class Container = std::vector<T>,
     *  class Compare = std::less<typename Container::<value_type>
     *> class priority_queue
     */

    /* The type of the underlying container to use to store the elements must satisfy the requirements
     * of SequenceContainer, and it's iterators must satisfy the requirements of LegacyRandomAccessIterator.
     * Additionally, it must provide the following functions with the usual semantics: front(), push_back(), pop_back()
     * std::vector and std::dequeue satisfy these requirements
     */

    /* A compare type is one providing strict weak ordering
     * Compare parameter is defined such that, it returns true if its first argument comes before
     * its second argument in a weak ordering
     */

    return EXIT_SUCCESS;
}
