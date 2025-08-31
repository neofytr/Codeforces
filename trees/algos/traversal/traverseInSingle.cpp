#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    Node *left, *right;
    int data;
    explicit Node(const int data) {
        this->data = data;
        left = right = nullptr;
    }
};

Node *buildTree(const int node, const vector<vector<int>> &children) {
    const auto n = new Node(node);
    const vector<int> &child = children[node];
    const int size = (int)child.size();
    if (size >= 1)
        n->left = buildTree(child[0], children);
    if (size >= 2)
        n->right = buildTree(child[1], children);
    return n;
}

void traverse(const Node *node, vector<int> &pre, vector<int> &in, vector<int> &post) {
    if (!node)
        return;
    pre.push_back(node->data);
    traverse(node->left, pre, in, post);
    in.push_back(node->data);
    traverse(node->right, pre, in, post);
    post.push_back(node->data);
}

int32_t main() {
    int n, rt;
    cin >> n >> rt;

    int u, v;
    vector<vector<int>> children(n);
    for (int r = 1; r <= n - 1; r++)
        cin >> u >> v, children[u].push_back(v);

    Node *root = buildTree(rt, children);

    stack<pair<Node *, int>> st;
    vector<int> pre, in, post;

    st.push({root, 1});
    while (!st.empty()) {
        auto [node, num] = st.top();
        st.pop();

        if (num == 1) {
            pre.push_back(node->data);
            st.push({node, num + 1});
            if (node->left)
                st.push({node->left, 1});
        }
        if (num == 2) {
            in.push_back(node->data);
            st.push({node, num + 1});
            if (node->right)
                st.push({node->right, 1});
        }
        if (num == 3)
            post.push_back(node->data);
    }
    return EXIT_SUCCESS;
}