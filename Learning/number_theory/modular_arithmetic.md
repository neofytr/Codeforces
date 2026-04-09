## 4. Modular Arithmetic

### 4.1 The Ring Z/mZ

**Definition.** For a positive integer m, the set Z/mZ = {0, 1, 2, ..., m-1} with
addition and multiplication performed modulo m forms a commutative ring.

**Fundamental property.** If a = a' (mod m) and b = b' (mod m), then:
- a + b = a' + b' (mod m)
- a - b = a' - b' (mod m)
- a * b = a' * b' (mod m)

In other words, we may reduce modulo m at any intermediate step of a computation
involving addition, subtraction, and multiplication without affecting the final result.

**Division is NOT preserved.** 6 = 6 (mod 10), 2 = 2 (mod 10), but 6/2 = 3 while
we cannot simply "divide mod 10" without care. Division requires a modular inverse.

### 4.2 Handling Negative Remainders

In C++, the `%` operator can return negative values when the dividend is negative:
(-7) % 3 = -1 in C++.

**Fix:** To ensure a non-negative result:

```cpp
long long mod(long long a, long long m) {
    return ((a % m) + m) % m;
}
```

**Proof.** If a % m = r with -m < r < 0, then (r + m) is in [1, m-1] and is congruent
to a (mod m). If r >= 0, then (r + m) % m = r, which is correct. QED.

### 4.3 Modular Inverse

**Definition.** The *modular inverse* of a modulo m, denoted a^{-1} mod m, is an
integer x such that ax = 1 (mod m).

**Theorem 4.1.** a^{-1} mod m exists if and only if gcd(a, m) = 1.

**Proof.**
(=>) If ax = 1 (mod m), then ax = 1 + km for some integer k, i.e., ax - km = 1.
Any common divisor of a and m must divide 1, so gcd(a, m) = 1.

(<=) If gcd(a, m) = 1, then by Bezout's identity there exist x, y with ax + my = 1.
Reducing mod m: ax = 1 (mod m), so x is the inverse. QED.

**Corollary.** When m is prime, every nonzero element of Z/mZ has an inverse. That is,
Z/pZ is a field.

---

## 5. Binary Exponentiation

### 5.1 The Algorithm

**Problem.** Compute a^b mod m efficiently.

**Naive approach.** Multiply a by itself b times: O(b) multiplications. For b ~ 10^18,
this is far too slow.

**Binary exponentiation.** Express b in binary: b = b_0 + 2*b_1 + 4*b_2 + ... . Then:

    a^b = a^{b_0} * (a^2)^{b_1} * (a^4)^{b_2} * ...

We repeatedly square a and multiply into the result when the corresponding bit of b
is set. This requires only O(log b) multiplications.

### 5.2 Formal Correctness

**Invariant.** At each iteration of the loop, the value `result * a^b mod m` equals
the desired answer.

**Proof.** Initially, result = 1 and a^b is the desired answer, so the invariant holds.

At each step:
- If b is odd: result <- result * a (mod m), and b <- b - 1. The invariant becomes
  (result * a) * a^{b-1} = result * a^b. Preserved.
- Then: a <- a^2 (mod m), b <- b / 2. The invariant becomes
  result * (a^2)^{b/2} = result * a^b. Preserved.

When b = 0: result * a^0 = result, so result is the answer. QED.

**Complexity.** The loop runs O(log b) times, each iteration performing O(1)
multiplications modulo m.

```cpp
long long binpow(long long a, long long b, long long m) {
    long long result = 1;
    a %= m;
    while (b > 0) {
        if (b & 1)
            result = (__int128)result * a % m;
        a = (__int128)a * a % m;
        b >>= 1;
    }
    return result;
}
```

**Note on overflow.** When m can be up to ~10^18, the product of two numbers mod m can
overflow a 64-bit integer. Using `__int128` handles this. For m <= ~2*10^9, regular
`long long` multiplication suffices.

---

## 6. Fermat's Little Theorem and Modular Inverse via Exponentiation

### 6.1 Fermat's Little Theorem

