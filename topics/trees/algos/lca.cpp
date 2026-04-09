#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  private:
    vector<TreeNode *> vecp, vecq;
    void dfs(TreeNode *node, TreeNode *p, TreeNode *q, vector<TreeNode *> &path) {
        if (!node)
            return;
        path.push_back(node);
        if (node == p)
            vecp = path;
        if (node == q)
            vecq = path;

        dfs(node->left, p, q, path);
        dfs(node->right, p, q, path);
        path.pop_back();
    }

  public:
    // this returns the lca of p and q if they both exist inside the subtree rooted at node,
    // if only one of them exists in this subtree, that is returned, and if none of them are present,
    // nullptr is returned
    TreeNode *lcaEfficient(TreeNode *node, TreeNode *p, TreeNode *q) {
        // definition: f(node) returns either
        // - nullptr if neither p nor q exists in this subtree
        // - p or q if the current subtree contains exactly one of them
        // - the lowest common ancestor if this subtree contains both

        if (!node)
            return nullptr;
        // base case: empty subtree contains nothing

        if (node == p || node == q)
            return node;
        // base case: if current node is p or q, return it upward
        // this acts like a "found signal" that bubbles up

        auto left = lcaEfficient(node->left, p, q);
        // recursive call: search in left subtree
        auto right = lcaEfficient(node->right, p, q);
        // recursive call: search in right subtree

        if (left && right)
            return node;
        // recurrence: if left subtree has one target and right has the other,
        // then current node is the first point where both meet,
        // so by definition this node is the lowest common ancestor

        return left ? left : right;
        // if only one subtree is non-null, propagate it upward:
        // - means that either subtree already found p or q
        // - or that subtree has already identified the lca deeper inside
        // if both are null, return null (no target found here)
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        queue<pair<TreeNode *, vector<TreeNode *>>> que;
        vector<TreeNode *> vecp, vecq;
        if (!root)
            return nullptr;
        que.push({root, {root}});
        bool foundp = false;
        bool foundq = false;
        while (!que.empty()) {
            auto [node, path] = que.front();
            que.pop();

            if (node == p)
                foundp = true, vecp = path;
            if (node == q)
                break;

            foundq = true, vecq = path;
            if (foundp && foundq) {
                TreeNode *lca = root;
                int size = min(vecp.size(), vecq.size());
                for (int r = 0; r < size; r++)
                    if (vecp[r] == vecq[r])
                        lca = vecp[r];
                return lca;
            }

            if (node->left) {
                vector<TreeNode *> np = path;
                np.push_back(node->left);
                que.push({node->left, np});
            }
            if (node->right) {
                vector<TreeNode *> np = path;
                np.push_back(node->right);
                que.push({node->right, np});
            }
        }
        return nullptr;
    }
};