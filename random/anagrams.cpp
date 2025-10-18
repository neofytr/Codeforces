#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
	unordered_map<int, int> patFreq;
	unordered_map<int, int> windowFreq;
	bool check() {
		for (int c = 0; c < 26; c++)
			if (patFreq[c] != windowFreq[c])
				return false;
		return true;
	}
  public:
    int search(string &pat, string &txt) {
    	int n = (int)txt.length();
    	int patSize = (int)pat.length();
        for (char c : pat)
        	patFreq[c - 'a']++;

        int l = 0;
        int cnt = 0;
        for (int r = 0; r < n; r++) {
        	windowFreq[txt[r] - 'a']++;
        	if (r - l + 1 == patSize) {
        		if (check())
        			cnt++;
        		windowFreq[txt[l++] - 'a']--;
        	}
        }

        return cnt;
    }
};