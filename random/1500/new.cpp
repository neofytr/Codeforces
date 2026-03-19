#include <bits/stdc++.h>
using namespace std;

#define int long long

int maxProfit(vector<int> &prices) {
	int minpr = LLONG_MAX;
	int maxprofit = 0;

	for (int price : prices) {
		minpr = min(minpr, price);
		maxprofit = max(maxprofit, price - minpr);
	}

	return maxprofit;
}

int32_t main() {
	vector<int> prices = {7,6,4,3,1};

	cout << maxProfit(prices) << endl;
	return 0;
}