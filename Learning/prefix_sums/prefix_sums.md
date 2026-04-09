# Prefix Sums: A Rigorous Treatment

## 1. The Algebraic Foundation

### 1.1 Definition

Let **a** = (a_0, a_1, ..., a_{n-1}) be a finite sequence of elements drawn from an abelian
group (G, +). The **prefix sum array** P = (P_0, P_1, ..., P_n) is defined by:

    P_0 = 0    (the identity element of G)
    P_i = P_{i-1} + a_{i-1}    for i = 1, 2, ..., n

Equivalently, by unrolling the recurrence:

              i-1
    P_i  =   sum   a_j
              j=0

Note that P has n+1 entries for an input of n entries. The extra element P_0 = 0 is not
a convenience -- it is essential. It represents the empty prefix and ensures that every
subarray, including those starting at index 0, can be expressed uniformly.

### 1.2 The Fundamental Theorem of Prefix Sums

**Theorem 1.1 (Range Sum via Prefix Sums).**
For any 0 <= l <= r <= n, the sum over the half-open interval [l, r) satisfies:

    r-1
    sum   a_j  =  P_r - P_l
    j=l

**Proof.** Write the difference as a telescoping sum:

    P_r - P_l  =  sum_{i=l+1}^{r} (P_i - P_{i-1})
               =  sum_{i=l+1}^{r} a_{i-1}
               =  sum_{j=l}^{r-1} a_j              (substituting j = i - 1)

The key step is that each term P_i - P_{i-1} = a_{i-1} by definition, and all
intermediate terms cancel. This is the discrete analogue of the Fundamental Theorem
of Calculus:  integral_a^b f'(x) dx = f(b) - f(a).                                 QED

**Corollary 1.2.** Prefix sums reduce any range sum query to O(1) after O(n) preprocessing.

### 1.3 The Group-Theoretic Perspective

The construction above works whenever:
  (i)   the operation + is associative,
  (ii)  there exists an identity element 0,
  (iii) every element has an inverse (-a for addition, a^{-1} for multiplication).

That is, the construction works for any **group** (G, *). Let us examine key instances:

**Example 1: (Z, +).** Standard prefix sums. Inverse is negation.

**Example 2: (Z/2Z, XOR).** Define:

    X_0 = 0
    X_i = X_{i-1} XOR a_{i-1}

Then XOR(a_l, ..., a_{r-1}) = X_r XOR X_l.

This works because XOR is its own inverse: for any x, x XOR x = 0. Thus "subtraction"
in this group is the same as addition. This is why prefix XOR is so clean.

