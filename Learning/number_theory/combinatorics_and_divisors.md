## 9. Matrix Exponentiation for Linear Recurrences

### 9.1 The Core Theorem

**Theorem 9.1.** Let f be a linear recurrence of order k:

    f(n) = c_1*f(n-1) + c_2*f(n-2) + ... + c_k*f(n-k)

with initial values f(1), f(2), ..., f(k). Then f(n) can be computed in O(k^3 log n)
arithmetic operations.

**Proof (by construction).** Define the state vector:

    v(n) = [f(n), f(n-1), ..., f(n-k+1)]^T

Then v(n) = T * v(n-1), where T is the k x k companion matrix:

    T = | c_1  c_2  c_3  ...  c_{k-1}  c_k |
        |  1    0    0   ...    0        0  |
        |  0    1    0   ...    0        0  |
        |  .    .    .   ...    .        .  |
        |  0    0    0   ...    1        0  |

**Verification.** The first row of T*v(n-1) gives:
c_1*f(n-1) + c_2*f(n-2) + ... + c_k*f(n-k) = f(n). The remaining rows simply shift:
the i-th row (i >= 2) copies f(n-i+1) from position i-1 of v(n-1).

By induction: v(n) = T^{n-k} * v(k), where v(k) = [f(k), f(k-1), ..., f(1)]^T.

Compute T^{n-k} by binary exponentiation on matrices. Each matrix multiplication is
O(k^3), and we perform O(log n) multiplications. Total: O(k^3 log n). QED.

### 9.2 Example: Fibonacci Numbers

f(n) = f(n-1) + f(n-2), with f(1) = f(2) = 1.

    T = | 1  1 |      v(2) = | f(2) | = | 1 |
        | 1  0 |             | f(1) |   | 1 |

    v(n) = T^{n-2} * v(2)

The answer f(n) is the top element of v(n).

### 9.3 Example: Custom Recurrence

f(n) = 2*f(n-1) + 3*f(n-2), with f(1) = 1, f(2) = 5.

    T = | 2  3 |
        | 1  0 |

### 9.4 Example: Three-Term Recurrence

f(n) = 3*f(n-1) + 5*f(n-2) + 2*f(n-3), with f(1) = 1, f(2) = 3, f(3) = 14.

    T = | 3  5  2 |
        | 1  0  0 |
        | 0  1  0 |

### 9.5 Implementation

```cpp
typedef vector<vector<long long>> Matrix;
const long long MOD = 1e9 + 7;

Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            if (A[i][k])
                for (int j = 0; j < n; j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

Matrix matpow(Matrix A, long long p) {
    int n = A.size();
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1; // identity
    while (p > 0) {
        if (p & 1) result = multiply(result, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return result;
}
```

**Optimization note.** The loop order `i, k, j` (rather than `i, j, k`) improves cache
performance because B[k][j] is accessed sequentially in j for a fixed k. The `if
(A[i][k])` short-circuits zero entries, which helps for sparse matrices.

---

## 10. Combinatorics Toolkit

### 10.1 Binomial Coefficients

**Definition.** The binomial coefficient C(n, k) (read "n choose k") is:

    C(n, k) = n! / (k! * (n-k)!)

for 0 <= k <= n, and C(n, k) = 0 if k < 0 or k > n.

**Combinatorial interpretation.** C(n, k) counts the number of ways to choose k objects
from n distinct objects, disregarding order.

### 10.2 Precomputation for Modular Binomials

When the modulus m is prime (typically m = 10^9 + 7), we can compute C(n, k) mod m in
O(1) per query after O(N) precomputation.

**Step 1.** Precompute factorials:
    fact[0] = 1
    fact[i] = fact[i-1] * i mod m      for i = 1, 2, ..., N

**Step 2.** Precompute inverse factorials.

The key insight: rather than computing N separate modular inverses (each O(log m)), we
compute only one inverse and propagate backward.

    inv_fact[N] = binpow(fact[N], m-2, m)       // one modular inverse
    inv_fact[i] = inv_fact[i+1] * (i+1) mod m   // for i = N-1, N-2, ..., 0

**Proof of backward propagation.** We claim inv_fact[i] = (i!)^{-1} mod m.

Base: inv_fact[N] = (N!)^{-1} by Fermat's inverse.

