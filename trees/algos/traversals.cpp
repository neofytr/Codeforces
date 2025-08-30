#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    struct Node *left;
    struct Node *right;
    int data;

    explicit Node(const int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

Node *buildTree(const int nd, const vector<vector<int>> &children) {
    const auto node = new Node(nd);
    if (children[nd].size() >= 1)
        node->left = buildTree(children[nd][0], children);
    if (children[nd].size() >= 2)
        node->right = buildTree(children[nd][1], children);
    return node;
}

void inorder(const Node *node) {
    if (!node)
        return;
    // left, root, right

    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

void preorder(const Node *node) {
    if (!node)
        return;

    // root, left, right
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void postorder(const Node *node) {
    if (!node)
        return;

    // left, right, root
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

int32_t main() {
    // 0-indexed nodes
    // guaranteed to be a binary tree

    int n, rt;
    cin >> n >> rt;

    int u, v;
    vector<vector<int>> children(n);
    for (int r = 1; r <= n - 1; r++) {
        cin >> u >> v;
        children[u].push_back(v);
    }

    struct Node *root = buildTree(rt, children);
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    postorder(root);
    cout << endl;

    // BFS
    vector<vector<int>> ans;
    queue<struct Node *> q;

    if (root)
        q.push(root);
    while (!q.empty()) {
        int size = (int)q.size();
        vector<int> currLevel;
        while (size--) {
            struct Node *node = q.front();
            q.pop();

            currLevel.push_back(node->data);
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
        ans.push_back(currLevel);
    }
    return EXIT_SUCCESS;
}