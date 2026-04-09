# Contest Templates -- Copy-Paste Ready

Minimal, correct templates. Each has a one-line description of WHEN to use it.

---

## 1. Base Template

```cpp
// Use as the starting point for every contest problem.
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(v) (v).begin(), (v).end()

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        // solve
    }
    return 0;
}
```

---

## 2. DSU (Disjoint Set Union)

```cpp
// Use when you need to merge sets and query connectivity. O(alpha(n)) per op.
struct DSU {
    vector<int> parent, sz;
    int components;

    DSU(int n) : parent(n), sz(n, 1), components(n) {
        iota(all(parent), 0);
    }

    int find(int x) {
        while (x != parent[x]) x = parent[x] = parent[parent[x]];
        return x;
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        components--;
        return true;
    }

    bool connected(int a, int b) { return find(a) == find(b); }
    int size(int a) { return sz[find(a)]; }
};
```

---

## 3. Segment Tree (Point Update, Range Query)

```cpp
// Use for range queries with point updates. O(log n) per operation.
template <typename T, T(*combine)(T, T), T identity>
struct SegTree {
    int n;
    vector<T> tree;

    SegTree(int n) : n(n), tree(2 * n, identity) {}

    SegTree(const vector<T>& a) : n(a.size()), tree(2 * a.size(), identity) {
        for (int i = 0; i < n; i++) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) tree[i] = combine(tree[2*i], tree[2*i+1]);
    }

    void update(int pos, T val) {
        pos += n;
        tree[pos] = val;
        for (pos >>= 1; pos > 0; pos >>= 1)
            tree[pos] = combine(tree[2*pos], tree[2*pos+1]);
    }

    // query [l, r)
    T query(int l, int r) {
        T resl = identity, resr = identity;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = combine(resl, tree[l++]);
            if (r & 1) resr = combine(tree[--r], resr);
        }
        return combine(resl, resr);
    }
};

// Example instantiation for sum:
int sum_combine(int a, int b) { return a + b; }
// SegTree<int, sum_combine, 0> seg(n);

// Example instantiation for min:
int min_combine(int a, int b) { return min(a, b); }
// SegTree<int, min_combine, LLONG_MAX> seg(n);
```

---

## 4. Segment Tree with Lazy Propagation

```cpp
// Use for range updates + range queries. O(log n) per operation.
struct LazySegTree {
    int n;
    vector<int> tree, lazy;

    LazySegTree(int n) : n(n), tree(4 * n, 0), lazy(4 * n, 0) {}

    void push(int v, int tl, int tr) {
        if (lazy[v]) {
            int tm = (tl + tr) / 2;
            apply(2*v, tl, tm, lazy[v]);
            apply(2*v+1, tm+1, tr, lazy[v]);
            lazy[v] = 0;
        }
    }

    void apply(int v, int tl, int tr, int val) {
        tree[v] += val * (tr - tl + 1);  // for sum; change for other ops
        lazy[v] += val;
    }

    void build(const vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) { tree[v] = a[tl]; return; }
        int tm = (tl + tr) / 2;
        build(a, 2*v, tl, tm);
        build(a, 2*v+1, tm+1, tr);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    void update(int v, int tl, int tr, int l, int r, int val) {
        if (l > tr || r < tl) return;
        if (l <= tl && tr <= r) { apply(v, tl, tr, val); return; }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        update(2*v, tl, tm, l, r, val);
        update(2*v+1, tm+1, tr, l, r, val);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > tr || r < tl) return 0;
        if (l <= tl && tr <= r) return tree[v];
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return query(2*v, tl, tm, l, r) + query(2*v+1, tm+1, tr, l, r);
    }

    // Convenience wrappers (0-indexed, inclusive [l, r])
    void build(const vector<int>& a) { build(a, 1, 0, n - 1); }
    void update(int l, int r, int val) { update(1, 0, n - 1, l, r, val); }
    int query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
```

---

## 5. Binary Search (Sentinel-Based)

