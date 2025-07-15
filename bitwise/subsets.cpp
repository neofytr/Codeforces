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

	curr = 0;	 // holds the current sum of elements in the current subset
	highest = 0; // index to pick the next new element when starting a new subset
	iter = 0;	 // index to iterate through elements when adding to existing subset

	for (int subset = 0; subset < (1 << n); subset++) // loop over all 2^n possible subsets
	{
		if (isPowerOfTwo(subset))  // if 'subset' is a power of 2, it means a new subset is starting
			curr = arr[highest++]; // start a new subset with the next single element
		else
			curr += arr[iter++]; // continue adding elements to the current subset

		if (curr == target) // if the current sum matches the target
		{
			cout << "Yes\n";	 // a subset with required sum is found
			return EXIT_SUCCESS; // exit successfully
		}
	}

	cout << "No\n";
	return EXIT_SUCCESS;
}