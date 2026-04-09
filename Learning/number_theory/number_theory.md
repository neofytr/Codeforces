# Number Theory for Competitive Programming

A rigorous treatment of the number-theoretic tools that appear most frequently in
competitive programming. We state theorems precisely, give proofs where they build
intuition, and provide battle-tested C++ templates at the end.

---

## 1. Divisibility and Primes

### 1.1 Basic Definitions

**Definition.** An integer d *divides* an integer n (written d | n) if there exists an
integer q such that n = dq. We call d a *divisor* (or *factor*) of n.

**Definition.** An integer p > 1 is *prime* if its only positive divisors are 1 and p.
An integer n > 1 that is not prime is *composite*.

### 1.2 The Fundamental Theorem of Arithmetic

**Theorem 1.1 (Fundamental Theorem of Arithmetic).**
Every integer n > 1 can be written as a product of primes:

    n = p_1^{a_1} * p_2^{a_2} * ... * p_k^{a_k}

where p_1 < p_2 < ... < p_k are primes and a_i >= 1. Moreover, this representation
is *unique* up to the ordering of the factors.

**Proof (Existence).** By strong induction on n. The base case n = 2 is itself prime.
Suppose every integer m with 2 <= m < n has a prime factorization. If n is prime,
we are done. Otherwise n = ab with 1 < a, b < n. By the inductive hypothesis both
a and b have prime factorizations, and their product gives a prime factorization of n.

