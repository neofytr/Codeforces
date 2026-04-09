#include <bits/stdc++.h>
using namespace std;

#define int long long

class SegmentTree {
public:
    int len;
    vector<pair<int, int>> values;

    void build(int idx, int l, int r, vector<int> &arr) {
        if (l == r) {
            values[idx] = {arr[l], 1};
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * idx, l, m, arr);
        build(2 * idx + 1, m + 1, r, arr);

        int left = values[2 * idx].first, leftcnt = values[2 * idx].second;
        int right = values[2 * idx + 1].first, rightcnt = values[2 * idx + 1].second;

        if (left < right) values[idx] = {left, leftcnt};
        else if (left > right) values[idx] = {right, rightcnt};
        else values[idx] = {left, rightcnt + leftcnt};
    }

    void update(int i, int v, int idx, int l, int r) {
        if (l == r) {
            values[idx] = {v, 1};
            return;
        }

        if (i < l || i > r)
            return;

        int m = l + (r - l) / 2;
        if (i <= m)
            update(i, v, 2 * idx, l, m);
        else 
            update(i, v, 2 * idx + 1, m + 1, r);

        int left = values[2 * idx].first, leftcnt = values[2 * idx].second;
        int right = values[2 * idx + 1].first, rightcnt = values[2 * idx + 1].second;

        if (left < right) values[idx] = {left, leftcnt};
        else if (left > right) values[idx] = {right, rightcnt};
        else values[idx] = {left, rightcnt + leftcnt};
    }

    pair<int, int> get(int l, int r, int rangeL, int rangeR, int idx) {
        if (r < rangeL || rangeR < l) return {LLONG_MAX, 1};
        if (l >= rangeL && r <= rangeR) return values[idx];

        if (l == r) return values[idx];

        int m = l + (r - l) / 2;
        auto left = get(l, m, rangeL, rangeR, 2 * idx);
        auto right = get(m + 1, r, rangeL, rangeR, 2 * idx + 1);

        if (left.first < right.first) return left;
        if (right.first < left.first) return right;
        return {left.first, left.second + right.second};
    }

    SegmentTree(int n, vector<int> &arr) {
        values.resize(4 * n + 1);
        len = n;

        build(1, 1, len, arr);
    }

    void set(int i, int v) {
        update(i, v, 1, 1, len);
    }

    pair<int, int> query(int l, int r) {
        return get(1, len, l, r, 1);
    }
};

int32_t main() {
    int n, m;
    cin >> n >> m;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    SegmentTree s(n, arr);

    // for (int r = 1; r <= 4 * n; r++)
    //     cout << r << " " << s.values[r].first << " " << s.values[r].second << endl;

    while (m--) {
        int type; cin >> type;
        if (type == 1) {
            int i, v;
            cin >> i >> v;

            s.set(i + 1, v);
        } else {
            int l, r;
            cin >> l >> r;

            auto [m, cnt] = s.query(l + 1, r);
            cout << m << " " << cnt << endl;
        }
    }

    return 0;
}