**Example 3: (Z/pZ \ {0}, *).** Multiplication modulo a prime p. Every nonzero element
has a multiplicative inverse (by Fermat's little theorem, a^{-1} = a^{p-2} mod p).
So prefix products modulo p support range product queries.

**Non-example: (Z, min).** The operation min is associative and has an identity
(+infinity), but there is no inverse -- given min(a, b) = a, you cannot recover b.
The prefix sum technique fails. Range min queries require fundamentally different
structures: sparse tables (O(n log n) / O(1)), or segment trees (O(n) / O(log n)).

**Non-example: (Z, gcd).** Similarly, gcd is associative and has an identity (0), but
lacks inverses. Knowing gcd(a, b) and a does not determine b.

**Takeaway.** Before reaching for prefix sums, ask: does my operation form a group?
If yes, prefix sums give O(1) range queries. If no, you need a different data structure.


## 2. The Counting Trick (Prefix Sum + HashMap)

This is arguably the single most important pattern involving prefix sums. It transforms
a problem about subarrays into a problem about pairs of prefix sums.

### 2.1 Counting Subarrays with Sum Equal to k

**Problem.** Given a = (a_0, ..., a_{n-1}) and an integer k, count the number of
subarrays [l, r) such that sum_{j=l}^{r-1} a_j = k.

**Theorem 2.1.** The number of such subarrays equals the number of pairs (l, r)
with 0 <= l < r <= n and P_l = P_r - k.

**Proof.** By Theorem 1.1, sum_{j=l}^{r-1} a_j = k if and only if P_r - P_l = k,
i.e., P_l = P_r - k. The pairs (l, r) with l < r are in bijection with subarrays
of positive length.                                                                  QED

**Algorithm.** Iterate r from 0 to n. Maintain a hash map freq where freq[v] counts
the number of indices l < r with P_l = v. For each r:

    1. Add freq[P_r - k] to the answer.
    2. Increment freq[P_r].

The order matters: we query before inserting to ensure l < r (we never count l = r,
which would correspond to an empty subarray).

**Complexity.** O(n) expected time, O(n) space.

### 2.2 Proof of Correctness

**Claim.** After processing index r, freq[v] = |{l : 0 <= l <= r, P_l = v}|.

Proof is by induction on r. Initially freq is empty and r = 0; we query freq[P_0 - k]
(which is 0 since freq is empty), then insert P_0. Inductively, when we process r,
freq contains exactly the entries for l = 0, 1, ..., r-1. We query how many of these
equal P_r - k, then insert P_r. Each valid pair (l, r) is counted exactly once: at the
moment r is processed.                                                               QED

### 2.3 Modular Variant

**Problem.** Count subarrays with sum divisible by m.

**Theorem 2.2.** sum_{j=l}^{r-1} a_j = 0 (mod m) if and only if P_l = P_r (mod m).

So we count pairs of equal values in the sequence (P_0 mod m, P_1 mod m, ..., P_n mod m).
If value v appears f_v times, the answer is sum_v C(f_v, 2) = sum_v f_v(f_v - 1)/2.

### 2.4 The "Good Subarrays" Transformation

A subarray [l, r) is "good" if its sum equals its length:

    sum_{j=l}^{r-1} a_j = r - l

Define the transformed sequence a'_j = a_j - 1. Then:

    sum_{j=l}^{r-1} a'_j = sum_{j=l}^{r-1} a_j - (r - l)

So the subarray is "good" if and only if sum a'_j over [l, r) equals 0. We have reduced
the problem to Section 2.3 with k = 0. Count equal prefix sums of the transformed array.

This illustrates a general principle: many subarray conditions can be reformulated as
"transformed subarray sum equals constant" by a clever change of variables.

### 2.5 A Note on Hash Maps and Adversarial Inputs

C++ unordered_map uses a hash function that, by default, is the identity for integers.
An adversary can craft inputs where all prefix sums collide in the same bucket, degrading
lookups from O(1) to O(n), yielding O(n^2) total time.

**Defense.** Use a custom hash that mixes bits unpredictably:

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

    unordered_map<long long, int, custom_hash> freq;

The FIXED_RANDOM seed changes each run, so no fixed input can reliably cause collisions.


## 3. Two-Dimensional Prefix Sums

### 3.1 Definition

Let a be an m x n matrix. Define the 2D prefix sum P of size (m+1) x (n+1) by:

    P[0][j] = 0  for all j
    P[i][0] = 0  for all i

              i-1   j-1
    P[i][j] = sum   sum  a[r][c]
              r=0   c=0

That is, P[i][j] is the sum of all elements in the rectangle [0, i) x [0, j).

### 3.2 Construction

**Theorem 3.1 (2D Prefix Sum Recurrence).**

    P[i][j] = a[i-1][j-1] + P[i-1][j] + P[i][j-1] - P[i-1][j-1]

**Proof.** By inclusion-exclusion on overlapping L-shaped regions:

    P[i-1][j] covers [0, i-1) x [0, j)        -- everything except row i-1
    P[i][j-1] covers [0, i) x [0, j-1)         -- everything except column j-1

Their union covers [0, i) x [0, j) minus {a[i-1][j-1]}, but the intersection
[0, i-1) x [0, j-1) is counted twice. So:

    P[i][j] = P[i-1][j] + P[i][j-1] - P[i-1][j-1] + a[i-1][j-1]

The subtraction removes the double-counted rectangle; the addition of a[i-1][j-1]
adds the single missing cell.                                                        QED

### 3.3 Range Query

**Theorem 3.2 (2D Range Sum).**
The sum over the rectangle [r1, r2) x [c1, c2) is:

    S = P[r2][c2] - P[r1][c2] - P[r2][c1] + P[r1][c1]

**Proof.** Apply inclusion-exclusion. Define R = [r1, r2) x [c1, c2).

    P[r2][c2] = sum over [0, r2) x [0, c2)          -- contains R, plus three extra regions
    P[r1][c2] = sum over [0, r1) x [0, c2)           -- the rows above R (plus top-left)
    P[r2][c1] = sum over [0, r2) x [0, c1)           -- the columns left of R (plus top-left)
    P[r1][c1] = sum over [0, r1) x [0, c1)           -- the top-left corner

    P[r2][c2] - P[r1][c2] subtracts the top strip, but leaves [0,r1) x [0,c1) removed.
    Further subtracting P[r2][c1] removes the left strip, but now [0,r1) x [0,c1) has
    been subtracted twice. Adding P[r1][c1] corrects this.

Formally:

    S = P[r2][c2] - P[r1][c2] - P[r2][c1] + P[r1][c1]

by Mobius inversion on the poset of rectangles anchored at the origin.                QED

### 3.4 Complexity

Construction is O(mn). Each query is O(1). This extends to d dimensions with
2^d terms per query (inclusion-exclusion over 2^d corners of a d-dimensional box).


## 4. Maximum Subarray Sum (Kadane's Algorithm)

### 4.1 Derivation from Prefix Sums

**Theorem 4.1.** The maximum subarray sum of a = (a_0, ..., a_{n-1}) equals:

    max_{0 <= l < r <= n} (P_r - P_l)  =  max_{1 <= r <= n} (P_r - min_{0 <= l <= r} P_l)

**Proof.** The first equality is by Theorem 1.1. For the second, observe that for
fixed r, P_r - P_l is maximized when P_l is minimized over l in [0, r]. Taking the
outer maximum over r gives the result.                                               QED

**Algorithm (Kadane).**

    prefix_min = 0      // P_0 = 0
    current_prefix = 0  // P_0
    answer = -infinity

    for i = 0 to n-1:
        current_prefix += a[i]               // now current_prefix = P_{i+1}
        answer = max(answer, current_prefix - prefix_min)
        prefix_min = min(prefix_min, current_prefix)

This is Kadane's algorithm, derived not as a clever trick but as a direct consequence
of the prefix sum framework. The "running minimum" is the key insight: we do not need
to search over all l for each r, because the minimum is monotonically maintainable.

### 4.2 The Flipping Game Reduction

**Problem (Flipping Game).** Given a binary array of length n, you must flip all bits
in exactly one subarray [l, r]. Maximize the number of 1s after flipping.

Let z_i = 1 if a_i = 0, and -1 if a_i = 1. Flipping [l, r] changes the count of 1s by
sum_{j=l}^{r} z_j (each 0 becomes 1: gain +1; each 1 becomes 0: gain -1).

The answer is (original count of 1s) + max subarray sum of z.

Now let us connect this to prefix sums. Define P_i = sum_{j=0}^{i-1} a_j (prefix sum of
the original binary array). The number of zeros in [l, r] is (r - l + 1) - (P_{r+1} - P_l).
The number of ones is P_{r+1} - P_l. So flipping gain = (r-l+1) - 2(P_{r+1} - P_l).

Define del_i = 2P_i - i. Then:

    flipping gain over [l, r] = -(del_{r+1} - del_l) = del_l - del_{r+1}

So we want max_{l <= r} (del_l - del_{r+1}), which is max_{l < r'} (del_l - del_{r'}).
This is the "maximum drop" problem, equivalent to max subarray sum on the negated
difference sequence, solvable in O(n) by the same prefix-min technique of Section 4.1.

