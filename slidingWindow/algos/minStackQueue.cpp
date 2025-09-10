#include <bits/stdc++.h>
using namespace std;

/*
 * Stack Modification
 * We want to modify the stack data structure in such a way, that it is possible to find the smallest
 * element in the stack in constant time, while maintaining the same asymptotic behavior for adding and removing
 * elements from the stack
 *
 * To do this, we will not only store the elements in the stack, but we will store them in pairs: the element itself
 * and the minimum in the stack starting from this element and below
 *
 * It is clear that finding the minimum in the whole stack consists only of looking at the value stack.top().second()
 * It is also obvious that adding or removing an element to the stack can be done in constant time
 */

struct MinStack {
  private:
    stack<pair<int, int>> st;

  public:
    void push(const int x) {
        if (st.empty())
            st.push({x, x});
        else {
            auto [val, mini] = st.top();
            st.push({x, min(mini, x)});
        }
    }
    void pop() { st.pop(); }
    bool empty() const { return st.empty(); }
    int top() const { return st.top().first; }
    int getMin() const { return st.top().second; }
};

/*
 * queue modification – method 1: efficient minimum tracking with a monotonic queue
 *
 * in this approach, we want to implement a queue that supports two operations:
 * 1. insert an element at the end (enqueue).
 * 2. remove an element from the front (dequeue).
 *
 * unlike a normal queue that stores all elements, this modified queue is optimized for
 * tracking the minimum efficiently. the main idea is to only store elements that are
 * necessary for determining the current minimum.
 *
 * key concept:
 * we maintain the queue in non-decreasing order, meaning:
 * - the smallest element is always at the front.
 * - elements are stored in such a way that the minimum can be retrieved in constant time.
 * this structure is often called a monotonic queue.
 *
 * how elements are added (enqueue):
 * when adding a new element, we don’t blindly append it to the end of the queue.
 * instead, we first remove all elements from the back that are larger than the new element.
 *
 * why remove larger elements?
 * - any element larger than the incoming element cannot be the minimum at this point or later.
 * - keeping such elements would waste space and complicate the process of finding the minimum.
 *
 * procedure:
 * 1. while the queue is not empty and the last element is larger than the new element:
 *    - remove the last element from the queue.
 * 2. add the new element to the back of the queue.
 *
 * this ensures that:
 * - the queue remains in non-decreasing order.
 * - the smallest element is always at the front.
 * - we only store elements that can potentially be the minimum in future operations.
 *
 * how elements are removed (dequeue):
 * since we remove some elements while adding new ones, the original queue’s order is no longer fully preserved.
 *
 * problem:
 * - the element at the front of the original queue may have already been removed when a smaller element was added.
 * - we need to check whether the element being removed from the original queue is still at the front of the modified queue.
 *
 * procedure:
 * 1. when removing an element from the front:
 *    - if the value at the front of the queue matches the element to be removed, remove it.
 *    - if it does not match, it means the element was already discarded earlier and no removal is needed.
 *
 * this check ensures that the queue remains correct while efficiently tracking the minimum without storing all elements.
 *
 * advantages:
 * - space efficiency: only elements that can be the minimum are stored.
 * - time efficiency: both insertion and removal are fast since unnecessary elements are removed early.
 * - always ready: the current minimum is always at the front of the queue.
 *
 * important notes:
 * - this method does not store every element that has ever been added to the queue.
 * - elements are removed based on their value and their potential to be the minimum, not strictly on insertion order.
 * - this method is especially useful in problems like sliding window minimum or maximum, where only relevant elements matter.
 *
 * it is clear that on average, all these operations only take O(1) time (because every element can only be pushed and popped once)
 */

struct MinQueueOne {
  private:
    deque<int> que;

  public:
    void push(const int x) {
        while (!que.empty() && que.back() > x)
            que.pop_back();
        que.push_back(x);
    }
    void pop(const int x) {
        if (!que.empty() && que.front() == x)
            que.pop_front();
    }
    int getMin() const { return que.front(); }
};

