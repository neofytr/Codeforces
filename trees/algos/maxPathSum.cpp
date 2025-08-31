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

int maxPath = LLONG_MIN;
int maxGain(const Node *node) {
    if (!node)
        return 0;

    const int left = maxGain(node->left);
    const int right = maxGain(node->right);
    const int maxPathThroughNode = node->data + max(0LL, left) + max(0LL, right);
    maxPath = max(maxPath, maxPathThroughNode);

    return node->data + max(0LL, max(left, right));
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

    // we need to find the maximum sum along paths for any non-empty path in the binary trees

    // for a node n, we define
    // maxGain(n) = 0 if n == nullptr
    // maxGain(n) = max(n->data, max(maxGain(n->left) + n->data, maxGain(n->right) + n->data) otherwise
    //            = n->data + max(0, maxGain(n->left), maxGain(n->right))
    // maxGain(n) is the best sum starting at node n, and going downwards
    // we only pick one side (either left, or right, or none) so that we can continue the path upward

    // maxPath(n) is the maximum path sum passing through node n in the subtree rooted at n
    // maxPath(n) = 0 if n == nullptr
    //            = n->data + max(0, maxGain(n->left)) + max(0, maxGain(n->right)

    // maximum sum along paths for any non-empty path =
    // max(maxPath(n) for all nodes n in the tree)
    // Proof ->
    // suppose there is a non-empty path we haven't considered in this relation
    // since the path is non-empty, there must a node n such that n is on the path
    // and n has the least height among all the nodes in the path
    // then, this path is the longest path passing through n in the subtree rooted at n
    // which will be considered in maxPath(n)
    // a contradiction

    maxGain(root);
    cout << maxPath << endl;
    return EXIT_SUCCESS;
}