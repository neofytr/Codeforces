# String Algorithms: A Rigorous Treatment

## Section 1: Polynomial Rolling Hash

### Motivation

String comparison is O(n) in the worst case. Hashing compresses a string into a single
integer, enabling O(1) comparisons (with probabilistic guarantees). The challenge is
designing a hash function with:
1. Low collision probability
2. Efficient computation of substring hashes

### Definition

**Definition (Polynomial Rolling Hash)**: For a string s = s[0]s[1]...s[n-1] over an
alphabet mapped to positive integers, the polynomial hash is:

    hash(s) = ( s[0] * p^0 + s[1] * p^1 + ... + s[n-1] * p^{n-1} ) mod m

where:
- p is a prime number greater than the alphabet size (the **base**)
- m is a large prime number (the **modulus**)
- Characters are mapped to positive integers (a -> 1, b -> 2, ..., z -> 26)

**Why positive integers**: Mapping a -> 0 causes hash("a") = hash("aa") = hash("aaa") = 0.
Mapping a -> 1 avoids this degeneracy: different strings of 'a's have different hashes.

**Why p > alphabet size**: If p <= |alphabet|, two single characters a, b with a != b could
satisfy a * p^0 = b * p^0 (mod m), but since 0 < a, b < p < m (a prime), this is impossible.
More generally, choosing p > |alphabet| ensures single-character strings have distinct hashes.

### Parameter Choices

Recommended parameters:
- **p = 31**: Prime, greater than 26 (for lowercase English letters). The choice p = 31
  is conventional; p = 37 works too.
- **m = 10^9 + 9**: A large prime. Being prime ensures the multiplicative group mod m has
  order m-1, maximizing the period of p^i mod m.

**Alternative**: m = 10^9 + 7 is also widely used, but avoid using both m values in a
single-hash scheme. Reserve one for double hashing.

### Prefix Hash Array

**Construction**: Define the prefix hash array H[0..n]:

    H[0] = 0
    H[i] = H[i-1] + s[i-1] * p^{i-1}  (mod m)

Expanding: H[i] = s[0]*p^0 + s[1]*p^1 + ... + s[i-1]*p^{i-1} (mod m).

Also precompute the power array: pw[0] = 1, pw[i] = pw[i-1] * p (mod m).

### Substring Hash Extraction

**Theorem**: hash(s[l..r]) * p^l = H[r+1] - H[l]  (mod m).

**Proof**:

    H[r+1] - H[l] = sum_{i=l}^{r} s[i] * p^i  (mod m)
                   = p^l * sum_{i=l}^{r} s[i] * p^{i-l}  (mod m)
                   = p^l * ( s[l]*p^0 + s[l+1]*p^1 + ... + s[r]*p^{r-l} )  (mod m)
                   = p^l * hash(s[l..r])  (mod m)

**Two approaches to compare substrings**:

**Approach 1 (Multiply up)**: To compare hash(s[l1..r1]) with hash(s[l2..r2]):
Instead of extracting the raw hashes, compare:

    (H[r1+1] - H[l1]) * pw[l2]  ==  (H[r2+1] - H[l2]) * pw[l1]  (mod m)

This avoids computing modular inverses. Both sides equal hash * p^{l1+l2}.

**Approach 2 (Inverse)**: Precompute inv_pw[i] = modular inverse of pw[i].
Then hash(s[l..r]) = (H[r+1] - H[l]) * inv_pw[l] (mod m).

Approach 1 is simpler and avoids the cost of computing inverses.

### Collision Analysis

**Theorem (Schwartz-Zippel Lemma, special case)**: For two distinct strings s, t of the
same length, if p is chosen uniformly at random from Z_m (the integers mod m, with m prime),
then:

    P(hash(s) = hash(t)) <= (n-1) / m

where n is the string length.

**Proof sketch**: hash(s) - hash(t) is a nonzero polynomial of degree at most n-1 in p
(over the field Z_m). A nonzero polynomial of degree d over a field has at most d roots.
Therefore the number of "bad" values of p is at most n-1, giving probability <= (n-1)/m.