```cpp
// Use when searching for the first/last position satisfying a monotone predicate.
// Returns the first index in [0, n-1] where predicate is true, or n if never true.
int binary_search(int n, function<bool(int)> pred) {
    int lo = -1, hi = n;  // invariant: pred(lo)=false, pred(hi)=true
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        if (pred(mid)) hi = mid;
        else lo = mid;
    }
    return hi;  // first true; lo = last false
}

// Binary search on real values (fixed iterations, no epsilon issues)
double binary_search_real(double lo, double hi, function<bool(double)> pred) {
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2;
        if (pred(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}
```

---

## 6. Sieve of Eratosthenes

```cpp
// Use to find all primes up to N. O(N log log N).
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; (long long)i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    return is_prime;
}

// Linear sieve: O(N), also computes smallest prime factor (SPF).
struct LinearSieve {
    vector<int> spf, primes;

    LinearSieve(int n) : spf(n + 1, 0) {
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) { spf[i] = i; primes.push_back(i); }
            for (int p : primes) {
                if (p > spf[i] || (long long)i * p > n) break;
                spf[i * p] = p;
            }
        }
    }
};
```

---

## 7. Prime Factorization

```cpp
// Trial division: O(sqrt(n)) per number. Use for individual queries.
map<int, int> factorize(int n) {
    map<int, int> factors;
    for (int d = 2; d * d <= n; d++) {
        while (n % d == 0) {
            factors[d]++;
            n /= d;
        }
    }
    if (n > 1) factors[n]++;
    return factors;
}

// SPF-based: O(log n) per number after O(N) sieve. Use for many queries.
// Requires LinearSieve from template 6.
map<int, int> factorize_spf(int n, const vector<int>& spf) {
    map<int, int> factors;
    while (n > 1) {
        factors[spf[n]]++;
        n /= spf[n];
    }
    return factors;
}
```

---

## 8. Binary Exponentiation (Modular)

```cpp
// Use for a^b mod m. O(log b).
int binpow(int a, int b, int m) {
    int res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
```

---

## 9. Extended GCD + Modular Inverse

```cpp
// Use for solving ax + by = gcd(a,b), and for modular inverse when m is not prime.
int extgcd(int a, int b, int& x, int& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int x1, y1;
    int g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Modular inverse of a mod m. Requires gcd(a, m) = 1.
int modinv(int a, int m) {
    int x, y;
    int g = extgcd(a, m, x, y);
    assert(g == 1);  // inverse exists only if gcd = 1
    return ((x % m) + m) % m;
}

// When m is prime, simpler: modinv(a, m) = binpow(a, m-2, m).
```

---

## 10. Matrix Exponentiation

```cpp
// Use for linear recurrences (Fibonacci, etc.) in O(k^3 log n) where k = matrix size.
typedef vector<vector<int>> Matrix;
const int MOD = 1e9 + 7;

Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size(), m = B[0].size(), k = B.size();
    Matrix C(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int p = 0; p < k; p++)
                C[i][j] = (C[i][j] + A[i][p] * B[p][j]) % MOD;
    return C;
}

Matrix matpow(Matrix A, int p) {
    int n = A.size();
    Matrix result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1;  // identity
    while (p > 0) {
        if (p & 1) result = multiply(result, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return result;
}

// Example: Fibonacci F(n) mod MOD
// [[F(n+1)], [F(n)]] = [[1,1],[1,0]]^n * [[1],[0]]
int fibonacci(int n) {
    if (n <= 1) return n;
    Matrix M = {{1, 1}, {1, 0}};
    Matrix R = matpow(M, n);
    return R[0][1];  // F(n)
}
```

---

## 11. Binomial Coefficients (Factorial Precomputation)

