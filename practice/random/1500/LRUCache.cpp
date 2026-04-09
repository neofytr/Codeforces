#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
	int key, val;
	Node *next, Node *prev;
	Node (int k, int v) {
		key = k, val = v;
		next = prev = nullptr;
	}
};


class LRUCache {
	int cap;
	Node *head, Node *tail;
	unordered_map<int, Node *> f; 

	void remove(Node *node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	void insert(Node *node) {
		node->next = head->next;
		head->next->prev = node;
		node->prev = head;
		head->next = node;
	}

public:

	LRUCache(int capacity) {
		cap = capacity;
		head = new Node(0, 0);
		tail = new Node(0, 0);
		head->next = tail, tail->prev = head;
	}

	int get(int key) {
		if (!f.count(key)) return -1;
		Node *node = f[key];
		remove(node), insert(node);
		return node->val;
	}

	void put(int key, int val) {
		if (!cap) return;
		if (f.count(key)) {
			Node *node = f[key];
			node->val = val;
			remove(node), insert(node);
			return;
		}

		if (f.size() == cap) {
			Node *lru = tail->prev;
			f.erase(lru->key);
			remove(lru);
			delete lru;
		}

		Node *node = new Node(key, val);
		f[key] = node;
		insert(node);
	}
};