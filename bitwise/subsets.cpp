// sample problem for iterating over all subsets of a set
#include <bits/stdc++.h>
using namespace std;

bool isPowerOfTwo(int n)
{
	return n > 0 && !(n & (n - 1)); // a very clever bitwise trick for checking powers of 2
}

int main()
{
	int n, highest, iter;
	long long target, curr;
	cin >> n >> target;

	vector<long long> arr(n);
	for (long long &val : arr)
		cin >> val;

	// print yes if there is a subset with sum target
	// print no otherwise

	// there are a total of 2^n subsets
	// there are also a total of 2^n binary numbers from 0 to 2^n - 1
	// to each of these numbers, we can associate a unique subset and vice-versa

	for (int subset = 0; subset < (1 << n); subset++) // loop over all 2^n possible subsets
	{
		curr = 0;
		for (int bit = 0; bit < n; bit++)
		{
			if (subset & (1 << bit))
				curr += arr[bit];

			if (curr > target)
				break;
		}

		if (curr == target)
		{
			cout << "Yes\n";
			return EXIT_SUCCESS;
		}
	}

	cout << "No\n";
	return EXIT_SUCCESS;
}