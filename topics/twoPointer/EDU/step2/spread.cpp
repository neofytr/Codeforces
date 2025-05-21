#include <bits/stdc++.h>
using namespace std;

int main()
{
    // read input values
    int n;
    long long k;
    cin >> n >> k;

    // read the array of n elements
    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    // we use two sets of stacks to simulate a sliding window
    // the window is defined by indices [left, right)
    // left_stack: stores elements from the left side of the window
    // left_min: tracks the minimum element in left_stack
    // left_max: tracks the maximum element in left_stack
    // right_stack: stores elements added on the right side of the window
    // right_min: tracks the minimum element in right_stack
    // right_max: tracks the maximum element in right_stack
    // using these, we can get the current window's max and min in O(1)

    stack<long long> left_stack, left_min, left_max;
    stack<long long> right_stack, right_min, right_max;

    // initialize pointers and count of valid subarrays
    int left = 0, right = 0;
    long long count = 0;

    // move the left boundary of the window from 0 to n - 1
    while (left < n)
    {
        // expand the right boundary as far as the condition is satisfied
        while (right < n)
        {
            long long elt = arr[right];
            right_stack.push(elt); // add element to right_stack

            // maintain right max stack
            if (!right_max.empty())
                right_max.push(max(elt, right_max.top()));
            else
                right_max.push(elt);

            // maintain right min stack
            if (!right_min.empty())
                right_min.push(min(elt, right_min.top()));
            else
                right_min.push(elt);

            // calculate the total minimum and maximum of current window
            long long totmax;
            long long totmin;

            // if left stack is not empty, min is min of left and right
            if (!left_min.empty())
                totmin = min(left_min.top(), right_min.top());
            else
                totmin = right_min.top();

            // same logic for max
            if (!left_max.empty())
                totmax = max(left_max.top(), right_max.top());
            else
                totmax = right_max.top();

            // if the condition is violated, break and rollback
            if (totmax - totmin > k)
            {
                // remove the last pushed element since it broke the condition
                right_stack.pop();
                right_min.pop();
                right_max.pop();
                break;
            }

            // if valid, move right forward
            right++;
        }

        // add the number of valid subarrays starting at 'left'
        count += (right - left);

        // now we want to move the left pointer forward
        // but we can't pop from the bottom of right_stack, so we use a trick:
        // when left_stack is empty, transfer all elements from right_stack to left_stack
        // this simulates queue behavior using two stacks
        // and allows us to remove the leftmost element in O(1)

        if (left_stack.empty())
        {
            // transfer all elements from right_stack to left_stack
            while (!right_stack.empty())
            {
                long long val = right_stack.top();
                right_stack.pop();
                right_min.pop();
                right_max.pop();

                left_stack.push(val);

                // update left_max with max of current and previous top
                if (!left_max.empty())
                    left_max.push(max(val, left_max.top()));
                else
                    left_max.push(val);

                // update left_min with min of current and previous top
                if (!left_min.empty())
                    left_min.push(min(val, left_min.top()));
                else
                    left_min.push(val);
            }
        }

        // pop the leftmost element of the current window
        // this is safe now because it's on top of left_stack
        if (!left_stack.empty())
        {
            left_stack.pop();
            left_min.pop();
            left_max.pop();
        }

        // move the left boundary forward
        left++;
    }

    // output the final count of valid subarrays
    cout << count << endl;
    return 0;
}

/*

Explanation of the Two-Stack Technique:

1. we are trying to count subarrays [left, right) such that the difference between max and min in that range is ≤ k

2. calculating max/min as the window grows right is easy: we can just track max/min using a stack

3. calculating max/min as the window shrinks from the left is hard, because we can't remove arbitrary elements from a stack

4. to solve this, we simulate a queue using two stacks:

5. left_stack represents elements that have already been "pushed" and not yet popped from the left

6. right_stack contains elements being pushed from the right

7. when left_stack becomes empty, we transfer all elements from right_stack to left_stack, effectively reversing the order

8. this lets us efficiently remove from both ends and always maintain current max and min using two extra stacks per side

9. the max and min at any time are simply the max of the top of left_max and right_max (and similar for min)

this approach gives us O(n) amortized time complexity to find the total number of valid subarrays satisfying the condition.

*/