/*
 * queue modification – method 2: tracking minimum without knowing the exact element
 *
 * this is an improved version of method 1, designed to handle cases where we want to remove elements
 * from the front of the queue without needing to know which exact element it is.
 * in method 1, we compared the value at the front with the element to be removed,
 * but that approach is not always practical because we might not have access to the value.
 * here, we solve this by associating each element with its insertion index.
 *
 * key idea:
 * we store each element as a pair containing its value and its index (i.e., the order in which it was added).
 * by tracking how many elements have been added and removed, we can always determine when to remove the front element.
 *
 * why this approach works:
 * - elements are added with an increasing index using cntAdded.
 * - when elements are removed from the front, we only need to compare the index of the front element with cntRemoved.
 * - if they are equal, it means the element at the front is exactly the one that should be removed at this time.
 *   otherwise, it means the element was already discarded while adding a smaller element, so we don't need to remove it.
 *
 * how it always removes the correct element:
 * - the actual queue we want to model operates on all elements in order.
 * - however, in order to optimize, we only keep elements that could potentially be the minimum in future operations.
 * - when adding a new element, we remove all elements at the back that are larger than it because they can never be the minimum later.
 *   this ensures that the queue only stores candidates for the minimum in future steps.
 * - when removing an element, we only need to ensure that the element being removed is the one that is currently at the front.
 *   because we always track how many elements have been removed (cntRemoved), the front's index can be compared to it.
 *   if they match, it means this is the element that should be removed.
 *   if they don't match, the element was already discarded, and removing it again would be incorrect.
 *
 * why index == cntRemoved is sufficient and correct:
 * - cntRemoved tracks the exact number of elements that have been removed from the logical queue.
 * - every element is pushed with its corresponding cntAdded value at that time.
 * - the first element in the queue is always the earliest element that has not yet been removed.
 * - if its index matches cntRemoved, it means that it is the next element to be removed according to queue semantics.
 * - if the index is greater, it means that element was already removed while processing previous additions,
 *   and hence we should not remove it again.
 *
 * additional details:
 * - cntAdded increments each time a new element is pushed to ensure every element has a unique index.
 * - cntRemoved increments each time a pop operation is requested, whether an actual element is removed.
 * - this distinction allows the queue to handle cases where elements are skipped during addition without affecting correctness.
 * - the pair (value, index) serves as metadata to efficiently manage queue operations without needing to store or pass around the full dataset.
 *
 * benefits of this approach:
 * - efficient: both adding and removing elements remain fast operations.
 * - space optimized: only necessary elements are stored to track the minimum.
 * - accurate: elements are removed in the correct order based on their original position.
 * - avoids ambiguity: since each element has a unique index, no confusion arises when deciding which element to remove.
 * - robust: even if elements are discarded during addition, the queue maintains correctness by tracking order with cntAdded and cntRemoved.
 *
 * practical applications:
 * - this method is especially useful in problems like sliding window minimum or maximum,
 *   where we need to track the minimum efficiently over a moving window.
 * - by associating elements with indices, we can ensure operations reflect the correct queue behavior while optimizing performance.
 */

struct MinQueueTwo {
  private:
    deque<pair<int, int>> que;
    int cntAdded = 0, cntRemoved = 0;

  public:
    int minimum() const { return que.front().first; }
    void push(const int x) {
        while (!que.empty() && que.back().first > x)
            que.pop_back();
        que.push_back({x, cntAdded++});
    }
    void pop() {
        if (!que.empty() && que.front().second == cntRemoved)
            que.pop_back();
        cntRemoved++;
    }
};

/*
 * the third method for modifying a queue is to use two min stacks
 *
 * the idea is to simulate a queue using two stacks that are able to track the minimum element efficiently.
 * this approach combines the benefits of a stack that maintains the minimum element with the queue's fifo behavior.
 * by cleverly transferring elements between the two stacks, we ensure that all operations – push, pop, and getMin – are correct and efficient.
 *
 * how it works:
 * - we use two stacks, named front and back.
 * - both are special stacks (min stacks) that can track the minimum element at any time.
 * - elements are always pushed into the back stack.
 * - when popping elements from the queue, we pop from the front stack.
 * - if the front stack is empty when a pop is requested, we transfer all elements from the back stack to the front stack.
 *   this process is called balancing.
 * - while transferring, we preserve the order of elements by popping from back and pushing into front.
 *   this ensures that the first-in element becomes available at the top of the front stack for popping.
 *
 * why this approach maintains correctness:
 * - push operations always append elements to the back, ensuring elements are processed in order.
 * - the balance function guarantees that when the front stack is empty, it is refilled with elements from the back in reverse order,
 *   thus restoring the original queue order.
 * - pop operations remove elements from the front, just as a normal queue would.
 * - getMin retrieves the smallest element from either stack because any element currently in the queue must exist in either the front or back stack.
 *   we simply compare the minimums of both stacks to find the overall minimum.
 *
 * why balance is necessary:
 * - the queue must support removing elements from the front.
 * - if the front stack is empty, we need to move elements from the back to the front to maintain the correct order.
 * - transferring all elements at once ensures that the sequence of elements remains intact and we don't lose any data.
 * - we only perform the transfer when necessary (i.e., when the front is empty), keeping operations efficient.
 *
 * why getMin always gives the correct result:
 * - each stack separately keeps track of its own minimum element.
 * - because every element in the queue resides in either the front or back stack,
 *   the overall minimum must be the smallest of the two stacks' minimums.
 * - when one stack is empty, getMin simply returns the minimum of the other stack.
 * - this ensures that even during transfers, or when one stack is temporarily empty, the correct minimum is always accessible.
 *
 * additional details:
 * - transferring elements from back to front may seem expensive, but it happens only when necessary,
 *   and amortized analysis shows that each element is moved at most once, so the overall cost is low.
 * - this method allows both push and pop to run efficiently in practice while maintaining accurate minimum tracking.
 * - the queue abstraction is preserved while leveraging stack properties for optimization.
 *
 * practical applications:
 * - this approach is widely used in problems like sliding window minimum or maximum,
 *   where maintaining the minimum efficiently during dynamic insertion and removal is essential.
 * - by combining two stacks, we create a robust and efficient queue implementation without needing complex data structures.
 */

struct MinQueue {
  private:
    MinStack front, back;
    void balance() {
        while (!back.empty())
            front.push(back.top()), back.pop();
    }

  public:
    void push(const int x) { back.push(x); }
    void pop() {
        if (front.empty())
            balance();
        if (front.empty())
            return;
        front.pop();
    }
    int getMin() const {
        if (front.empty() && back.empty())
            return -1;
        if (front.empty())
            return back.getMin();
        if (back.empty())
            return front.getMin();
        return min(front.getMin(), back.getMin());
    }
};