**Proof (Uniqueness).** We require Euclid's Lemma: if p is prime and p | ab, then
p | a or p | b. (This itself follows from the property that gcd(p, a) = 1 when p
does not divide a, combined with Bezout's identity.)

Suppose n = p_1^{a_1} * ... * p_k^{a_k} = q_1^{b_1} * ... * q_m^{b_m} are two prime
factorizations. Since p_1 divides the left side, p_1 divides the right side. By
repeated application of Euclid's Lemma, p_1 | q_j for some j. Since q_j is prime,
p_1 = q_j. We can cancel one copy of p_1 from both sides and proceed by induction
on the total number of prime factors. This establishes that the two factorizations
are identical. QED.

### 1.3 The Divisor-Counting Function tau(n)

**Theorem 1.2.** If n = p_1^{a_1} * p_2^{a_2} * ... * p_k^{a_k}, then the number of
positive divisors of n is:

    tau(n) = (a_1 + 1)(a_2 + 1) * ... * (a_k + 1)

**Proof.** Every divisor d of n has the form d = p_1^{e_1} * ... * p_k^{e_k} where
0 <= e_i <= a_i for each i (by uniqueness of prime factorization, d cannot contain a
prime not in the factorization of n, nor can the exponent of p_i in d exceed a_i).
Conversely, every such choice of exponents yields a divisor. The number of independent
choices is the product of the number of options for each exponent, which is
(a_1 + 1)(a_2 + 1)...(a_k + 1). QED.

**Example.** n = 360 = 2^3 * 3^2 * 5^1. Then tau(360) = 4 * 3 * 2 = 24.

### 1.4 The Divisor-Sum Function sigma(n)

**Theorem 1.3.** If n = p_1^{a_1} * ... * p_k^{a_k}, then the sum of positive divisors is:

    sigma(n) = Product_{i=1}^{k} (p_i^{a_i + 1} - 1) / (p_i - 1)

**Proof.** Expanding the product of sums over each prime:

    sigma(n) = Sum_{0 <= e_i <= a_i} p_1^{e_1} * ... * p_k^{e_k}
             = (Sum_{e_1=0}^{a_1} p_1^{e_1}) * ... * (Sum_{e_k=0}^{a_k} p_k^{e_k})

Each factor is a geometric series:

    Sum_{e=0}^{a} p^e = (p^{a+1} - 1) / (p - 1)

The product of these geometric sums gives the formula. QED.

**Example.** sigma(12) = sigma(2^2 * 3) = (2^3 - 1)/(2-1) * (3^2 - 1)/(3-1) = 7 * 4 = 28.

### 1.5 T-Primes: Numbers with Exactly 3 Divisors

**Theorem 1.4.** An integer n > 1 has exactly 3 positive divisors if and only if
n = p^2 for some prime p.

**Proof.**
(<=) If n = p^2, then tau(n) = 2 + 1 = 3, and the divisors are {1, p, p^2}.

(=>) Suppose tau(n) = 3. Write n = p_1^{a_1} * ... * p_k^{a_k}. Then
(a_1+1)(a_2+1)...(a_k+1) = 3. Since 3 is prime, the only way to express 3 as a
product of integers >= 2 (since each a_i >= 1 implies a_i + 1 >= 2) is 3 = 3 itself,
with k = 1 and a_1 + 1 = 3, i.e., a_1 = 2. Hence n = p^2 for a single prime p. QED.

**Competitive programming application.** To check if n is a "T-prime," verify that
n is a perfect square and that sqrt(n) is prime. Precompute primes up to sqrt(10^12)
= 10^6 with a sieve.

---

## 2. Primality Testing and Sieves

### 2.1 Trial Division

**Algorithm.** To test whether n is prime, check divisibility by every integer d from
2 to floor(sqrt(n)).

**Correctness.** If n is composite, n = ab with 1 < a <= b < n. Then a <= sqrt(n)
(for if both a, b > sqrt(n), then ab > n, a contradiction). So at least one factor
is found by the trial.

**Complexity.** O(sqrt(n)).

**Optimization: 6k +/- 1 form.**
Every prime p > 3 satisfies p = 6k +/- 1 for some positive integer k.

*Proof.* Every integer falls into one of six residue classes modulo 6:
- 6k:     divisible by 6
- 6k + 1: possibly prime
- 6k + 2: divisible by 2
- 6k + 3: divisible by 3
- 6k + 4: divisible by 2
- 6k + 5: equivalent to 6(k+1) - 1, possibly prime

So any prime > 3 must be congruent to 1 or 5 (mod 6), i.e., of the form 6k +/- 1.

This lets us check only 2, 3, and then numbers of the form 6k +/- 1 up to sqrt(n),
reducing the constant factor by roughly 3x.

```cpp
bool is_prime(long long n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
```

### 2.2 Sieve of Eratosthenes

**Algorithm.** To find all primes up to N:
1. Create a boolean array is_prime[0..N], initialized to true.
2. Set is_prime[0] = is_prime[1] = false.
3. For each p from 2 to sqrt(N), if is_prime[p], mark is_prime[p*p], is_prime[p*p+p],
   is_prime[p*p+2p], ... as false.

**Key optimization: start from p^2.** When processing prime p, every composite number
p*k with k < p has already been marked by a smaller prime factor of k. The smallest
unmarked multiple is therefore p*p.

**Theorem 2.1 (Complexity).** The Sieve of Eratosthenes runs in O(N log log N) time.

**Proof sketch.** The total number of marking operations is:

    Sum_{p prime, p <= N} N/p = N * Sum_{p prime, p <= N} 1/p

By Mertens' second theorem (1874):

    Sum_{p prime, p <= N} 1/p = ln(ln N) + M + O(1/ln N)

where M ~ 0.2615 is the Meissel-Mertens constant. Therefore the total work is
O(N log log N). This is extremely close to O(N) in practice since log log N grows
so slowly (log log 10^9 ~ 3). QED.

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

**Bitset variant.** For very large N, use a bitset to reduce memory by 8x compared to
vector<bool> (which already packs bits, but bitset has better cache behavior):

```cpp
const int MAXN = 100000001;
bitset<MAXN> is_prime;

void sieve_bitset() {
    is_prime.set();           // all bits to 1
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; (long long)i * i < MAXN; i++)
        if (is_prime[i])
            for (int j = i * i; j < MAXN; j += i)
                is_prime[j] = 0;
}
```

### 2.3 Smallest Prime Factor (SPF) Sieve

**Idea.** Store spf[i] = smallest prime factor of i. This enables O(log n)
factorization of any number up to N.

**Construction (linear sieve variant):**

```cpp
vector<int> spf;

void build_spf(int N) {
    spf.assign(N + 1, 0);
    for (int i = 2; i <= N; i++) {
        if (spf[i] == 0) { // i is prime
            for (int j = i; j <= N; j += i)
                if (spf[j] == 0)
                    spf[j] = i;
        }
    }
}
```

**Factorization using SPF:**

```cpp
vector<pair<int,int>> factorize(int x) {
    vector<pair<int,int>> factors;
    while (x > 1) {
        int p = spf[x], cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        factors.push_back({p, cnt});
    }
    return factors;
}
```

**Complexity of factorization.** Each division reduces x by at least a factor of 2
(since spf[x] >= 2), so the number of divisions is at most log_2(x). Hence
factorization is O(log x).

More precisely: if x has the prime factorization p_1^{a_1} * ... * p_k^{a_k}, then
the number of divisions is exactly a_1 + a_2 + ... + a_k = Omega(x), the number of
prime factors counted with multiplicity. Since Omega(x) <= log_2(x), the bound follows.

---

## 3. GCD and the Euclidean Algorithm

### 3.1 Greatest Common Divisor

**Definition.** For integers a, b (not both zero), gcd(a, b) is the largest positive
integer that divides both a and b.

**Convention.** gcd(a, 0) = |a| for all a != 0.

### 3.2 The Euclidean Algorithm

**Theorem 3.1.** For integers a >= 0 and b > 0:

    gcd(a, b) = gcd(b, a mod b)

**Proof.** Let d = gcd(a, b). Write a = qb + r where r = a mod b and q = floor(a/b).

Claim: d | r. Since d | a and d | b, we have d | (a - qb) = r. Therefore d divides
both b and r, so d | gcd(b, r).

Claim: gcd(b, r) | d. Let d' = gcd(b, r). Then d' | b and d' | r. Since a = qb + r,
we get d' | a. So d' divides both a and b, hence d' | gcd(a, b) = d.

From d | gcd(b, r) and gcd(b, r) | d we conclude gcd(a, b) = gcd(b, r). QED.

**Implementation:**

```cpp
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
```

(In practice, use `__gcd(a, b)` or C++17 `std::gcd(a, b)`.)

### 3.3 Complexity of the Euclidean Algorithm

**Theorem 3.2.** The Euclidean algorithm on inputs a >= b > 0 terminates in at most
O(log(min(a, b))) steps.

**Proof.** We show that after every two consecutive steps, the first argument decreases
by at least a factor of 2.

Consider two steps: gcd(a, b) -> gcd(b, r) -> gcd(r, r') where r = a mod b and
r' = b mod r.

Case 1: r <= b/2. Then after one step the smaller argument dropped below b/2.

Case 2: r > b/2. Then b mod r = b - r < b/2. So after two steps, the remainder is
less than b/2.

In either case, within two steps the pair's smaller element is at most half what it
was. Since b can be halved at most O(log b) times before reaching 0, the total number
of steps is O(log(min(a, b))). QED.

**Remark (Worst case: Fibonacci numbers).** The inputs that maximize the number of steps
are consecutive Fibonacci numbers. gcd(F_{n+1}, F_n) requires exactly n-1 steps because
F_{n+1} mod F_n = F_{n-1}. This is essentially the converse of the halving argument:
Fibonacci numbers grow as phi^n where phi = (1+sqrt(5))/2, so n ~ log_{phi}(b) ~
1.44 log_2(b).

### 3.4 The Row-GCD Trick

**Problem pattern.** Compute gcd(a_1 + k, a_2 + k, ..., a_n + k) for many different
values of k.

**Key identity.** For any integers x, y:

    gcd(x, y) = gcd(x, y - x)

By extension:

    gcd(a_1+k, a_2+k, ..., a_n+k) = gcd(a_1+k, a_2-a_1, a_3-a_1, ..., a_n-a_1)

**Proof.** Let g = gcd(a_1+k, a_2+k, ..., a_n+k). Since g | (a_i+k) and g | (a_1+k),
we have g | (a_i - a_1) for all i >= 2. Also g | (a_1 + k). So
g | gcd(a_1+k, a_2-a_1, ..., a_n-a_1).

Conversely, let g' = gcd(a_1+k, a_2-a_1, ..., a_n-a_1). Since g' | (a_1+k) and
g' | (a_i - a_1), we get g' | (a_i + k) for all i. So g' | g.

Therefore g = g'. QED.

**Why this is powerful.** The differences a_i - a_1 are independent of k. Define
G = gcd(a_2-a_1, a_3-a_1, ..., a_n-a_1), computed once. Then for any k:

    answer = gcd(a_1 + k, G)

This reduces each query from O(n log V) to O(log V), where V is the value range.

---

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
