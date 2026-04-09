# Bit Manipulation: A Rigorous Treatment

## Section 1: Bitwise Algebra

### The Galois Field GF(2)

A single bit inhabits the **Galois field** GF(2) = ({0, 1}, +, *), where:
- Addition (+) is XOR: 0+0=0, 0+1=1, 1+0=1, 1+1=0
- Multiplication (*) is AND: 0*0=0, 0*1=0, 1*0=0, 1*1=1

This is a proper field: every nonzero element (just 1) has a multiplicative inverse (1),
and every element is its own additive inverse (a + a = 0 for all a in GF(2)).

For n-bit integers, we work in GF(2)^n: vectors of n bits with component-wise XOR and AND.
AND distributes over XOR:

    a & (b ^ c) = (a & b) ^ (a & c)

**Proof**: For each bit position independently, this is a * (b + c) = a*b + a*c in GF(2),
which holds because GF(2) is a field (distributivity is a field axiom).

Note: OR does NOT distribute over XOR. The bitwise operations form a Boolean algebra
under (AND, OR, NOT), but the ring structure uses (XOR, AND).

### De Morgan's Laws

**Theorem (De Morgan)**:
1. ~(a & b) = (~a) | (~b)
2. ~(a | b) = (~a) & (~b)

**Proof**: Verify for each bit position independently. For a single bit:
- Case 1: a=0, b=0: ~(0&0)=~0=1, (~0)|(~0)=1|1=1. Check.
- Case 2: a=0, b=1: ~(0&1)=~0=1, (~0)|(~1)=1|0=1. Check.
- Case 3: a=1, b=0: symmetric to Case 2. Check.
- Case 4: a=1, b=1: ~(1&1)=~1=0, (~1)|(~1)=0|0=0. Check.

Law 2 follows by duality (substitute a'=~a, b'=~b into Law 1 and complement both sides).

### XOR Properties

**(i) Self-inverse**: a ^ a = 0.
Proof: For each bit, x + x = 0 in GF(2).

**(ii) Identity**: a ^ 0 = a.
Proof: 0 is the additive identity in GF(2).

**(iii) Associativity and Commutativity**: Inherited from addition in GF(2).

**(iv) Cancellation**: a ^ b = 0 implies a = b.
Proof: XOR both sides with a: a ^ a ^ b = a ^ 0, so 0 ^ b = a, so b = a.

**(v) Cancellation (general form)**: a ^ b = a ^ c implies b = c.
Proof: XOR both sides with a and apply (i) and (ii).

These properties make XOR the workhorse of competitive programming: it is invertible,
has no "information loss" (unlike AND or OR), and supports prefix-sum-like constructions.

### The Identity n & (n-1): Clearing the Lowest Set Bit

**Theorem**: For any positive integer n, the operation n & (n-1) clears the lowest set bit
of n and leaves all other bits unchanged.

**Proof**: Let n have binary representation:

    n = [prefix]1[000...0]
                 ^         ^
                 |         |
          lowest set bit   k trailing zeros

Then n-1 is obtained by the standard binary subtraction (borrow propagation):

    n-1 = [prefix]0[111...1]

The prefix is identical in both n and n-1. The bit where n has its lowest 1 becomes 0
in n-1. The k trailing zeros of n become k ones in n-1. Therefore:

    n & (n-1) = [prefix]0[000...0]

The lowest set bit is cleared; all higher bits are preserved. QED.

### Brian-Kernighan's Algorithm

**Algorithm**: To count the number of set bits (popcount) of n:

```cpp
int count = 0;
while (n) {
    n = n & (n - 1);  // clear lowest set bit
    count++;
}
```

**Correctness**: Each iteration clears exactly one set bit (by the theorem above) and
increments the counter. The loop terminates when n = 0, i.e., when all bits are cleared.
Therefore count equals the number of set bits.

