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

int getHeight(const Node *node) {
    if (!node)
        return 0;
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

// this returns the height of the tree if it's balanced, or -1 if it's not balanced
int checkBalanced(const Node *node) {
    if (!node)
        return 0;

    const int left = checkBalanced(node->left);
    const int right = checkBalanced(node->right);
    if (left == -1 || right == -1 || abs(left - right) > 1)
        return -1;

    return 1 + max(left, right);
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

    // a binary tree is balanced iff for every node, |height(left) - height(right)| <= 1

    // the maximum depth of a tree from some node is the number of nodes in the path from that node to the
    // farthest leaf node of the tree; this is also the height of the tree from that node
    // height(node) = 1 + max(height(node->left), height(node->right))
    // base case -> if (!node) return 0
    return EXIT_SUCCESS;
}