**Theorem 6.1 (Fermat's Little Theorem).** If p is prime and p does not divide a, then:

    a^{p-1} = 1 (mod p)

**Proof.** Consider the p-1 nonzero residues: {1, 2, ..., p-1}. Multiply each by a:
{a, 2a, ..., (p-1)a}. We claim these are a permutation of {1, 2, ..., p-1} modulo p.

- Each ia mod p is nonzero (since p does not divide a or i).
- They are distinct: if ia = ja (mod p), then (i-j)a = 0 (mod p), and since p does
  not divide a, p | (i-j), which forces i = j (as 1 <= i, j <= p-1).

Therefore:

    (a)(2a)(3a)...((p-1)a) = 1 * 2 * 3 * ... * (p-1)  (mod p)
    a^{p-1} * (p-1)! = (p-1)!  (mod p)

Since gcd((p-1)!, p) = 1 (no factor of (p-1)! is divisible by p), we can cancel:

    a^{p-1} = 1 (mod p).  QED.

### 6.2 Modular Inverse via Fermat

**Corollary 6.2.** If p is prime and gcd(a, p) = 1, then:

    a^{-1} = a^{p-2} (mod p)

**Proof.** From a^{p-1} = 1 (mod p), multiply both sides by a^{-1}:
a^{p-2} = a^{-1} (mod p). Equivalently, a * a^{p-2} = a^{p-1} = 1 (mod p). QED.

**Computation.** Use binary exponentiation: a^{p-2} mod p in O(log p).

```cpp
long long modinv(long long a, long long p) {
    return binpow(a, p - 2, p);
}
```

**Limitation.** This method works only when the modulus is prime. For general moduli,
use the extended Euclidean algorithm (Section 7).

---

## 7. Extended Euclidean Algorithm

### 7.1 Bezout's Identity

**Theorem 7.1 (Bezout's Identity).** For any integers a, b (not both zero), there exist
integers x, y such that:

    ax + by = gcd(a, b)

Moreover, gcd(a, b) is the smallest positive integer expressible as a linear combination
of a and b.

### 7.2 The Extended Euclidean Algorithm

**Algorithm.** Modify the standard Euclidean algorithm to track the coefficients.

**Base case.** gcd(a, 0) = a. Coefficients: x = 1, y = 0 (since a*1 + 0*0 = a).

**Recursive step.** Suppose we have computed gcd(b, a mod b) = b*x_1 + (a mod b)*y_1.

Write a mod b = a - floor(a/b) * b. Substituting:

    gcd = b * x_1 + (a - floor(a/b) * b) * y_1
        = a * y_1 + b * (x_1 - floor(a/b) * y_1)

Therefore: x = y_1, y = x_1 - floor(a/b) * y_1.

```cpp
long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
```

### 7.3 Modular Inverse via Extended GCD

To find a^{-1} mod m (when gcd(a, m) = 1):

Solve ax + my = 1. Then ax = 1 (mod m), so x mod m is the inverse.

```cpp
long long modinv_extgcd(long long a, long long m) {
    long long x, y;
    long long g = extgcd(a, m, x, y);
    // g must be 1 for inverse to exist
    return ((x % m) + m) % m;
}
```

**Advantage over Fermat.** Works for any modulus m coprime to a, not just primes.

---

## 8. Euler's Theorem and Totient Function

### 8.1 Euler's Totient Function

**Definition.** For a positive integer n, Euler's totient function phi(n) counts the
number of integers k in {1, 2, ..., n} such that gcd(k, n) = 1:

    phi(n) = |{k : 1 <= k <= n, gcd(k, n) = 1}|

**Examples.** phi(1) = 1, phi(2) = 1, phi(6) = 2, phi(p) = p - 1 for prime p.

### 8.2 The Product Formula

**Theorem 8.1.** If n = p_1^{a_1} * p_2^{a_2} * ... * p_k^{a_k}, then:

    phi(n) = n * Product_{i=1}^{k} (1 - 1/p_i)
           = n * (p_1-1)/p_1 * (p_2-1)/p_2 * ... * (p_k-1)/p_k

**Proof by inclusion-exclusion.** Among {1, 2, ..., n}, we want to count integers
coprime to n, i.e., not divisible by any prime factor of n.

Let A_i = {k in {1,...,n} : p_i | k}. Then |A_i| = n / p_i.

By inclusion-exclusion:

    |A_1 union ... union A_k|
      = Sum |A_i| - Sum |A_i intersect A_j| + ...
      = Sum n/p_i - Sum n/(p_i * p_j) + ...

The count of integers NOT divisible by any p_i is:

    phi(n) = n - Sum n/p_i + Sum n/(p_i * p_j) - ...
           = n * (1 - 1/p_1)(1 - 1/p_2)...(1 - 1/p_k)

The last step follows by expanding the product: it produces exactly the
inclusion-exclusion sum with all possible subsets of {p_1, ..., p_k}. QED.

### 8.3 Properties of phi

**Property 1 (Multiplicativity).** If gcd(a, b) = 1, then phi(ab) = phi(a) * phi(b).

*Proof.* Follows directly from the product formula: the prime factors of ab are the
union of those of a and b (disjoint since gcd(a,b)=1), so the products combine.

**Property 2 (Divisor sum identity).** Sum_{d | n} phi(d) = n.

*Proof.* Partition {1, 2, ..., n} by gcd with n. For each divisor d of n, the set
{k : gcd(k, n) = d} has the same cardinality as {k/d : gcd(k/d, n/d) = 1} = phi(n/d).
As d ranges over divisors of n, so does n/d. Therefore Sum_{d|n} phi(d) = n. QED.

### 8.4 Euler's Theorem

**Theorem 8.2 (Euler's Theorem).** If gcd(a, n) = 1, then:

    a^{phi(n)} = 1 (mod n)

**Proof.** The proof generalizes Fermat's Little Theorem. Let r_1, r_2, ..., r_{phi(n)}
be the phi(n) integers in {1,...,n} coprime to n. The set {a*r_1 mod n, ..., a*r_{phi(n)} mod n}
is a permutation of {r_1, ..., r_{phi(n)}} (same argument: each product is coprime to n,
and they are distinct). Multiplying all elements:

    a^{phi(n)} * r_1 * r_2 * ... * r_{phi(n)} = r_1 * r_2 * ... * r_{phi(n)}  (mod n)

Canceling the product (which is coprime to n) gives a^{phi(n)} = 1 (mod n). QED.

**Corollary.** a^{-1} = a^{phi(n)-1} (mod n) when gcd(a, n) = 1.

**Remark.** Fermat's Little Theorem is the special case where n is prime and
phi(n) = n - 1.

### 8.5 Computing Euler's Totient

**Single value (via factorization), O(sqrt(n)):**

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

**Range computation (sieve), O(N log log N):**

```cpp
vector<int> phi_sieve(int N) {
    vector<int> phi(N + 1);
    iota(phi.begin(), phi.end(), 0);  // phi[i] = i initially
    for (int i = 2; i <= N; i++) {
        if (phi[i] == i) {  // i is prime
            for (int j = i; j <= N; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}
```

**Correctness.** When we encounter prime p (identified by phi[p] still equaling p), we
multiply phi[j] by (1 - 1/p) for every multiple j of p, which is exactly
phi[j] -= phi[j] / p. After processing all primes, phi[n] = n * Product(1 - 1/p_i).

---
