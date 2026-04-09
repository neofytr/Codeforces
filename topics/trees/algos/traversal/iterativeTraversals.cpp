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

struct Node *buildTree(const int node, vector<vector<int>> &children) {
    const auto n = new Node(node);
    const vector<int> &c = children[node];
    const int size = (int)c.size();
    if (size >= 1)
        n->left = buildTree(c[0], children);
    if (size >= 2)
        n->right = buildTree(c[1], children);
    return n;
}

vector<int> inorder(struct Node *root) {
    // left, root, right
    vector<int> in;
    stack<struct Node *> st;

    // keep going left, pushing nodes; when you hit null, pop, visit, and then go right
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

    // first stack does root -> right -> left (like reverse preorder)
    // the second stack reverses it -> gives left -> right -> root
    stOne.push(root);
    while (!stOne.empty()) {
        struct Node *node = stOne.top();
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

vector<int> postorderOne(struct Node *root) {
    // keep track of lastVisited to know if you've processed the right child already
    // left, right, root

    vector<int> post;
    stack<struct Node *> st;
    struct Node *curr = root, *lastVisited = nullptr;
    while (curr || !st.empty()) {
        if (curr) {
            st.push(curr);
            curr = curr->left;
        } else {
            struct Node *peek = st.top();
            if (peek->right && lastVisited != peek->right)
                curr = peek->right;
            else {
                post.push_back(peek->data);
                lastVisited = peek;
                st.pop();
            }
        }
    }
    return post;
}

vector<int> preorder(struct Node *root) {
    // root, left, right
    vector<int> pre;
    stack<struct Node *> st;

    // push right child, then left child, so left is processed first
    st.push(root);
    while (!st.empty()) {
        auto node = st.top();
        st.pop();
        if (!node)
            continue;
        pre.push_back(node->data);
        st.push(node->right);
        st.push(node->left);
    }
    return pre;
}

int32_t main() {
    int n, rt;
    cin >> n >> rt;

    int u, v;
    vector<vector<int>> children(n);
    for (int r = 1; r <= n - 1; r++)
        cin >> u >> v, children[u].push_back(v);

    struct Node *root = buildTree(rt, children);
}