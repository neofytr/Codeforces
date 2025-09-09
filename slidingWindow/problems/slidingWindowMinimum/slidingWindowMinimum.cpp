#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: slidingWindowMinimum
// URL: Not provided
// Difficulty: Unknown
// Tags:
// Strategy:

struct Stack {
    stack<pair<int, int>> st;
    void push(const int x) {
        if (st.empty())
            st.push({x, x});
        else {
            auto [val, mini] = st.top();
            mini = min(mini, x);
            st.push({x, mini});
        }
    }
    void pop() { st.pop(); }
    bool empty() { return st.empty(); }
    int top() const { return st.top().first; }
    int getMin() const { return st.top().second; }
};

struct Queue {
    Stack fnt, bck;
    void balance() {
        while (!bck.empty())
            fnt.push(bck.top()), bck.pop();
    }
    void push(const int x) { bck.push(x); }
    void pop() {
        if (fnt.empty())
            balance();
        fnt.pop();
    }
    int getMin() {
        assert(!fnt.empty() || !bck.empty()); // ensure the queue is not empty
        if (fnt.empty())
            return bck.getMin();
        if (bck.empty())
            return fnt.getMin();
        return min(fnt.getMin(), bck.getMin());
    }
};

int32_t main() {
    int n, k;
    cin >> n >> k;

    int x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<int> arr(n);
    arr[0] = x;

    int l = 0;
    int xr = 0;
    Queue que;
    for (int r = 0; r < n; r++) {
        if (r > 0)
            arr[r] = (a * arr[r - 1] + b) % c;
        que.push(arr[r]); // include into the window
        if (r - l + 1 == k)
            xr ^= que.getMin(), que.pop(), l++;
    }
    cout << xr << endl;
    return 0;
}