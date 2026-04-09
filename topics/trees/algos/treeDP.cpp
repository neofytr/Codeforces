#include <bits/stdc++.h>
using namespace std;

/*
====================================================
TREE DFS / DP GENERAL PATTERN
====================================================

1. IDENTIFYING TREE DP / DFS PROBLEMS:
   - Problems involve a binary/n-ary tree.
   - Ask for a "global property" of the tree:
       * Max/Min path sum
       * Max depth / height
       * Diameter
       * Subtree sums / sizes
       * Balanced tree check
   - Typically, you can solve them by breaking the problem
     into "what each node contributes" and combining children's results.

2. STRATEGY / GENERAL METHOD:
   Step 1: Define a subproblem for each node.
       - What info does parent need from this node?
       - Examples: height, max gain downward, subtree sum.

   Step 2: Use DFS to compute children's subproblem values.
       - Base case: null node → return identity value (0, -∞, etc.)

   Step 3: Combine children's values to update a global answer.
       - Examples:
         * Max path sum: node->value + max(0,left) + max(0,right)
         * Diameter: leftHeight + rightHeight
         * Max depth: 1 + max(leftDepth, rightDepth)

   Step 4: Return to parent the info needed to continue recursion.
       - Example: for max path sum, return node->value + max(0, max(left,right))

3. ADDITIONAL STRATEGIES:
   - Post-order traversal is almost always used.
   - Sometimes need multiple values per node (use struct / pair).
   - BFS is useful for level-based computations.
   - Memoization may help for repeated subtrees (rare in trees without DAG property).

====================================================
GENERIC TEMPLATE FOR TREE DFS / DP
====================================================
*/

struct Node {
    int data;
    Node *left;
    Node *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Global variable to store answer
int globalAnswer = 0;

// Generic DFS function
/*
  - Returns value needed by parent.
  - Updates globalAnswer based on node + children's info.
  - Adapt combine logic depending on problem:
      * max path sum
      * diameter
      * max depth
      * subtree sum
*/
int dfs(Node *node) {
    if (!node)
        return 0; // Base case

    // Step 1: Recursively compute children's values
    int leftVal = dfs(node->left);
    int rightVal = dfs(node->right);

    // Step 2: Combine children's values with node's data
    int nodeContribution = node->data + max(0, leftVal) + max(0, rightVal);

    // Step 3: Update global answer
    globalAnswer = max(globalAnswer, nodeContribution);

    // Step 4: Return value for parent (max downward gain)
    return node->data + max(0, max(leftVal, rightVal));
}

// Utility to build binary tree from adjacency list
Node *buildTree(int node, const vector<vector<int>> &children) {
    Node *newNode = new Node(node); // node's value = node index
    const vector<int> &child = children[node];
    if (child.size() >= 1)
        newNode->left = buildTree(child[0], children);
    if (child.size() >= 2)
        newNode->right = buildTree(child[1], children);
    return newNode;
}

int main() {
    /*
      Input format:
      n root
      n-1 edges (u v, parent to child)
      Example:
      5 0
      0 1
      0 2
      1 3
      1 4
    */
    int n, root;
    cin >> n >> root;

    vector<vector<int>> children(n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        children[u].push_back(v);
    }

    Node *rootNode = buildTree(root, children);

    // Run DFS
    dfs(rootNode);

    cout << "Global answer (e.g., max path sum): " << globalAnswer << endl;

    return 0;
}

/*
====================================================
USAGE & ADAPTATION:
====================================================

1. Max Depth / Height:
   - dfs returns 1 + max(leftHeight, rightHeight)
   - Update globalAnswer = max(globalAnswer, nodeDepth)

2. Diameter:
   - dfs returns 1 + max(leftHeight, rightHeight)
   - Update globalAnswer = max(globalAnswer, leftHeight + rightHeight)

3. Subtree Sum:
   - dfs returns node->data + leftSum + rightSum
   - Update globalAnswer = max(globalAnswer, subtreeSum) or other criteria

4. Max Path Sum:
   - dfs returns node->data + max(0, max(leftGain, rightGain))
   - Update globalAnswer = max(globalAnswer, node->data + max(0,leftGain) + max(0,rightGain))

5. Balanced Tree Check:
   - dfs returns {isBalanced, height} as struct/pair
   - Combine left/right info and propagate

The idea is always:
- Define what parent needs
- Compute children recursively
- Combine children's info at node
- Update global answer
- Return info for parent
*/
