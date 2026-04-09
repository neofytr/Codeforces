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

int maxDepth(const Node *node) {
    if (!node)
        return 0;
    return 1 + max(maxDepth(node->right), maxDepth(node->left));
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
    int depth = 0;
    if (root)
        que.push(root);
    while (!que.empty()) {
        int size = (int)que.size();
        while (size--) {
            const struct Node *node = que.front();
            que.pop();

            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        depth++;
    }

    cout << depth << endl;
    cout << maxDepth(root) << endl; // this is very simple too
    return EXIT_SUCCESS;
}