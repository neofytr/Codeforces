#include <bits/stdc++.h>
using namespace std;

#define int long long

class MedCol {
private:
	int nelts = 0;
	multiset<int> lo;
	multiset<int> hi;
	void rebalance() {
		if (lo.size() > hi.size() + 1) {
			int n = *lo.rbegin();
			hi.insert(n);
			lo.erase(prev(lo.end()));
			loSum -= n, hiSum += n;
		} else if (hi.size() > lo.size()) {
			int n = *hi.begin();
			lo.insert(n);
			hi.erase(hi.begin());
			loSum += n, hiSum -= n;
		}
	}

	// We maintain the following invariants:
	// 1. Any element of the collection is either in lo or hi
	// 2. lo.size() >= hi.size() >= 0
	// 3. 0 <= (lo.size() - hi.size()) <= 1

	// If the above invariants are maintained and the collection isn't empty,
	// the largest element of lo (*lo.rbegin()) is the median of the collection

public:
	int loSum = 0;
	int hiSum = 0;

	void insert(int x) {
		if (!nelts || x <= *lo.rbegin())
			lo.insert(x), loSum += x;
		else 
			hi.insert(x), hiSum += x;

		rebalance();
		nelts++;
	}
	void del(int x) {
		if (lo.find(x) != lo.end())
			lo.erase(lo.find(x)), loSum -= x;
		else if (hi.find(x) != hi.end())
			hi.erase(hi.find(x)), hiSum -= x;
		else 
			return; // x is not in the collection, or the collection is empty
		rebalance();
		nelts--;
	}

	int median() const {
		if (!nelts)
			runtime_error("median of an empty collection\n");
		return *lo.rbegin();
	}

	int idx() const { return lo.size() - 1;}
	bool empty() const {return !nelts;}
	int size() const {return nelts;}
};

int32_t main() {
	int n, k;
	cin >> n >> k;

	vector<int> arr(n);
	for (int &val : arr)
		cin >> val;

	MedCol med;

	int l = 0;
	for (int r = 0; r < n; r++) {
		med.insert(arr[r]);
		if (r - l + 1 == k) {
			cout << med.median() << " ";
			med.del(arr[l++]); 
		}
	}
	cout << endl;
	return 0;
}