#include <bits/stdc++.h>
using namespace std;

// this function builds a jump table (next_pos) such that
// next_pos[i][c] gives the first position >= i in s where character c occurs
vector<vector<int>> build_jump_table(const string &s, int k)
{
	int m = s.size();
	vector<vector<int>> next_pos(m + 1, vector<int>(k, m));

	// fill from right to left
	for (int i = m - 1; i >= 0; --i)
	{
		for (int j = 0; j < k; ++j)
		{
			next_pos[i][j] = next_pos[i + 1][j]; // copy from next position
		}
		next_pos[i][s[i] - 'a'] = i; // update with current character
	}
	return next_pos;
}

// check if a given string "candidate" is a subsequence of s using the jump table
bool is_subsequence(const string &candidate, const vector<vector<int>> &next_pos)
{
	int pos = 0;
	int m = next_pos.size() - 1; // original string size
	for (char c : candidate)
	{
		int ci = c - 'a';
		if (next_pos[pos][ci] == m)
			return false; // character not found
		pos = next_pos[pos][ci] + 1;
	}
	return true;
}

// generate the first missing subsequence of length n using the first k letters
// this function uses dfs-style lexicographic generation with early pruning
bool generate_missing(int idx, int n, int k, string &current,
					  const vector<vector<int>> &next_pos, string &result)
{
	if (idx == n)
	{
		if (!is_subsequence(current, next_pos))
		{
			result = current;
			return true;
		}
		return false;
	}
	for (int i = 0; i < k; ++i)
	{
		current.push_back('a' + i);
		if (generate_missing(idx + 1, n, k, current, next_pos, result))
		{
			return true;
		}
		current.pop_back();
	}
	return false;
}

void solve()
{
	int n, k, m;
	cin >> n >> k >> m;
	string s;
	cin >> s;

	// build jump table for fast subsequence checking
	vector<vector<int>> jump = build_jump_table(s, k);

	// try to generate any string of length n over first k letters that is not a subsequence
	string candidate = "", missing = "";
	if (generate_missing(0, n, k, candidate, jump, missing))
	{
		cout << "NO\n"
			 << missing << "\n";
	}
	else
	{
		cout << "YES\n";
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
