#include <bits/stdc++.h>
using namespace std;

#define int long long 

class Solution {
  public:
    vector<int> countDistinct(vector<int> &arr, int k) {
		int n = (int)arr.size();
		vector<int> res;

		int l = 0;
		unordered_map<int, int> freq;
		set<int> s;
		for (int r = 0; r < n; r++) {
			if (!s.count(arr[r]))
				s.insert(arr[r]);
			freq[arr[r]]++;
			if (r - l + 1 == k) {
				res.push_back(s.size());
				if (!(--freq[arr[l]]))
					s.erase(arr[l]);
				l++;
			}
		}        
		return res;
    }
};