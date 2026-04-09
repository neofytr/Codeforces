#include <bits/stdc++.h>
using namespace std;

class Solution {
  private:
    bool solve(TreeNode *one, TreeNode *two) {
        if (!one && !two)
            return true;
        if ((one && !two) || (!one && two))
            return false;
        return (one->val == two->val) && solve(one->left, two->right) && solve(one->right, two->left);
    }

  public:
    bool isSymmetric(TreeNode *root) {
        if (!root)
            return true;

        queue<TreeNode *> que;
        que.push(root);

        while (!que.empty()) {
            int size = que.size();
            vector<TreeNode *> level;

            while (size--) {
                TreeNode *node = que.front();
                que.pop();
                level.push_back(node);

                if (node) {
                    que.push(node->left);
                    que.push(node->right);
                }
            }

            int l = 0, r = level.size() - 1;
            while (l < r) {
                if (!level[l] && !level[r]) {
                    l++, r--;
                    continue;
                }
                if (!level[l] || !level[r])
                    return false; // one null, one non-null
                if (level[l]->val != level[r]->val)
                    return false;
                l++, r--;
            }
        }
        return true;
    }
};
