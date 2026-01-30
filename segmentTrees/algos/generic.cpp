// 1-indexed Generic Segment Tree
template<typename T>
class SegmentTree {
private:
    vector<T> tree;
    int n;
    T identity;
    function<T(T, T)> combine;
    
    void build(int node, int left, int right, vector<T>& arr) {
        if (left == right) {
            tree[node] = arr[left];
            return;
        }
        
        int mid = left + (right - left) / 2;
        build(2 * node, left, mid, arr);
        build(2 * node + 1, mid + 1, right, arr);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
    
    T query(int node, int left, int right, int queryLeft, int queryRight) {
        if (queryRight < left || right < queryLeft) 
            return identity;
        
        
        if (queryLeft <= left && right <= queryRight) 
            return tree[node];
        
        
        int mid = left + (right - left) / 2;
        T leftResult = query(2 * node, left, mid, queryLeft, queryRight);
        T rightResult = query(2 * node + 1, mid + 1, right, queryLeft, queryRight);
        return combine(leftResult, rightResult);
    }
    
    void update(int node, int left, int right, int pos, T val) {
        if (left == right) {
            tree[node] = val;
            return;
        }
        
        int mid = left + (right - left) / 2;
        if (pos <= mid) 
            update(2 * node, left, mid, pos, val);
        else 
            update(2 * node + 1, mid + 1, right, pos, val);
        
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
    
public:
    // constructor: size, input array, combine function, identity element
    SegmentTree(int size, vector<T>& input, function<T(T, T)> op, T id) 
        : n(size), combine(op), identity(id) {
        // the number of nodes in a segment tree with array length = 2^k for some k >= 1 is 2^(k + 1) - 1
        tree.resize(4 * n + 1, identity); // 4 * n + 1 >= 2 * next_power_of_two(n) - 1
        build(1, 1, n, input);
    }
    
    // range query [l, r]
    T query(int l, int r) {
        return query(1, 1, n, l, r);
    }
    
    // point update: set arr[idx] = val
    void set(int idx, T val) {
        update(1, 1, n, idx, val);
    }
};