Inductive step: inv_fact[i] = inv_fact[i+1] * (i+1) = ((i+1)!)^{-1} * (i+1)
= (i+1) / ((i+1) * i!) = 1 / i! = (i!)^{-1} (mod m). QED.

**Step 3.** Answer queries:

    C(n, k) = fact[n] * inv_fact[k] % m * inv_fact[n-k] % m

```cpp
const int MAXN = 2000001;
const long long MOD = 1e9 + 7;
long long fact[MAXN], inv_fact[MAXN];

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i-1] * i % MOD;
    inv_fact[MAXN - 1] = binpow(fact[MAXN - 1], MOD - 2, MOD);
    for (int i = MAXN - 2; i >= 0; i--)
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
}

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] % MOD * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}
```

### 10.3 Lucas' Theorem

**Theorem 10.1 (Lucas).** For a prime p and non-negative integers n, k:

    C(n, k) = Product_{i} C(n_i, k_i)  (mod p)

where n = n_s * p^s + ... + n_1 * p + n_0 and k = k_s * p^s + ... + k_1 * p + k_0
are the base-p representations of n and k.

**Convention.** C(n_i, k_i) = 0 if k_i > n_i, making the entire product 0.

**Corollary.** C(n, k) mod p = 0 if any digit of k in base p exceeds the corresponding
digit of n. This is equivalent to (n AND k) = k when viewed bitwise in base p.

**When to use.** Lucas is essential when n and k are huge but p is small (e.g., p = 2, 3,
or a small prime). Standard factorial precomputation only works up to p-1 anyway.

```cpp
long long lucas(long long n, long long k, long long p) {
    if (k == 0) return 1;
    return C(n % p, k % p) * lucas(n / p, k / p, p) % p;
}
```

(Here C(n, k) uses the precomputed table of size p.)

---

## 11. Divisor Enumeration Tricks

### 11.1 All Divisors of a Single Number

**Algorithm.** Iterate i from 1 to floor(sqrt(n)). If i | n, add both i and n/i.

```cpp
vector<long long> get_divisors(long long n) {
    vector<long long> divs;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i)
                divs.push_back(n / i);
        }
    }
    sort(divs.begin(), divs.end());
    return divs;
}
```

**Complexity.** O(sqrt(n)) for enumeration, O(sqrt(n) log(sqrt(n))) if sorting is needed.

### 11.2 All Divisors of All Numbers 1 to N

**Algorithm.** For each i from 1 to N, iterate through multiples i, 2i, 3i, ..., <= N.
Mark i as a divisor of each.

```cpp
vector<vector<int>> all_divisors(int N) {
    vector<vector<int>> divs(N + 1);
    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j += i)
            divs[j].push_back(i);
    return divs;
}
```

**Complexity.** The total number of operations is:

    Sum_{i=1}^{N} floor(N/i) = N * Sum_{i=1}^{N} 1/i ~ N * ln(N)

by the harmonic series. So this is O(N log N).

### 11.3 Divisor-Pair Optimization

**Problem pattern.** Given n, find a pair (a, b) with a*b = n that minimizes max(a, b)
(or equivalently, find the pair closest to sqrt(n)).

**Solution.** Iterate i from 1 to sqrt(n). If i | n, consider the pair (i, n/i). The
pair with i closest to sqrt(n) minimizes max(i, n/i).

**Proof.** Among all pairs (d, n/d) with d | n and d <= sqrt(n), the value max(d, n/d)
= n/d is minimized when d is as large as possible, i.e., d is the largest divisor
of n that does not exceed sqrt(n).

**Application (Omkar and Shovels style).** When dividing n items into groups as evenly
as possible, the answer often involves finding the divisor of n closest to sqrt(n).

```cpp
// Find the divisor pair (a, b) of n with a*b = n minimizing max(a, b)
pair<long long, long long> best_pair(long long n) {
    long long best_d = 1;
    for (long long i = 1; i * i <= n; i++)
        if (n % i == 0)
            best_d = i;
    return {best_d, n / best_d};
}
```

---

## 12. Key Code Templates (Summary)

Below is a consolidated collection of all the core templates, ready for use in contests.

### 12.1 Sieve of Eratosthenes

