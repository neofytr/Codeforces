#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> count_sort_two(vector<int> &rank, vector<int> &v) {
	vector<int> res;
	unordered_map<int, vector<int>> buckets;
	for (int e : v)
		buckets[rank[e]].push_back(e);

	for (int i = 0; i < n; i++)
		for (int j : buckets[i])
			res.push_back(j);
	return res;
}

vector<int> count_sort_one(vector<int> &rank, int k) {
	unordered_map<int, vector<int>> buckets;
	vector<int> res;
	for (int i = 0; i < n; i++) 
		buckets[(i + k < n ? rank[i + k] : -1)].push_back(i);
	for (int i = -1; i < n; i++)
		for (int j : buckets[i]) res.push_back(j);
	return res;
}

vector<int> build_sa(string &s) {
	int n = s.length();
	vector<int> sa(n), rank(n), tmp(n);

	for (int i = 0; i < n; i++) sa[i] = i, rank[i] = s[i] - 'a';
	for (int k = 1; k < n; k <<= 1) {
		// (rank(i), (i + k < n ? rank[i + k] : -1)) 
		auto cmp = [&] (int a, int b) {
			if (rank[a] != rank[b]) 
				return rank[a] < rank[b];
			int ra = (a + k < n ? rank[a + k] : -1);
			int rb = (b + k < n ? rank[b + k] : -1);
			return ra < rb;
		};
		vector<int> v = count_sort_one(rank, k);
		v = count_sort_two(rank, v);
		for (int i = 0; i < n; i++) 
			sa[i] = v[i];

		tmp[sa[0]] = 0;
		for (int i = 1; i < n; i++)
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		swap(rank, tmp);
	}
	return sa;
}