### 4.3 Minimum Subarray Sum

By symmetry, the minimum subarray sum is:

    min_{0 <= l < r <= n} (P_r - P_l) = min_{r} (P_r - max_{l <= r} P_l)

Replace "min" with "max" in the tracking variable. This duality is immediate from the
prefix sum formulation but obscured in the traditional "Kadane" presentation.


## 5. Prefix Sums and Binary Search

### 5.1 Monotonicity

**Theorem 5.1.** If a_i >= 0 for all i, then P is monotonically non-decreasing:

    P_0 <= P_1 <= ... <= P_n

**Proof.** P_i - P_{i-1} = a_{i-1} >= 0.                                           QED

### 5.2 Applications of Monotonicity

When P is non-decreasing, binary search applies directly on P. This unlocks several
powerful query types:

**Query 1: Smallest r such that sum a[l..r] >= k (for fixed l).**

We need the smallest r >= l such that P_{r+1} - P_l >= k, i.e., P_{r+1} >= P_l + k.
Since P is non-decreasing, use lower_bound on P[l+1..n] for value P_l + k.
Time: O(log n) per query.

**Query 2: Shortest subarray starting at or after l with sum >= k.**

Binary search finds the endpoint. Repeating for all l and taking the minimum gives
O(n log n). (A two-pointer approach gives O(n), but the binary search version
generalizes to harder settings.)

