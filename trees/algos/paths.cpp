#include <bits/stdc++.h>
using namespace std;

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
  public:
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> ans;
        if (!root)
            return ans;

        queue<pair<TreeNode *, string>> que;
        que.push({root, to_string(root->val)});

        while (!que.empty()) {
            auto [node, path] = que.front();
            que.pop();
            if (!node->left && !node->right)
                ans.push_back(path);
            if (node->left)
                que.push({node->left, path + "->" + to_string(node->left->val)});
            if (node->right)
                que.push({node->right, path + "->" + to_string(node->right->val)});
        }

        return ans;
    }
};
