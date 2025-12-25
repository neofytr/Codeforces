#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define A 0
#define B 1
#define C 2 
#define AB 3  
#define BC 4
#define CA 5
#define ABC 6  


bool contains_all(const string& s) {
    return true;
}

template <typename First, typename... Rest>
bool contains_all(const string& s, const First& first, const Rest&... rest) {
    return s.find(first) != npos &&
           contains_all(s, rest...);
}

int32_t main() {
	int n;
	cin >> n;

	vector<pair<int, string>> v(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> v.first >> v.second;

	vector<int> dp(n + 1, vector<int>(7, -1));

	
	for (int r = 2; r <= n; r++)
}