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

// pre, in, post
vector<int> preorder(Node *root) {
    vector<int> pre;
    stack<Node *> st;

    // root, left, right
    st.push(root);
    while (!st.empty()) {
        Node *node = st.top();
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
    vector<int> in;
    stack<Node *> st;

    // left, root, right
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
    vector<int> post;
    stack<Node *> stOne, stTwo;

    // left, right, root
    // first, we do reverse postorder root -> right -> left
    // and then reverse this
    stOne.push(root);
    while (!stOne.empty()) {
        const auto node = stOne.top();
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

    vector<int> pre, in, post;
    stack<pair<Node *, int>> st;

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