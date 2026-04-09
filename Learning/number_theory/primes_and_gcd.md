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
