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
  private:
    void dfs(TreeNode *node, int row, int col, map<int, map<int, multiset<int>>> &colmp) {
        if (!node)
            return;

        colmp[col][row].insert(node->val);
        dfs(node->left, row + 1, col - 1, colmp);
        dfs(node->right, row + 1, col + 1, colmp);
    }

  public:
    vector<vector<int>> verticalTraversal(TreeNode *root) {
        map<int, map<int, multiset<int>>> colmp;
        dfs(root, 0, 0, colmp);
        vector<vector<int>> ans;

        for (auto &[col, rowmp] : colmp) {
            vector<int> level;
            for (auto &[row, arr] : rowmp)
                for (int v : arr)
                    level.push_back(v);
            ans.push_back(level);
        }
        return ans;
    }
};