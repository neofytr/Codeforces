/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int leftHeight(TreeNode *node) {
        if (!node)
            return 0;
        return 1 + leftHeight(node->left);
    }
    int rightHeight(TreeNode *node) {
        if (!node)
            return 0;
        return 1 + rightHeight(node->right);
    }

  public:
    // gives the total number of nodes in the subtree rooted at node, and the entire tree is complete
    int countNodes(TreeNode *node) {
        if (!node)
            return 0;
        const int left = leftHeight(node);
        // if left == right, the subtree rooted at node is complete
        // the number of nodes in it = 2 ^ left - 1;
        if (const int right = rightHeight(node); left == right)
            return (1 << (left)) - 1;
        // left > right
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
};