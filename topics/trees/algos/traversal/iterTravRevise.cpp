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

vector<int> preorder(Node *root) {
    // root, left, right
    vector<int> pre;
    stack<Node *> st;

    st.push(root);
    while (!st.empty()) {
        auto node = st.top();
        st.pop();
        if (!node)
            continue;
        st.push(node->right);
        st.push(node->left);
        pre.push_back(node->data);
    }
    return pre;
}

vector<int> inorder(Node *root) {
    // left, root, right
    vector<int> in;
    stack<Node *> st;

    Node *node = root;
    while (node || !st.empty()) {
        while (node) {
            st.push(node);
            node = node->left;
        }
        node = st.top(), st.pop();
        in.push_back(node->data);
        node = node->right;
    }
    return in;
}

vector<int> postorder(Node *root) {
    // left, right, root
    vector<int> post;
    stack<Node *> stOne, stTwo;

    // do root, right, left, then reverse
    stOne.push(root);
    while (!stOne.empty()) {
        auto node = stOne.top();
        stOne.pop();
        if (!node)
            continue;
        stOne.push(node->left);
        stOne.push(node->right);
        stTwo.push(node);
    }
    while (!stTwo.empty())
        post.push_back(stTwo.top()->data), stTwo.pop();
    return post;
}

int32_t main() {
    int n, rt;
    cin >> n >> rt;

    int u, v;
    vector<vector<int>> children(n);
    for (int r = 1; r <= n - 1; r++)
        cin >> u >> v, children[u].push_back(v);

    Node *root = buildTree(rt, children);
}