### 5.3 Connection to the Two-Pointer Technique

The two-pointer technique for "shortest/longest subarray with sum >= k" (with non-negative
elements) relies implicitly on the monotonicity of prefix sums.

Consider maintaining two pointers l, r. As r advances, P_r increases. For fixed r, the
set of valid l (those with P_r - P_l >= k) forms a prefix [0, l_max]. As r increases,
l_max can only increase (since P_r increases, more l values become valid). This monotonicity
in l_max is what allows the two-pointer technique to work in O(n).

**When elements can be negative**, P is no longer monotone. Two pointers fail. You need
a deque-based approach or a balanced BST on prefix sums (O(n log n)).

### 5.4 Prefix Sums on Sorted Structures

If you need prefix sums of a dynamically changing array with point updates and prefix
sum queries, use a **Fenwick tree (Binary Indexed Tree)**. It supports:

    - Point update: O(log n)
    - Prefix sum query: O(log n)

The Fenwick tree is, in essence, a compressed representation of the prefix sum array that
supports efficient updates. Its structure mirrors the binary representation of indices --
a beautiful connection between prefix sums and binary arithmetic.


## 6. Advanced Applications

### 6.1 Frequency Prefix Sums

Let s be a string over alphabet Sigma. For each character c in Sigma, define:

    count[c][0] = 0
    count[c][i] = |{j : 0 <= j < i, s[j] = c}|

Then the number of occurrences of c in s[l..r) is count[c][r] - count[c][l].

**Complexity.** O(|Sigma| * n) preprocessing, O(1) per query. For small alphabets
(e.g., lowercase English letters, |Sigma| = 26), this is extremely practical.

This technique generalizes: replace characters with any discrete classification of
elements, and you get O(1) range frequency queries.

### 6.2 Prefix GCD and Suffix GCD

Although GCD is not invertible (and so prefix GCD does not support range queries),
prefix and suffix GCD arrays together enable a useful trick.

Define:

    G_prefix[0] = 0,   G_prefix[i] = gcd(a_0, a_1, ..., a_{i-1})
    G_suffix[n] = 0,    G_suffix[i] = gcd(a_i, a_{i+1}, ..., a_{n-1})

Then gcd of all elements except a_i is:

    gcd(G_prefix[i], G_suffix[i+1])

This allows O(n) preprocessing and O(1) "GCD excluding one element" queries. A common
pattern in problems asking "remove one element to maximize/minimize something."

### 6.3 The Duality with Difference Arrays

**Theorem 6.1.** Let Sigma denote the prefix sum operator and Delta the difference operator:

    (Sigma(a))_i = sum_{j=0}^{i} a_j
    (Delta(a))_0 = a_0,    (Delta(a))_i = a_i - a_{i-1}  for i >= 1

Then Sigma and Delta are inverses: Sigma(Delta(a)) = a and Delta(Sigma(a)) = a.

**Proof.** For the first:

    (Sigma(Delta(a)))_i = sum_{j=0}^{i} (Delta(a))_j
                        = a_0 + sum_{j=1}^{i} (a_j - a_{j-1})
                        = a_0 + (a_i - a_0)       (telescoping)
                        = a_i

For the second:

    (Delta(Sigma(a)))_0 = (Sigma(a))_0 = a_0
    (Delta(Sigma(a)))_i = (Sigma(a))_i - (Sigma(a))_{i-1}
                        = sum_{j=0}^{i} a_j - sum_{j=0}^{i-1} a_j
                        = a_i                                                        QED

This duality is the discrete analogue of the Fundamental Theorem of Calculus:
differentiation and integration are inverse operations. Every technique for prefix sums
has a "dual" technique for difference arrays, and vice versa.

### 6.4 Prefix Sums of Prefix Sums

Applying the prefix sum operator k times yields the k-th order prefix sums. This is
related to polynomial interpolation: if a is a polynomial sequence of degree d, then
its k-th order prefix sums are polynomial of degree d + k.

The k-th order prefix sum of the constant sequence (1, 1, 1, ...) gives the binomial
coefficients C(n+k-1, k). This connection to combinatorics is deep and occasionally
useful in competitive programming (e.g., distributing items into bins).
