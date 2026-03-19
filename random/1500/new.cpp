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

mirahi 
hult prize (top 8)
60,000 per month
startup was in VR space
it was unofficial, i was working for the founding member senior (mihika deshpande)

in the range 50-70k would be appreciated
