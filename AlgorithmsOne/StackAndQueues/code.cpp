#include "Stack.h"
#include "stack.h"
#include <iostream>
using namespace std;

/*
 * Fundamental Data Types
 * Value -> collection of objects
 * Operations -> insert, remove, iterate, test if empty
 * Intent is clear when we insert
 * Which item do we remove?
 *
 *    front -> [x1, x2, x3, ..., xn] <- back
 * Insertion (push) and deletion (pop) from back (top) -> stack (LIFO = "last in first out")
 * Insertion (enqueue) at the back and deletion (dequeue) at the front ->  queue (LIFO = "last in first out")
 */

/*
 * Client, Implementation and Interface
 * Separate interface and implementation
 *
 * Benefits ->
 * 1. Client can't know details of implementation -> client has many implementations from which to choose
 * 2. Implementation can't know details of client needs -> many clients can reuse the same implementation
 * 3. Design -> creates modular, reusable libraries
 * 3. Performance -> use optimized implementation where it matters
 *
 * Client -> program using operations defined in interface
 * Implementation -> actual code implementing operations
 * Interface -> description of data type, basic operations
 */

int main() {
    StackOfStrings st();

}