**In practice**: With fixed p and random-looking strings, the heuristic collision
probability for a single comparison is approximately 1/m. For k comparisons:

    P(any collision) <= k/m  (union bound)

With m ~ 10^9 and k ~ 10^5 comparisons, this is ~10^{-4}. Acceptable for most
competitive programming problems, but hackable.

### Double Hashing

**Definition**: Compute two independent hashes with different (p, m) pairs:
- Hash 1: (p_1, m_1) = (31, 10^9 + 9)
- Hash 2: (p_2, m_2) = (37, 10^9 + 7)

Two strings "collide" only if both hashes match.

**Collision probability**: Assuming independence (justified by different primes),

    P(collision) ~ 1/(m_1 * m_2) ~ 10^{-18}

This is astronomically small. With k = 10^6 comparisons:

    P(any collision) <= k / (m_1 * m_2) ~ 10^{-12}

Double hashing is effectively unhackable.

### Implementation

```cpp
const long long MOD1 = 1e9 + 9, MOD2 = 1e9 + 7;
const long long BASE1 = 31, BASE2 = 37;

struct HashedString {
    int n;
    vector<long long> h1, h2, pw1, pw2;

    HashedString(const string& s) : n(s.size()), h1(n+1), h2(n+1), pw1(n+1), pw2(n+1) {
        pw1[0] = pw2[0] = 1;
        h1[0] = h2[0] = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a' + 1;  // 1-indexed
            h1[i+1] = (h1[i] + c * pw1[i]) % MOD1;
            h2[i+1] = (h2[i] + c * pw2[i]) % MOD2;
            pw1[i+1] = pw1[i] * BASE1 % MOD1;
            pw2[i+1] = pw2[i] * BASE2 % MOD2;
        }
    }

    // Compare hash(s[l1..r1]) with hash(s[l2..r2])
    // Using the multiply-up approach
    bool equal(int l1, int r1, int l2, int r2) {
        long long lhs1 = (h1[r1+1] - h1[l1] + MOD1) % MOD1 * pw1[l2] % MOD1;
        long long rhs1 = (h1[r2+1] - h1[l2] + MOD1) % MOD1 * pw1[l1] % MOD1;
        long long lhs2 = (h2[r1+1] - h2[l1] + MOD2) % MOD2 * pw2[l2] % MOD2;
        long long rhs2 = (h2[r2+1] - h2[l2] + MOD2) % MOD2 * pw2[l1] % MOD2;
        return lhs1 == rhs1 && lhs2 == rhs2;
    }
};
```

---

## Section 2: Applications of Hashing

### Application 1: Pattern Matching (Rabin-Karp)

**Problem**: Find all occurrences of pattern P (length m) in text T (length n).

**Algorithm**:
1. Compute hash(P).
2. For each position i in [0, n-m], compute hash(T[i..i+m-1]).
3. If hashes match, verify character-by-character (to handle collisions).

**Using prefix hashes**: Precompute the prefix hash array of T. Extract each window's
hash in O(1). Total: O(n + m) expected time.

```cpp
// Find all occurrences of pattern in text
vector<int> rabin_karp(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    if (m > n) return {};

    HashedString ht(text);

    // Compute hash of pattern separately
    long long ph1 = 0, ph2 = 0;
    long long pw1 = 1, pw2 = 1;
    for (int i = 0; i < m; i++) {
        int c = pattern[i] - 'a' + 1;
        ph1 = (ph1 + c * pw1) % MOD1;
        ph2 = (ph2 + c * pw2) % MOD2;
        if (i > 0) {
            pw1 = pw1 * BASE1 % MOD1;
            pw2 = pw2 * BASE2 % MOD2;
        }
    }
    // Careful: pw1, pw2 now hold BASE^{m-1}; we need proper comparison

    vector<int> matches;
    for (int i = 0; i <= n - m; i++) {
        // Compare hash(text[i..i+m-1]) with hash(pattern)
        // hash(text[i..i+m-1]) * p^i = ht.h[i+m] - ht.h[i]
        // hash(pattern) * p^0 = ph
        // So compare: (ht.h[i+m] - ht.h[i]) == ph * ht.pw[i]
        long long lhs1 = (ht.h1[i+m] - ht.h1[i] + MOD1) % MOD1;
        long long rhs1 = ph1 * ht.pw1[i] % MOD1;
        long long lhs2 = (ht.h2[i+m] - ht.h2[i] + MOD2) % MOD2;
        long long rhs2 = ph2 * ht.pw2[i] % MOD2;
        if (lhs1 == rhs1 && lhs2 == rhs2) {
            matches.push_back(i);
        }
    }
    return matches;
}
```