```cpp
// Use for C(n, k) mod p (p prime) with many queries. O(N) precomputation, O(1) per query.
const int MOD = 1e9 + 7;
const int MAXN = 2e6 + 5;
int fac[MAXN], inv_fac[MAXN];

void precompute() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fac[i] = fac[i - 1] * i % MOD;
    inv_fac[MAXN - 1] = binpow(fac[MAXN - 1], MOD - 2, MOD);
    for (int i = MAXN - 2; i >= 0; i--)
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
}

int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fac[n] % MOD * inv_fac[k] % MOD * inv_fac[n - k] % MOD;
}
```

---

## 12. Sparse Table

```cpp
// Use for static range minimum/maximum queries. O(n log n) build, O(1) query.
// Works for any idempotent operation: min, max, gcd, bitwise AND/OR.
struct SparseTable {
    vector<vector<int>> table;
    vector<int> lg;
    int n;

    SparseTable(const vector<int>& a) : n(a.size()), lg(a.size() + 1) {
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = lg[n] + 1;
        table.assign(K, vector<int>(n));
        table[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                table[k][i] = min(table[k-1][i], table[k-1][i + (1 << (k-1))]);
    }

    // query [l, r] inclusive
    int query(int l, int r) {
        int k = lg[r - l + 1];
        return min(table[k][l], table[k][r - (1 << k) + 1]);
    }
};
```

---

## 13. Custom Hash for unordered_map

```cpp
// Use whenever you need unordered_map on Codeforces to avoid hash collision TLE.
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// Usage: unordered_map<int, int, custom_hash> mp;
// For pair keys:
struct pair_hash {
    size_t operator()(pair<int,int> p) const {
        custom_hash h;
        return h(p.first) ^ (h(p.second) << 32);
    }
};
```

---

## 14. String Hashing (Polynomial Rolling Hash)

```cpp
// Use for O(1) substring comparison after O(n) precomputation.
// Double hash to minimize collision probability.
struct StringHash {
    static const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
    static const int BASE1 = 131, BASE2 = 137;
    int n;
    vector<int> h1, h2, pw1, pw2;

    StringHash(const string& s) : n(s.size()), h1(n+1), h2(n+1), pw1(n+1), pw2(n+1) {
        pw1[0] = pw2[0] = 1;
        for (int i = 0; i < n; i++) {
            h1[i+1] = ((long long)h1[i] * BASE1 + s[i]) % MOD1;
            h2[i+1] = ((long long)h2[i] * BASE2 + s[i]) % MOD2;
            pw1[i+1] = (long long)pw1[i] * BASE1 % MOD1;
            pw2[i+1] = (long long)pw2[i] * BASE2 % MOD2;
        }
    }

    // hash of s[l..r] inclusive (0-indexed)
    pair<int,int> get(int l, int r) {
        int v1 = (h1[r+1] - (long long)h1[l] * pw1[r-l+1] % MOD1 + (long long)MOD1 * 2) % MOD1;
        int v2 = (h2[r+1] - (long long)h2[l] * pw2[r-l+1] % MOD2 + (long long)MOD2 * 2) % MOD2;
        return {v1, v2};
    }

    // check if s[l1..r1] == s[l2..r2]
    bool equal(int l1, int r1, int l2, int r2) {
        return get(l1, r1) == get(l2, r2);
    }
};
```

---

## Quick Reference: When to Use What

| Problem Pattern | Template |
|---|---|
| Connectivity, merging sets | DSU (#2) |
| Point update + range query | Segment Tree PURQ (#3) |
| Range update + range query | Lazy Segment Tree (#4) |
| Optimize monotone predicate | Binary Search (#5) |
| "All primes up to N" | Sieve (#6) |
| Factor a single number | Trial Division (#7) |
| Factor many numbers | SPF Sieve (#6 + #7) |
| a^b mod m | Binary Exponentiation (#8) |
| 1/a mod m, solve ax+by=g | Extended GCD (#9) |
| Linear recurrence, nth term | Matrix Exponentiation (#10) |
| C(n,k) mod prime, many queries | Binomial Coefficients (#11) |
| Static range min/max/gcd | Sparse Table (#12) |
| Fast hashmap on Codeforces | Custom Hash (#13) |
| Substring equality, matching | String Hashing (#14) |
