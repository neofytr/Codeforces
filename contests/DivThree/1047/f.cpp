#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int MAX_VAL_TOTAL = 400005;
vector<int> seg_tree;

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        seg_tree[node] = val;
        return;
    }
    int mid = start + (end - start) / 2;
    if (start <= idx && idx <= mid) {
        update(2 * node, start, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, end, idx, val);
    }
    seg_tree[node] = max(seg_tree[2 * node], seg_tree[2 * node + 1]);
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l || l > r) {
        return 0;
    }
    if (l <= start && end <= r) {
        return seg_tree[node];
    }
    int mid = start + (end - start) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return max(p1, p2);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    int max_val_case = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        max_val_case = max(max_val_case, a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        max_val_case = max(max_val_case, b[i]);
    }
    vector<int> prev_ge(n + 1, 0);
    stack<int> st;
    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && a[st.top()] < a[i]) {
            st.pop();
        }
        if (!st.empty()) {
            prev_ge[i] = st.top();
        }
        st.push(i);
    }
    vector<int> prev_ge_V(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int V = max(a[i], b[i]);
        prev_ge_V[i] = query(1, 1, MAX_VAL_TOTAL, V, MAX_VAL_TOTAL);
        update(1, 1, MAX_VAL_TOTAL, a[i], i);
    }
    long long total_sum = 0;
    for (int i = 1; i <= n; ++i) {
        long long num_l = prev_ge_V[i];
        if (a[i] == b[i]) {
            num_l += (long long)i - prev_ge[i];
        }
        total_sum += (long long)(n - i + 1) * num_l;
    }
    cout << total_sum << endl;
    for (int i = 1; i <= n; ++i) {
        update(1, 1, MAX_VAL_TOTAL, a[i], 0);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    seg_tree.assign(4 * MAX_VAL_TOTAL + 4, 0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
