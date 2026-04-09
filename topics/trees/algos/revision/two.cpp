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

Node *buildTree(const int node, const vector<int> &values, const vector<vector<int>> &children) {
    const auto n = new Node(values[node]);
    const vector<int> &c = children[node];
    const auto size = c.size();
    if (size >= 1)
        n->left = buildTree(c[0], values, children);
    if (size >= 2)
        n->right = buildTree(c[1], values, children);
    return n;
}

int maxPath = LLONG_MIN;
int mpe(const Node *node) {
    if (!node)
        return 0;

    const int left = mpe(node->left);
    const int right = mpe(node->right);
    const int mptn = node->data + max(0LL, left) + max(0LL, right);
    maxPath = max(maxPath, mptn);
    return node->data + max(0LL, max(left, right));
}

int height(const Node *node) {
    if (!node)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

int diam = LLONG_MIN;
int getHeight(const Node *node) {
    if (!node)
        return 0;

    const int left = getHeight(node->left);
    const int right = getHeight(node->right);
    diam = max(diam, left + right);
    return 1 + max(left, right);
}

// preorder, inorder, postorder
vector<int> preorder(Node *root) {
    vector<int> pre;
    stack<Node *> st;

    // root, left, right

    if (root)
        st.push(root);
    while (!st.empty()) {
        auto node = st.top();
        st.pop();

        if (node->right)
            st.push(node->right);
        if (node->left)
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
        while (node)
            st.push(node), node = node->left;
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

    // do reverse post: root -> right -> left
    // then reverse again
    if (root)
        stOne.push(root);
    while (!stOne.empty()) {
        auto node = stOne.top();
        stOne.pop();

        if (node->left)
            stOne.push(node->left);
        if (node->right)
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
    vector<int> values(n);
    vector<vector<int>> children(n);
    for (int r = 1; r <= n - 1; r++)
        cin >> u >> v, children[u].push_back(v);
    for (int &val : values)
        cin >> val;

    Node *root = buildTree(rt, values, children);

    // combined traversal
    vector<int> pre, in, post;
    stack<pair<Node *, int>> st;

    if (root)
        st.push({root, 1});
    while (!st.empty()) {
        auto [node, num] = st.top();
        st.pop();
        if (num == 1) {
            pre.push_back(node->data);
            st.push({node, num + 1});
            if (node->left)
                st.push({node->left, 1});
        } else if (num == 2) {
            in.push_back(node->data);
            st.push({node, num + 1});
            if (node->right)
                st.push({node->right, 1});
        } else
            post.push_back(node->data);
    }
    return EXIT_SUCCESS;
}