#include <bits/stdc++.h>
using namespace std;

int main()
{
    queue<int> qu;
    qu.push(10); // pushes an element at the back of the queue
    qu.pop();    // pops an element from the front of queue

    qu.push(100);
    qu.push(200);

    cout << qu.front() << endl; // returns the element at the front of the queue (removal end)
    cout << qu.back() << endl;  // returns the element at the back of the queue (insertion end)

    cout << qu.size() << endl;  // returns the size of the queue
    cout << qu.empty() << endl; // return true if the queue is empty

    return EXIT_SUCCESS;
}