**Complexity**: O(popcount(n)) iterations. This is strictly better than the naive O(log n)
bit-scanning approach when popcount is small.

### Power of 2 Check

**Theorem**: A positive integer n is a power of 2 if and only if n & (n-1) == 0.

**Proof**:
(=>) If n = 2^k, then n has exactly one set bit (bit k). By the clearing theorem,
n & (n-1) clears that bit, yielding 0.

(<=) If n & (n-1) == 0 and n > 0, suppose n has two or more set bits. Then clearing
the lowest set bit leaves at least one set bit, so n & (n-1) > 0. Contradiction.
Therefore n has exactly one set bit, so n = 2^k for some k >= 0. QED.

**Code**: `n > 0 && (n & (n-1)) == 0`

The n > 0 guard is essential: 0 & (-1) = 0, but 0 is not a power of 2.

---

## Section 2: Subset Enumeration via Bitmasks

### Representation

A subset S of the universe U = {0, 1, ..., n-1} is represented as an n-bit integer mask:

    bit i of mask is 1  <=>  element i is in S

This bijection between subsets of U and integers in [0, 2^n) is the foundation of
bitmask techniques.

### Set Operations as Bitwise Operations

| Set Operation          | Bitwise     | Justification                                |
|------------------------|-------------|----------------------------------------------|
| S union T              | S \| T      | bit i set iff i in S or i in T               |
| S intersect T          | S & T       | bit i set iff i in S and i in T              |
| complement of S        | ~S & ((1<<n)-1) | flip all bits within the n-bit universe |
| S \ T (set difference) | S & ~T      | bit i set iff i in S and i not in T          |
| S symmetric diff T     | S ^ T       | bit i set iff i in exactly one of S, T       |
| S is subset of T       | (S & T) == S | equivalently, (S \| T) == T                |
| S is empty             | S == 0      |                                              |
| |S| (cardinality)      | __builtin_popcount(S) |                                  |

### Iterating All Subsets

```cpp
for (int mask = 0; mask < (1 << n); mask++) {
    // process subset represented by mask
}
```

This enumerates all 2^n subsets in order of their integer representation.

### Iterating All Submasks of a Given Mask

**Problem**: Given a bitmask `mask`, enumerate all subsets of the set represented by `mask`.

**Algorithm**:
```cpp
for (int s = mask; s > 0; s = (s - 1) & mask) {
    // process submask s
}
// don't forget to process s = 0 (the empty submask) if needed
```

**Theorem**: This loop generates all submasks of `mask` in strictly decreasing order,
visiting each exactly once.

**Proof of correctness**:

*Claim 1*: Every value s produced is a submask of mask.
After the AND with mask, only bits present in mask can be set in s. So s is a submask.

*Claim 2*: The sequence is strictly decreasing.
s-1 < s. Since (s-1) & mask <= s-1, we have (s-1) & mask < s. So the next value is
strictly less than the current.

*Claim 3*: Every submask of mask is produced.
Let t be a submask of mask with t < s (current value). We show t is eventually reached.
Consider (s-1) & mask. Since s-1 >= t (as s > t, s-1 >= t), and t is a submask of mask,
we have (s-1) & mask >= t (because every bit of t is in mask and in s-1 or a lower bit
compensates... more precisely, one can show by induction on s - t that t is eventually
reached since the sequence is strictly decreasing and bounded below by 0).

Strict proof by strong induction: the sequence s, (s-1)&mask, ((s-1)&mask - 1)&mask, ...
is strictly decreasing and consists only of submasks of mask. Since there are finitely
many submasks (2^popcount(mask)), and the sequence starts at mask and reaches 0, and
visits only submasks, it must visit all of them by the pigeonhole principle (it takes
exactly 2^popcount(mask) - 1 steps from mask down to reaching 0, which matches the
number of nonempty submasks).

### Total Work for All Submasks of All Masks

