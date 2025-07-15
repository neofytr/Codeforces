// sample problem for iterating over all subsets of a set
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	long long s;
	long long curr;
	vector<long long> arr(n);
	bool found = false;

	cin >> n >> s;
	for (long long &val : arr)
		cin >> val;

	// print yes if there is a subset with sum s
	// print no otherwise

	// there are a total of 2^n subsets
	// there are also a total of 2^n binary numbers from 0 to 2^n - 1
	// to each of these numbers, we can associate a unique subset and vice-versa

	for (int subset = 0; subset < (1 << n); subset++)
	{
		curr = 0;
		for (int bit = 0; bit < n; bit++)
			if (subset & (1 << bit)) // it the bit is set, we take the corresponding element into the subset
			{
				curr += arr[bit];
				if (curr > s)
					break;
			}

		if (curr == s)
			found = true;
	}

	if (found)
		cout << "Yes\n";
	else
		cout << "No\n";

	return EXIT_SUCCESS;
}