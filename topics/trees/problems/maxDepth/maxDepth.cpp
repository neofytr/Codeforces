#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: maxDepth
// URL: https://leetcode.com/problems/maximum-depth-of-binary-tree/
// Difficulty: easy
// Tags:
// Strategy:

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
    int maxDepth(TreeNode *root) {
        // a binary tree's maximum depth is the number of nodes along the longest path from the root node
        // down to the farthest leaf node

        queue<TreeNode *> que;

        int level = 0;
        if (root)
            que.push(root);
        while (!que.empty()) {
            int size = (int)que.size();
            while (size--) {
                auto node = que.front();
                que.pop();

                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
            level++;
        }

        return level;
    }
};