#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int INF = 1e9;

vector<int> seg_tree;
int seg_n;

void build(int n) {
    seg_n = n;
    seg_tree.assign(4 * seg_n, INF);
}

void update(int idx, int val, int node, int start, int end) {
    if (start == end) {
        seg_tree[node] = min(seg_tree[node], val);
        return;
    }
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid) {
        update(idx, val, 2 * node, start, mid);
    } else {
        update(idx, val, 2 * node + 1, mid + 1, end);
    }
    seg_tree[node] = min(seg_tree[2 * node], seg_tree[2 * node + 1]);
}

int query(int l, int r, int node, int start, int end) {
    if (r < start || end < l || l > r) {
        return INF;
    }
    if (l <= start && end <= r) {
        return seg_tree[node];
    }
    int mid = (start + end) / 2;
    return min(query(l, r, 2 * node, start, mid), query(l, r, 2 * node + 1, mid + 1, end));
}

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    long long total_subarrays = (long long)n * (n + 1) / 2;

    long long increasing_subarrays = 0;
    int current_block_len = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && p[i] > p[i - 1]) {
            current_block_len++;
        } else {
            increasing_subarrays += (long long)current_block_len * (current_block_len + 1) / 2;
            current_block_len = 1;
        }
    }
    increasing_subarrays += (long long)current_block_len * (current_block_len + 1) / 2;
    long long num_lds_ge_2 = total_subarrays - increasing_subarrays;

    vector<int> nse(n);
    stack<int> st;
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && p[st.top()] >= p[i]) {
            st.pop();
        }
        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    build(n + 1);
    vector<int> r_l(n + 1, n);
    for (int l = n - 1; l >= 0; --l) {
        int min_k = query(1, p[l] - 1, 1, 1, n);
        r_l[l] = min(r_l[l + 1], min_k);
        update(p[l], nse[l], 1, 1, n);
    }

    long long num_lds_ge_3 = 0;
    for (int l = 0; l < n; ++l) {
        if (r_l[l] < n) {
            num_lds_ge_3 += (n - r_l[l]);
        }
    }

    long long total_sum = total_subarrays + num_lds_ge_2 + num_lds_ge_3;
    cout << total_sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}