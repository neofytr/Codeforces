#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    Node(const int data) {
        this->data = data;
        return;
    }
    Node(const int val, struct Node *left, struct Node *right) {
        data = val;
        this->left = left;
        this->right = right;
        return;
    }
};

int32_t main() {
    return EXIT_SUCCESS;
}