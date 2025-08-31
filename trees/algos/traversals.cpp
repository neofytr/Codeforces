#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    struct Node *left;
    struct Node *right;
    int data;

    explicit Node(const int data) {
        this->data = data;
        left = right = nullptr;
    }
};

struct Node *buildTree(const int node, const vector<vector<int>> &children) {
    const auto newNode = new Node(node); // the data of the new node is the node index itself
    const vector<int> &child = children[node];
    if (child.size() >= 1)
        newNode->left = buildTree(child[0], children);
    if (child.size() >= 2)
        newNode->right = buildTree(child[1], children);
    return newNode;
}

void postorder(const struct Node *node) {
    if (!node)
        return;

    // left, right, root
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

void preorder(const struct Node *node) {
    if (!node)
        return;

    // root, left, right
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void inorder(const struct Node *node) {
    if (!node)
        return;

    // left, root, right
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
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

    // BFS
    queue<struct Node *> que;
    vector<vector<int>> ans;

    if (root)
        que.push(root);
    while (!que.empty()) {
        int size = (int)que.size();
        vector<int> level;
        while (size--) {
            struct Node *node = que.front();
            que.pop();

            level.push_back(node->data);
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        ans.push_back(level);
    }
    return EXIT_SUCCESS;
}