**Theorem**: The sum over all masks of the number of submasks equals 3^n:

    sum_{mask=0}^{2^n - 1} 2^{popcount(mask)} = 3^n

**Proof**: Each element e in {0, ..., n-1} is in one of three states:
1. e is in mask AND in submask
2. e is in mask but NOT in submask
3. e is NOT in mask (and therefore not in submask)

These choices are independent across elements, giving 3^n (mask, submask) pairs total.

Alternatively, by the binomial theorem:

    sum_{k=0}^{n} C(n,k) * 2^k = (1+2)^n = 3^n

where C(n,k) counts masks with popcount k, and each such mask has 2^k submasks.

---

## Section 3: Prefix XOR and Range XOR

### Construction

Given an array a[0], a[1], ..., a[n-1], define the prefix XOR array X of length n+1:

    X[0] = 0
    X[i] = X[i-1] ^ a[i-1]    for i = 1, ..., n

Expanding: X[i] = a[0] ^ a[1] ^ ... ^ a[i-1].

### Range XOR Query

**Theorem**: The XOR of the subarray a[l], a[l+1], ..., a[r] equals X[r+1] ^ X[l].

**Proof**:

    X[r+1] ^ X[l]
    = (a[0] ^ a[1] ^ ... ^ a[r]) ^ (a[0] ^ a[1] ^ ... ^ a[l-1])

By associativity and commutativity of XOR, we can pair up the common terms:

    = (a[0] ^ a[0]) ^ (a[1] ^ a[1]) ^ ... ^ (a[l-1] ^ a[l-1]) ^ a[l] ^ ... ^ a[r]
    = 0 ^ 0 ^ ... ^ 0 ^ a[l] ^ ... ^ a[r]
    = a[l] ^ a[l+1] ^ ... ^ a[r]

The key property is that XOR is its own inverse: a ^ a = 0. This is why prefix XOR
works analogously to prefix sums, but with XOR instead of addition.

**Note**: Unlike prefix sums (which support range sum queries), prefix XOR only supports
range XOR queries. There is no "range AND" or "range OR" analogue because AND and OR
are not self-inverse.

---

## Section 4: Bitset Optimization

### The std::bitset<N> Model

`std::bitset<N>` stores N bits packed into ceil(N/64) 64-bit words. All bitwise
operations (AND, OR, XOR, NOT, shift) operate on entire words, giving a constant-factor
speedup of 64x (or 32x on 32-bit machines) over bit-by-bit processing.

**Time complexities**:
- Bitwise AND/OR/XOR/NOT of two bitsets: O(N/64)
- Left/right shift by k positions: O(N/64)
- Count set bits (popcount): O(N/64) using hardware popcount
- Test/set/reset single bit: O(1)

### Subset Sum via Bitset

**Problem**: Given n items with weights w_1, ..., w_n, determine which sums in [0, W]
are achievable.

**Algorithm**:
```cpp
bitset<W+1> reachable;
reachable[0] = 1;  // sum 0 is always achievable
for (int i = 0; i < n; i++) {
    reachable |= (reachable << w[i]);
}
// reachable[s] == 1 iff sum s is achievable
```

**Correctness proof by induction on i**:

*Base*: After processing 0 items, reachable = {0}. Correct: the only achievable sum
using no items is 0.

*Inductive step*: Suppose after processing items 0..i-1, reachable[s] = 1 iff s is
achievable using some subset of {w_0, ..., w_{i-1}}.

After `reachable |= (reachable << w[i])`:
- `reachable << w[i]` has bit s set iff bit (s - w[i]) was set in the old reachable,
  i.e., iff (s - w[i]) is achievable using items 0..i-1. So bit s is set iff s is
  achievable by taking item i plus some subset achieving (s - w[i]).
- OR with the old reachable preserves all previously achievable sums (not taking item i).
- Therefore: new reachable[s] = 1 iff s is achievable using some subset of {w_0,...,w_i}.

