#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    Node *left, *right;
    int data;
    explicit Node(const int data) {
        this->data = data;
        left = right = nullptr;
    }
};

Node *buildTree(const int node, const vector<int> &data, const vector<vector<int>> &children) {
    const auto n = new Node(data[node]);
    const vector<int> &child = children[node];
    const auto size = child.size();
    if (size >= 1)
        n->left = buildTree(child[0], data, children);
    if (size >= 2)
        n->right = buildTree(child[1], data, children);
    return n;
}

vector<int> preorder(Node *root) {
    // root, left, right
    stack<Node *> st;
    vector<int> pre;

    st.push(root);
    while (!st.empty()) {
        const auto node = st.top();
        st.pop();
        if (!node)
            continue;

        st.push(node->right);
        st.push(node->left);
        pre.push_back(node->data);
    }
    return pre;
}

vector<int> inorder(Node *root) {
    // left, root, right
    vector<int> in;
    stack<Node *> st;

    Node *node = root;
    while (node || !st.empty()) {
        while (node)
            st.push(node), node = node->left;
        node = st.top(), st.pop();
        in.push_back(node->data);
        node = node->right;
    }
    return in;
}

vector<int> postorder(Node *root) {
    // left, right, root
    vector<int> post;
    stack<Node *> stOne, stTwo;

    // do reverse post root -> right -> left
    // then reverse
    stOne.push(root);
    while (!stOne.empty()) {
        const auto node = stOne.top();
        stOne.pop();
        if (!node)
            continue;
        stOne.push(node->left);
        stOne.push(node->right);
        stTwo.push(node);
    }
    while (!stTwo.empty())
        post.push_back(stTwo.top()->data), stTwo.pop();
    return post;
}

int maxDiam = LLONG_MIN;
int getHeight(const Node *node) {
    // diameter(n) = 0, if n == nullptr
    //             = length of the longest path in the subtree rooted at n, otherwise
    // diameter(n) = max(diameter(n->left), diameter(n->right), height(n->left) + height(n->right))

    if (!node)
        return 0;
    const int left = getHeight(node->left);
    const int right = getHeight(node->right);
    maxDiam = max(maxDiam, left + right); // maxDiam would be updated with max of diam(left, right) when getHeight will be called on left and right
    return 1 + max(left, right);
}

int maxMts = LLONG_MIN;
int mps(const Node *node) {
    // mps(n) = 0, if n == nullptr
    //        = maximum value path in the subtree rooted at n that ends at n, otherwise
    // mps(n) = n->data + max(0, mps(n->left), mps(n->right))

    // mts(n) = 0, if n == nullptr
    //        = maximum value path through n in the subtree rooted at n
    // mts(n) = n->data + max(0, mps(n->left)) + max(0, mps(n->right))

    // maximum value path in the graph rooted at root
    // = max(mts(n) for all nodes n in the graph rooted at root)
    if (!node)
        return 0;
    const int left = mps(node->left);
    const int right = mps(node->right);
    const int mtsnode = node->data + max(0LL, left) + max(0LL, right);
    maxMts = max(maxMts, mtsnode);
    return node->data + max(0LL, max(left, right));
}

int height(const Node *node) {
    // height(n) = 0, if n == nullptr
    //           = length of the path from n to the farthest leaf in the subtree rooted at n, otherwise
    // height(n) = 1 + max(height(n->left), height(n->right))
    if (!node)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

int32_t main() {
    int n, rt;
    cin >> n >> rt;

    int u, v;
    vector<vector<int>> children(n);
    vector<int> data(n);
    for (int r = 1; r <= n - 1; r++)
        cin >> u >> v, children[u].push_back(v);
    for (int node = 0; node < n; node++)
        cin >> data[node];

    Node *root = buildTree(rt, data, children);

    vector<int> pre, in, post;
    stack<pair<Node *, int>> st;
    if (root)
        st.push({root, 1});
    while (!st.empty()) {
        const auto [node, num] = st.top();
        st.pop();

        if (num == 1) {
            pre.push_back(node->data);
            st.push({node, num + 1});
            if (node->left)
                st.push({node->left, 1});
        } else if (num == 2) {
            in.push_back(node->data);
            st.push({node, num + 1});
            if (node->right)
                st.push({node->right, 1});
        } else
            post.push_back(node->data);
    }

    return EXIT_SUCCESS;
}