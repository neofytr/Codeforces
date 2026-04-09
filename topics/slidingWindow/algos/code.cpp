#include <bits/stdc++.h>
using namespace std;

#define int long long

// sliding window technique overview:
// - we are working with subarrays (continuous parts of an array).
// - a sliding window is a subarray of fixed size that moves from left to right.
// - at each step, we want to compute some property (sum, min, max, etc.) of the current window.
// - when the operation is invertible (like sum, xor), we can easily add/remove elements in O(1).
// - when it's non-invertible (like min, max, gcd), we need clever data structures to maintain the result efficiently.

// this implementation focuses on both invertible and non-invertible cases and shows how to generalize the approach.

// -------------------
// invertible operations
// -------------------

// fixed-size window sum:
// we maintain a running sum by adding the new element and removing the element that falls out of the window.
vector<int> slideSum(const vector<int> &arr, int k) {
    int n = (int)arr.size(), sum = 0;
    vector<int> ans;

    int l = 0; // left index of the window
    for (int r = 0; r < n; r++) {
        sum += arr[r];          // include arr[r] in the window
        if (r - l + 1 == k) {   // window size reached
            ans.push_back(sum); // record current sum
            sum -= arr[l];      // remove arr[l] from sum as it will slide out
            l++;                // move left pointer forward
        }
    }
    return ans;
}

// fixed-size window xor:
// similar to sum, xor can be undone by re-applying xor with the same element.
vector<int> slideXor(const vector<int> &arr, int k) {
    int n = (int)arr.size(), xr = 0;
    vector<int> ans;

    int l = 0;
    for (int r = 0; r < n; r++) {
        xr ^= arr[r];          // include arr[r] in xor
        if (r - l + 1 == k) {  // window size reached
            ans.push_back(xr); // record current xor
            xr ^= arr[l];      // remove arr[l] by re-xoring
            l++;               // move left pointer forward
        }
    }
    return ans;
}

// -------------------
// non-invertible operations
// -------------------

// for operations like min, max, gcd, lcm, bitwise or/and,
// we can't simply remove an element by undoing the operation.
// thus, we need to use data structures like multi-set or segment tree for efficient solutions (usually O(n log n)).
// or we can use more advanced structures like a queue with two stacks and aggregated information.

// -------------------
// augmented queue idea
// -------------------

// a sliding window can be thought of as a queue:
// - new elements are added to the back.
// - old elements are removed from the front.
// if we can maintain the aggregate information of the queue efficiently,
// we can compute the result for each window in O(1) or amortized O(1).

// to simulate a queue, we use two stacks (fnt, bck):
// - front stack stores elements that will be popped first.
// - back stack stores newly added elements.
// when front is empty, we move all elements from back to front in reverse order.
// this guarantees that popping and accessing the front is efficient.

// augmented queue structure with two stacks:
struct AugQueue {
  private:
    stack<int> fnt, bck; // stacks representing front and back parts of the queue

    // balance function: moves all elements from back to front
    // this happens when we need to pop or access the front but the front stack is empty
    void balance() {
        while (!bck.empty()) {
            fnt.push(bck.top());
            bck.pop();
        }
    }

  public:
    // add an element to the back
    void push(const int x) { bck.push(x); }

    // remove the front element
    void pop() {
        if (fnt.empty())
            balance();
        fnt.pop();
    }

    // access the front element
    int front() {
        if (fnt.empty())
            balance();
        return fnt.top();
    }
};

// -------------------
// aggregate min stack
// -------------------

// to maintain minimum in a stack efficiently,
// we store each element along with the minimum value up to that point.
// each time we push, we update the current minimum.

struct AggMinStack {
    stack<pair<int, int>> st; // each element is (value, min so far)

    // push operation: store the element and the updated min
    void push(const int x) {
        int mini = st.empty() ? x : min(x, st.top().second);
        st.push({x, mini});
    }

    // remove the top element
    void pop() { st.pop(); }

    // check if stack is empty
    bool empty() const { return st.empty(); }

    // access the top element's value
    int top() const { return st.top().first; }

    // get the current minimum value in the stack
    int getMin() const { return st.top().second; }
};

// -------------------
// augmented min queue
// -------------------

// combining two aggregated min stacks to maintain minimum for the entire queue
// - when we pop from the front, we rely on fnt
// - when we push to the back, we rely on bck
// - when one is empty, we only consider the other
// - when both have elements, the current min is the smaller of the two

struct AugMinQueue {
  private:
    AggMinStack fnt, bck;

    // balance: move elements from bck to fnt if fnt is empty
    void balance() {
        while (!bck.empty()) {
            int val = bck.top().first;
            bck.pop();
            fnt.push(val);
        }
    }

  public:
    // add element to the back
    void push(const int x) { bck.push(x); }

    // remove element from the front
    void pop() {
        if (fnt.empty())
            balance();
        fnt.pop();
    }

    // get the front element
    int front() {
        if (fnt.empty())
            balance();
        return fnt.top();
    }

    // get the minimum element in the queue
    int getMin() {
        if (fnt.empty())
            return bck.getMin();
        if (bck.empty())
            return fnt.getMin();
        return min(fnt.getMin(), bck.getMin());
    }
};

// -------------------
// generalization notes
// -------------------

// this structure can be adapted to other aggregates:
// - max: store max so far instead of min in AggMinStack -> AggMaxStack
// - gcd: store gcd so far, requires gcd operation
// - lcm: store lcm so far, requires lcm operation
// - bitwise or/and: store or/and so far

// key points:
// - when an operation is invertible (sum, xor), we can undo an operation easily.
// - when not invertible, we need auxiliary data structures to recompute aggregates efficiently.
// - two-stack queues help us simulate queue operations and maintain additional info in amortized constant time.
// - storing aggregated info in stacks is a powerful pattern and can be used in many sliding window problems.

int32_t main() {
    // In general, it is not required for the subarray to have constant size as long as both the left and
    // right endpoints of the subarray only move to the right
}
