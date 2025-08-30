#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    int data;
    Node *left;
    Node *right;
    explicit Node(const int data) : data(data), left(nullptr), right(nullptr) {}
};

Node *buildTree(const int node, vector<vector<int>> &children) {
    auto *newNode = new Node(node);
    if (children[node].size() >= 1) {
        newNode->left = buildTree(children[node][0], children);
    }
    if (children[node].size() == 2) {
        newNode->right = buildTree(children[node][1], children);
    }
    return newNode;
}

void preorder(const Node *node) {
    // root, left, right
    if (!node)
        return;

    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void postorder(const Node *node) {
    // left, right, root
    if (!node)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

void inorder(const Node *node) {
    // left, root, right
    if (!node)
        return;

    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, rt;
    cin >> n >> rt;

    // 0-indexed nodes
    // the input is guaranteed to be a binary tree
    // we follow the convention that->
    // if u -> v comes first and u -> w comes next, then v is the left node and w is the right node of u
    vector<vector<int>> children(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        children[u].push_back(v); // only store directed edge
    }

    const Node *root = buildTree(rt, children);
    inorder(root);
    cout << endl;
    postorder(root);
    cout << endl;
    preorder(root);
    cout << endl;

    // BFS
    int src = rt;

    queue<int> que;
    que.push(src);
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        cout << x << " ";
        for (int v : children[x])
            que.push(v);
    }
    cout << endl;
    return EXIT_SUCCESS;
}
