#include <bits/stdc++.h>
using namespace std;

#define int long long 

// Let S is a non-empty set of integers with atleast 2 elements
// Let x1, x2, ..., xn are the elements of S in non-decreasing order, where n = |S|
// We define the median of S as follows
// 1. If n is even, it is x(n / 2)
// 2. If n is odd, it is x((n + 1) / 2)

// The following collection supports insertion and deletion of integers in O(log(n))
// and can query the median of the collection in O(1), where n is the size of the collection
// before insertion/deletion

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
		} else if (hi.size() > lo.size()) {
			int n = *hi.begin();
			lo.insert(n);
			hi.erase(hi.begin());
		}
	}

	// We maintain the following invariants:
	// 1. Any element of the collection is either in lo or hi
	// 2. lo.size() >= hi.size() >= 0
	// 3. 0 <= (lo.size() - hi.size()) <= 1

	// If the above invariants are maintained and the collection isn't empty,
	// the largest element of lo (*lo.rbegin()) is the median of the collection

public:
	void insert(int x) {
		if (!nelts || x <= *lo.rbegin())
			lo.insert(x);
		else 
			hi.insert(x);

		rebalance();
		nelts++;
	}
	void delete(int x) {
		if (lo.find(x) != lo.end())
			lo.erase(lo.find(x));
		else if (hi.find(x) != hi.end())
			hi.erase(hi.find(x));
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
	bool empty() const {return !nelts;}
	int size() const {return nelts;}
};