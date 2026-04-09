#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    Node *left, *right;
    int val;
    Node(const int val) {
        this->val = val;
        left = right = nullptr;
    }
};

// we want to see what types of traversals are required to construct a unique binary tree
// out of 2-order combinations of the 3 traversal orders (preorder, inorder, postorder), a unique
// binary tree can be constructed using the following combinations ->

// preorder and inorder
// postorder and inorder

// preorder -> root, left, right
// inorder -> left, root, right

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
    unordered_map<int, int> mp;
    TreeNode *construct(vector<int> &preorder, int preStart, int preEnd, vector<int> &inorder, int inStart, int inEnd) {
        if (preStart > preEnd)
            return nullptr;
        if (inStart > inEnd)
            return nullptr;

        int curr = preorder[preStart];
        auto node = new TreeNode(curr);

        int idx = mp[curr];
        int numLeft = idx - 1 - inStart + 1;

        node->left = construct(preorder, preStart + 1, preStart + 1 + numLeft - 1, inorder, inStart, idx - 1);
        node->right = construct(preorder, preStart + numLeft + 1, preEnd, inorder, idx + 1, inEnd);
        return node;
    }

  public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        int size = preorder.size();
        for (int r = 0; r < size; r++)
            mp[inorder[r]] = r;
        return construct(preorder, 0, size - 1, inorder, 0, size - 1);
    }
};

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
class SolutionTwo {
    unordered_map<int, int> mp;
    // inorder -> left, root, right
    // postorder -> left, right, root
    TreeNode *construct(vector<int> &postorder, int postStart, int postEnd, vector<int> &inorder, int inStart, int inEnd) {
        if (postStart > postEnd)
            return nullptr;
        if (inStart > inEnd)
            return nullptr;

        int curr = postorder[postEnd];
        int idx = mp[curr];
        int sz = idx - inStart;

        node->left = construct(postorder, postStart, postStart + sz - 1, inorder, inStart, idx - 1);
        node->right = construct(postorder, postStart + sz, postEnd - 1, inorder, idx + 1, inEnd);
        return node;
    }

  public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        int size = (int)inorder.size();
        for (int r = 0; r < size; r++)
            mp[inorder[r]] = r;
        return construct(postorder, 0, size - 1, inorder, 0, size - 1);
    }
};