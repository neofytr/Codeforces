#include <bits/stdc++.h>
using namespace std;

int main()
{
    stack<int> intStack;

    intStack.push(10); // pushes 10 onto the stack
    cout << intStack.top() << endl; // returns the top element of the stack
    cout << intStack.size() << endl; // returns the size of the stack
    cout << intStack.empty() << endl; // returns true if the stack is empty
    intStack.pop(); // pops the topmost element of the stack

    return EXIT_SUCCESS;
}
