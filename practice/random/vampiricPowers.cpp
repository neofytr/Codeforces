#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

class DynamicBitset {
	using u64 = uint64_t;
	static constexpr int B = 64;

	size_t n;
	vector<u64> bits;

	inline void trim() {
		if (bits.empty()) return;
		size_t rem = n % B;
		if (rem) bits.back() &= ((1ULL << rem) - 1);
	}

public:
	DynamicBitset(size_t sz = 0)
		: n(sz), bits((sz + B - 1) / B, 0) {}

	size_t size() const { return n; }

	void reset() { fill(bits.begin(), bits.end(), 0); }

	void set_all() {
		fill(bits.begin(), bits.end(), ~0ULL);
		trim();
	}

	bool get(size_t i) const {
		return (bits[i >> 6] >> (i & 63)) & 1ULL;
	}

	void set(size_t i) {
		bits[i >> 6] |= 1ULL << (i & 63);
	}

	void reset(size_t i) {
		bits[i >> 6] &= ~(1ULL << (i & 63));
	}

	void flip(size_t i) {
		bits[i >> 6] ^= 1ULL << (i & 63);
	}

	int first_set_bit() const {
		for (size_t i = 0; i < bits.size(); i++)
			if (bits[i])
				return (i << 6) + __builtin_ctzll(bits[i]);
		return -1;
	}

	int first_set_bit(size_t pos) const {
		size_t w = pos >> 6;
		if (w >= bits.size()) return -1;

		u64 cur = bits[w] & (~0ULL << (pos & 63));
		if (cur) return (w << 6) + __builtin_ctzll(cur);

		for (++w; w < bits.size(); w++)
			if (bits[w])
				return (w << 6) + __builtin_ctzll(bits[w]);

		return -1;
	}

	int count() const {
		int ans = 0;
		for (u64 x : bits)
			ans += __builtin_popcountll(x);
		return ans;
	}

	bool any() const {
		for (u64 x : bits)
			if (x) return true;
		return false;
	}

	bool none() const { return !any(); }

	bool all() const {
		if (!n) return true;

		for (size_t i = 0; i + 1 < bits.size(); i++)
			if (bits[i] != ~0ULL)
				return false;

		size_t rem = n % B;
		return rem ? bits.back() == ((1ULL << rem) - 1)
				   : bits.back() == ~0ULL;
	}

	DynamicBitset& operator&=(const DynamicBitset& o) {
		assert(n == o.n);
		for (size_t i = 0; i < bits.size(); i++)
			bits[i] &= o.bits[i];
		return *this;
	}

	DynamicBitset& operator|=(const DynamicBitset& o) {
		assert(n == o.n);
		for (size_t i = 0; i < bits.size(); i++)
			bits[i] |= o.bits[i];
		return *this;
	}

	DynamicBitset& operator^=(const DynamicBitset& o) {
		assert(n == o.n);
		for (size_t i = 0; i < bits.size(); i++)
			bits[i] ^= o.bits[i];
		return *this;
	}

	friend DynamicBitset operator&(DynamicBitset a, const DynamicBitset& b) {
		return a &= b;
	}

	friend DynamicBitset operator|(DynamicBitset a, const DynamicBitset& b) {
		return a |= b;
	}

	friend DynamicBitset operator^(DynamicBitset a, const DynamicBitset& b) {
		return a ^= b;
	}

	DynamicBitset operator~() const {
		DynamicBitset r = *this;
		for (u64& x : r.bits) x = ~x;
		r.trim();
		return r;
	}

	DynamicBitset& operator<<=(size_t s) {
		if (s >= n) return reset(), *this;

		size_t ws = s >> 6, bs = s & 63;
		vector<u64> r(bits.size(), 0);

		for (int i = (int)bits.size() - 1; i >= 0; i--) {
			if (!bits[i]) continue;

			size_t ni = i + ws;
			if (ni >= bits.size()) continue;

			r[ni] |= bits[i] << bs;

			if (bs && ni + 1 < bits.size())
				r[ni + 1] |= bits[i] >> (64 - bs);
		}

		bits = move(r);
		trim();
		return *this;
	}

	DynamicBitset& operator>>=(size_t s) {
		if (s >= n) return reset(), *this;

		size_t ws = s >> 6, bs = s & 63;
		vector<u64> r(bits.size(), 0);

		for (size_t i = ws; i < bits.size(); i++) {
			size_t ni = i - ws;

			r[ni] |= bits[i] >> bs;

			if (bs && i + 1 < bits.size())
				r[ni] |= bits[i + 1] << (64 - bs);
		}

		bits = move(r);
		return *this;
	}

	friend DynamicBitset operator<<(DynamicBitset a, size_t s) {
		return a <<= s;
	}

	friend DynamicBitset operator>>(DynamicBitset a, size_t s) {
		return a >>= s;
	}
};

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), p(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) p[i] = p[i - 1] ^ a[i];

	vector<DynamicBitset> z(8, DynamicBitset(n + 1));
	vector<DynamicBitset> o(8, DynamicBitset(n + 1));

	for (int bit = 0; bit <= 7; bit++)
		z[bit].set(0);

	int maxi = LLONG_MIN;
	for (int i = 1; i <= n; i++) {
		DynamicBitset running(n + 1);
		running.set_all();
		for (int bit = 7; bit >= 0; bit--) {
			DynamicBitset prv = running;
			if (p[i] & (1ll << bit)) {
				running &= z[bit];

				if (!running.count()) {
					running = prv;
					continue;
				}

				int idx = running.first_set_bit();
				maxi = max(maxi, p[i] ^ p[idx]);				
			} else {
				running &= o[bit];

				if (!running.count()) {
					running = prv;
					continue;
				}

				int idx = running.first_set_bit();
				maxi = max(maxi, p[i] ^ p[idx]);
			}
		}

		for (int bit = 0; bit <= 7; bit++)
			if (p[i] & (1ll << bit)) o[bit].set(i);
			else z[bit].set(i);
	}

	cout << maxi << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}