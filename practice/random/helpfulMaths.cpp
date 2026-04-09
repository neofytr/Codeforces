#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n";

int32_t main() {
	string str;
	cin >> str;

	multiset<int> nums;
	for (int r = 0; r < str.size(); r++)
		if (str[r] != '+')
			nums.insert(str[r] - '0');

	for (auto itr = nums.begin(); itr != nums.end(); ++itr)
		if (itr != --nums.end())
			cout << *itr << "+";
		else 
			cout << *itr;
	cout << endl;
	return 0;
}