**Complexity**: O(n + m) preprocessing, O(n) for the scan, O(m) per match for verification
(omitted above since double hashing makes false positives negligible). Expected total: O(n + m).

**Comparison with KMP**: KMP is deterministic O(n + m) and avoids hash collisions entirely.
Rabin-Karp's advantage is simplicity and extensibility to 2D pattern matching and
multi-pattern matching.

### Application 2: Longest Common Substring

**Problem**: Given strings s and t, find the length of their longest common substring.

**Algorithm**: Binary search on the answer length L.

For a given L:
1. Compute all hashes of length-L substrings of s. Store in a hash set.
2. Compute all hashes of length-L substrings of t. Check if any is in the set.
3. If a match exists, L is achievable; try larger. Otherwise, try smaller.

**Correctness of binary search**: If a common substring of length L exists, then common
substrings of all lengths L' < L also exist (take any prefix of length L'). So the
predicate "common substring of length L exists" is monotone (true up to some L*, then false).

**Complexity**: O((n + m) * log(min(n, m))). Each binary search step does O(n + m) work
for hashing and set operations.

### Application 3: Counting Distinct Substrings

**Problem**: Count the number of distinct substrings of a string s of length n.

**Approach 1 (Hashing)**: For each length L from 1 to n, hash all substrings of length L
and count the distinct hashes. Total: O(n^2 / 64) with bitset optimization, or O(n^2) with
hash sets.

**Approach 2 (Suffix Array)**: The number of distinct substrings = n(n+1)/2 - sum(LCP array).
This is O(n log n) or O(n) with SA-IS and Kasai's algorithm. Strictly superior for large n.

---

## Section 3: Beyond Basic Hashing

### Hashing for Palindrome Queries

**Problem**: Given a string s, answer queries "is s[l..r] a palindrome?"

**Approach**: Maintain two hash arrays:
- Forward hash of s: H_f
- Forward hash of reverse(s): H_r (equivalently, hash s right-to-left)

s[l..r] is a palindrome iff hash(s[l..r]) == hash(reverse(s[l..r])).

The reverse of s[l..r] corresponds to s_rev[n-1-r..n-1-l] where s_rev = reverse(s).
Compare the two hashes in O(1).

### Anti-Hash Tests and Defensive Hashing

**Problem**: In competitive programming, adversarial test cases ("anti-hash tests") can
force collisions for a specific (p, m) pair.

**Thue-Morse-based attack**: For a known (p, m), construct two distinct strings with
the same hash by finding a root of the hash-difference polynomial mod m.

**Defenses**:
1. **Double hashing** (two independent hash functions): probability ~10^{-18}
2. **Randomized base**: Choose p uniformly at random from [2, m-1] at runtime.
   The adversary cannot predict p, so Schwartz-Zippel gives worst-case guarantees.
3. **Both**: Randomized double hashing is maximally robust.

```cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const long long BASE1 = uniform_int_distribution<long long>(2, MOD1 - 1)(rng);
const long long BASE2 = uniform_int_distribution<long long>(2, MOD2 - 1)(rng);
```

### 2D Hashing

For an n x m matrix, compute a 2D polynomial hash:

    hash(A) = sum_{i,j} A[i][j] * p1^i * p2^j  (mod m)

Use two different bases p1 (for rows) and p2 (for columns). Precompute prefix hashes
along both dimensions to extract any submatrix hash in O(1).