```cpp
vector<bool> sieve(int N) {
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; (long long)i * i <= N; i++)
        if (is_prime[i])
            for (int j = i * i; j <= N; j += i)
                is_prime[j] = false;
    return is_prime;
}
```

### 12.2 Smallest Prime Factor Sieve + Factorization

```cpp
vector<int> spf;
void build_spf(int N) {
    spf.assign(N + 1, 0);
    for (int i = 2; i <= N; i++)
        if (spf[i] == 0)
            for (int j = i; j <= N; j += i)
                if (spf[j] == 0)
                    spf[j] = i;
}

vector<pair<int,int>> factorize(int x) {
    vector<pair<int,int>> factors;
    while (x > 1) {
        int p = spf[x], cnt = 0;
        while (x % p == 0) { x /= p; cnt++; }
        factors.push_back({p, cnt});
    }
    return factors;
}
```

### 12.3 Binary Exponentiation

```cpp
long long binpow(long long a, long long b, long long m) {
    long long result = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) result = (__int128)result * a % m;
        a = (__int128)a * a % m;
        b >>= 1;
    }
    return result;
}
```

### 12.4 Extended GCD + Modular Inverse (General)

```cpp
long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

long long modinv(long long a, long long m) {
    long long x, y;
    extgcd(a, m, x, y);
    return ((x % m) + m) % m;
}
```

### 12.5 Modular Inverse via Fermat (Prime Modulus)

```cpp
long long modinv_fermat(long long a, long long p) {
    return binpow(a, p - 2, p);
}
```

### 12.6 Matrix Exponentiation

```cpp
typedef vector<vector<long long>> Matrix;
const long long MOD = 1e9 + 7;

Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) if (A[i][k])
            for (int j = 0; j < n; j++)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

Matrix matpow(Matrix A, long long p) {
    int n = A.size();
    Matrix R(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) R[i][i] = 1;
    while (p > 0) {
        if (p & 1) R = multiply(R, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return R;
}
```

### 12.7 Binomial Coefficients (Mod Prime)

```cpp
const int MAXN = 2000001;
const long long MOD = 1e9 + 7;
long long fact[MAXN], inv_fact[MAXN];

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i-1] * i % MOD;
    inv_fact[MAXN-1] = binpow(fact[MAXN-1], MOD-2, MOD);
    for (int i = MAXN-2; i >= 0; i--)
        inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] % MOD * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
}
```

### 12.8 Euler's Totient (Single Value)

```cpp
long long euler_phi(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}
```

### 12.9 Euler's Totient (Sieve)

```cpp
vector<int> phi_sieve(int N) {
    vector<int> phi(N + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= N; i++)
        if (phi[i] == i)
            for (int j = i; j <= N; j += i)
                phi[j] -= phi[j] / i;
    return phi;
}
```

---

## Appendix: Quick Reference of Complexities

| Operation                          | Time Complexity         | Space       |
|------------------------------------|-------------------------|-------------|
| Trial division primality           | O(sqrt(n))              | O(1)        |
| Sieve of Eratosthenes up to N     | O(N log log N)          | O(N)        |
| SPF sieve up to N                  | O(N log log N)          | O(N)        |
| Factorize via SPF                  | O(log n)                | O(log n)    |
| GCD (Euclidean)                    | O(log min(a,b))         | O(1)        |
| Extended GCD                       | O(log min(a,b))         | O(log n)*   |
| Binary exponentiation              | O(log b)                | O(1)        |
| Modular inverse (Fermat)           | O(log p)                | O(1)        |
| Modular inverse (ExtGCD)           | O(log m)                | O(log m)*   |
| Euler's totient (single)           | O(sqrt(n))              | O(1)        |
| Euler's totient (sieve to N)       | O(N log log N)          | O(N)        |
| Matrix exponentiation (k x k)     | O(k^3 log n)            | O(k^2)      |
| Binomial coefficient (after setup) | O(1) per query          | O(N)        |
| Factorial precomputation           | O(N)                    | O(N)        |
| Enumerate divisors of n            | O(sqrt(n))              | O(sqrt(n))  |
| Enumerate all divisors 1..N        | O(N log N)              | O(N log N)  |

*Recursive implementation uses O(log n) stack space; iterative version uses O(1).

---

*End of number theory guide.*
