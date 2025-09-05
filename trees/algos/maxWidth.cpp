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

/*
Given the root of a binary tree, return the maximum width of the given tree.
The maximum width of a tree is the maximum width among all levels.
The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
It is guaranteed that the answer will be in the range of a 32-bit signed integer.
*/

#define ll long long
class Solution {
  public:
    ll widthOfBinaryTree(TreeNode *root) {
        queue<pair<TreeNode *, ll>> que; // node, and its index in it's level (assuming complete binary tree)
        if (root)
            que.push({root, 0});
        ll maxi = 0;
        while (!que.empty()) {
            ll size = (ll)que.size();
            ll first = que.front().second;
            ll last = que.back().second;
            maxi = max(maxi, last - first + 1);
            while (size--) {
                auto [node, idx] = que.front();
                que.pop();

                idx -= first; // to prevent overflow, since shifting the indexes won't affect the actual numbers
                // between the real nodes

                if (node->left)
                    que.push({node->left, 2 * idx});
                if (node->right)
                    que.push({node->right, 2 * idx + 1});
            }
        }
        return maxi;
    }
};