**Application**: 2D pattern matching. Given a large matrix T and a small pattern matrix P,
find all positions where P appears in T. Binary hash over rows, then hash the column of
row-hashes. O(nm + rc) where T is n x m and P is r x c.

---

## Section 4: Comparison of String Matching Algorithms

### Summary Table

| Algorithm    | Preprocessing | Matching   | Deterministic? | Multi-pattern? |
|-------------|---------------|------------|----------------|----------------|
| Naive        | O(1)          | O(nm)      | Yes            | No             |
| Rabin-Karp   | O(n + m)      | O(n) exp.  | No (hashing)   | Yes (easily)   |
| KMP          | O(m)          | O(n)       | Yes            | No             |
| Aho-Corasick | O(sum |P_i|)  | O(n + occ) | Yes            | Yes            |
| Z-algorithm  | O(n + m)      | O(n + m)   | Yes            | No             |
| Suffix Array | O(n log n)    | O(m log n) | Yes            | Yes            |

### When to Use Hashing

**Use hashing when**:
- You need to compare many pairs of substrings (hashing gives O(1) per comparison)
- The problem involves 2D pattern matching
- You need a quick implementation and can tolerate probabilistic guarantees
- You need to binary search on a string property (e.g., longest common substring)

**Avoid hashing when**:
- Deterministic guarantees are required and the judge has anti-hash tests
- A single pattern match suffices (KMP is simpler and deterministic)
- You need all occurrences of multiple patterns (Aho-Corasick is purpose-built)

---

## Section 5: Modular Arithmetic for Hashing

### Avoiding Overflow

In C++, multiplication of two `long long` values (up to ~10^{18}) can overflow.
Since our modulus m ~ 10^9, the product of two values mod m is at most (10^9)^2 = 10^{18},
which fits in a `long long` (max ~9.2 * 10^{18}).

**Safe pattern**:
```cpp
long long mod_mul(long long a, long long b, long long m) {
    return (a % m) * (b % m) % m;
}
```

Ensure both operands are reduced mod m before multiplying. The product fits in `long long`
since both operands are < 10^9.

### Computing Modular Inverse

For hash extraction with division by p^l, compute the modular inverse via Fermat's
little theorem: for prime m, a^{-1} = a^{m-2} mod m.

```cpp
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

long long mod_inv(long long a, long long m) {
    return power(a, m - 2, m);  // Fermat's little theorem
}
```

**Precompute inverse powers**: inv_pw[0] = 1, inv_pw[i] = inv_pw[i-1] * p^{-1} mod m.
Or equivalently, inv_pw[i] = power(pw[i], m-2, m). Precomputing all n inverse powers
costs O(n) multiplications (using the recurrence) or O(n log m) (using exponentiation
for each, but this is wasteful).

**Efficient approach**: Compute p_inv = power(p, m-2, m) once, then:
inv_pw[0] = 1, inv_pw[i] = inv_pw[i-1] * p_inv % m. Total: O(n).

---

## Section 6: Common Pitfalls

1. **Zero-indexed characters**: Mapping 'a' -> 0 causes leading 'a's to vanish.
   Always use 'a' -> 1.

2. **Negative modular arithmetic**: In C++, (a - b) % m can be negative if a < b.
   Always use ((a - b) % m + m) % m.

3. **Single hash with known parameters**: If the judge knows your (p, m), they can
   construct adversarial inputs. Use double hashing or randomized bases.

4. **Comparing substrings of different strings**: Ensure both strings use the same
   (p, m) and the same character mapping. Prefix hash arrays are string-specific;
   the comparison formula must account for different power offsets.

5. **Integer overflow**: Always reduce intermediate results mod m before multiplying.
   Even `long long` overflows at ~9.2 * 10^{18}; two unreduced values near 10^9
   can produce a product near 10^{18}, which is safe, but three such values multiplied
   without intermediate reduction will overflow.

6. **Off-by-one in substring indexing**: The hash of s[l..r] (inclusive on both ends)
   uses H[r+1] - H[l]. Mixing 0-indexed and 1-indexed strings is a common source of bugs.
   Establish a convention and stick to it.
