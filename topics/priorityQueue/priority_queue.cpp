#include <bits/stdc++.h>
using namespace std;

int main() {
    // the stl priority_queue provides the functionality of a priority queue data structure

    // a priority queue is a special type of queue in which each element is associated with a
    // priority value and elements are served based on their priority

    // by default, the stl priority queue gives the largest element the highest priority

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

    return EXIT_SUCCESS;
}
