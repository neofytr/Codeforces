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

/*
The recurrence says:
diameter(u) = max(diameter(left), diameter(right), height(left)+height(right))

Our DFS does this implicitly:
When height(node.left) is called, it also updates the global diameter for the left subtree
Same for the right subtree
Then at node, we check lh + rh and update the global diameter.
So the global variable diameter ends up being the max of all three terms for every node, exactly as the recurrence requires.
*/

int diam = LLONG_MIN;
int getHeight(const Node *node) {
    if (!node)
        return 0;

    const int left = getHeight(node->left);   // diam is updated for the left subtree when this is called
    const int right = getHeight(node->right); // diam is also updated for the right subtree when this is called
    diam = max(diam, left + right);           // so this implicitly implements the recurrence we derived in main
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

    // the diameter of a binary tree is the longest simple path between any two nodes of the tree

    // we define ->
    // diameter(n) is the diameter of the subtree rooted at n
    // diameter(nullptr)= 0
    // height(node) is the length of the simple path from n to the farthest leaf node of n
    // height(nullptr) = 0

    // the following holds ->
    // diameter(n) = max(diameter(n->left), diameter(n->right), height(n->left) + height(n->right))
    // Proof ->
    // The longest path from one node to another in the subtree rooted at n can either
    // 1. pass through n
    // 2. doesn't pass through n and is in the right-subtree of n, in which case it's diameter(n->right); if there is no right-subtree, its 0
    // 3. doesn't pass through n and is in the left-subtree of n, in which case it's diameter(n->left); if there is no left-subtree, its 0
    // The length of the longest path from one node to another in the subtree rooted at n that passes through n is
    // clearly height(n->left) + height(n->right); if either of the left or right subtree doesn't exist, height of that is 0 and is consistent with the definition
    // Hence, we have the relation
}