**Complexity**: O(n * W / 64). For n = 1000, W = 10^5, this is roughly 10^8 / 64 ~ 1.5 * 10^6
operations, well within time limits.

---

## Section 5: Key Tricks Quick Reference

| Trick                    | Code                  | Why It Works                                      |
|--------------------------|-----------------------|---------------------------------------------------|
| Clear lowest set bit     | `n & (n-1)`           | Binary subtraction flips the trailing 10...0 pattern |
| Isolate lowest set bit   | `n & (-n)`            | Two's complement: -n = ~n + 1. Only the lowest set bit survives the AND |
| Check power of 2         | `n && !(n & (n-1))`   | Powers of 2 have exactly one set bit; clearing it yields 0 |
| Check if kth bit is set  | `(n >> k) & 1`        | Shift bit k to position 0, mask off everything else |
| Set the kth bit          | `n \| (1 << k)`       | OR with a mask having only bit k set              |
| Clear the kth bit        | `n & ~(1 << k)`       | AND with a mask having only bit k cleared         |
| Toggle the kth bit       | `n ^ (1 << k)`        | XOR flips the target bit, leaves others unchanged |
| All bits below position k| `(1 << k) - 1`        | 2^k - 1 = 0...01...1 (k ones)                    |
| Round up to next power of 2 | Various (see below) | Fill all bits below the highest, then add 1      |
| Popcount                 | `__builtin_popcount(n)` | Hardware instruction on modern CPUs (O(1))      |
| Count trailing zeros     | `__builtin_ctz(n)`    | Position of the lowest set bit                    |
| Count leading zeros      | `__builtin_clz(n)`    | 32 - 1 - floor(log2(n)) for 32-bit integers      |
| Highest set bit position | `31 - __builtin_clz(n)` | floor(log2(n)) for n > 0                       |

### Isolate Lowest Set Bit: Detailed Proof

**Theorem**: For n > 0, `n & (-n)` equals 2^k where k is the position of the lowest set bit.

**Proof**: In two's complement representation, -n = ~n + 1.

Let n = [prefix]1[000...0] with k trailing zeros.
Then ~n = [~prefix]0[111...1].
Adding 1: ~n + 1 = [~prefix]1[000...0].

Now n & (-n):
- The trailing zeros: 0 & 0 = 0 in both.
- The lowest set bit position: 1 & 1 = 1.
- The prefix: [prefix] & [~prefix] = 0 (bit-by-bit, x & ~x = 0).

Result: 000...010...0 = 2^k. QED.

### Round Up to Next Power of 2

```cpp
uint32_t next_pow2(uint32_t n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}
```

**Why it works**: After n--, we need to find 2^(floor(log2(n)) + 1). The sequence of
OR-shifts propagates the highest set bit downward, filling all lower bits with 1s.
The result is 2^k - 1 for some k, and adding 1 gives 2^k.

---

## Section 6: XOR Basis (Linear Algebra over GF(2))

A set of integers can be viewed as a set of vectors in GF(2)^w (where w is the bit width).
A **XOR basis** (or linear basis) is a maximal linearly independent subset: the smallest
set of vectors whose XOR-combinations (linear span) equal the XOR-combinations of the
original set.

**Gaussian elimination to build a basis**:
```cpp
int basis[LOG];  // basis[i] has its highest set bit at position i, or 0
memset(basis, 0, sizeof(basis));

void insert(int x) {
    for (int i = LOG - 1; i >= 0; i--) {
        if (!((x >> i) & 1)) continue;
        if (!basis[i]) { basis[i] = x; return; }
        x ^= basis[i];
    }
    // x == 0: linearly dependent, not added
}
```

**Applications**:
- Maximum XOR of a subset: greedily XOR basis elements from highest bit down.
- Count of distinct XOR values achievable: 2^(basis size).
- Check if a target XOR is achievable: try to reduce it to 0 using the basis.
