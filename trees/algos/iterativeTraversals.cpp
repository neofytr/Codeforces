#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    struct Node *left, *right;
    int data;
    explicit Node(const int data) {
        this->data = data;
        left = right = nullptr;
    }
};

struct Node *buildTree(const int node, const vector<vector<int>> &children) {
    const auto n = new Node(node);
    const vector<int> &c = children[node];
    const int size = (int)c.size();
    if (size >= 1)
        n->left = buildTree(c[0], children);
    if (size >= 2)
        n->right = buildTree(c[1], children);
    return n;
}

vector<int> preorder(struct Node *root) {
    // root, left, right
    vector<int> pre;
    stack<struct Node *> st;

    st.push(root);
    while (!st.empty()) {
        const auto node = st.top();
        st.pop();
        if (!node)
            continue;

        pre.push_back(node->data);
        st.push(node->right);
        st.push(node->left);
    }
    return pre;
}

vector<int> inorder(struct Node *root) {
    // left, root, right
    vector<int> in;
    stack<struct Node *> st;

    struct Node *node = root;
    while (node || !st.empty()) {
        while (node) {
            st.push(node);
            node = node->left;
        }
        node = st.top();
        st.pop();
        in.push_back(node->data);
        node = node->right;
    }
    return in;
}

vector<int> postorder(struct Node *root) {
    // left, right, root
    stack<struct Node *> stOne, stTwo;
    vector<int> post;

    stOne.push(root);
    while (!stOne.empty()) {
        struct Node *node = stOne.top();
        stOne.pop();
        if (!node)
            continue;
        post.push_back(node->data);
        stTwo.push(node->left);
        stTwo.push(node->right);
    }
    return post;
}

int32_t main() {
    int n, rt;
    cin >> n >> rt;

    int u, v;
    vector<vector<int>> children;
    for (int r = 1; r <= n - 1; r++)
        cin >> u >> v, children[u].push_back(v);

    struct Node *root = buildTree(rt, children);
}