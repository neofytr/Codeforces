# XOR Techniques and Bit-Level Observations

---

## 7. XOR Deep Results

### 7.1 Prefix XOR array

For array a[1..n], define p[0] = 0, p[i] = p[i-1] ^ a[i].

- **Range XOR:** XOR(l, r) = p[r] ^ p[l-1].
- **Recover element:** a[r] = p[r] ^ p[r-1].

### 7.2 Partitioning into equal-XOR subarrays

**Goal.** Partition a[1..n] into >= 2 consecutive subarrays with equal XOR.

**Case 1: Total XOR = 0** (p[n] = 0).
Always possible. If total XOR is 0, we can split at any position where the
prefix XOR equals half -- but since x ^ x = 0, we just need any prefix where
p[i] = p[n] ^ p[i] (which is just p[i] = p[i], trivially). More precisely:
find any i where p[i] equals some target, and split into [1..i] and [i+1..n].

**Case 2: Total XOR > 0.**
Only **odd-length** partitions can exist (XOR of an even number of identical
values is 0, contradicting non-zero total). Each part must XOR to p[n].
Greedily scan for positions where prefix XOR equals p[n]:

```cpp
int cnt = 0, cur_xor = 0;
for (int i = 1; i <= n; i++) {
    cur_xor ^= a[i];
    if (cur_xor == total_xor) {
        cnt++;
        cur_xor = 0;
    }
}
// cnt >= 3 means a valid 3-partition (or more) exists
```

### 7.3 XOR pair sum (bit contribution trick)

**Problem.** Compute S = sum of (a[i] XOR a[j]) for all i < j.

**Key insight.** XOR operates independently per bit. For each bit position b:
- Let ones_b = count of elements with bit b set.
- Let zeros_b = n - ones_b.
- Pairs that differ at bit b: ones_b * zeros_b.
- Each such pair contributes 2^b.

**Formula:**

    S = sum over all bits b of: ones_b * zeros_b * 2^b

**Range update trick:** If you XOR the entire array with value x, every bit b
that is set in x flips: cnt[b] becomes (n - cnt[b]). This allows O(bits)
updates.

### 7.4 XOR of consecutive numbers

**Three consecutive:**
- n even: n ^ (n+1) ^ (n+2) = n+3.
  (Because n ^ (n+1) = 1 when n even, and 1 ^ (n+2) = n+3 since n+2 is even.)
- n odd: n ^ (n+1) ^ (n+2) = n-1.
  (Because (n+1) ^ (n+2) = 1 when n+1 even, and n ^ 1 = n-1 since n is odd.)

**Four consecutive (n even):** n ^ (n+1) ^ (n+2) ^ (n+3) = 0.
(From the three-consecutive result: (n+3) ^ (n+3) = 0.)

### 7.5 XOR of first n natural numbers

Let f(n) = 1 ^ 2 ^ ... ^ n. Pattern repeats with period 4:

| n mod 4 | f(n) |
|---------|------|
| 0       | n    |
| 1       | 1    |
| 2       | n+1  |
| 3       | 0    |

**Proofs:**
- **n % 4 = 0:** Split into pairs (0^1), (2^3), ..., ((n-2)^(n-1)), then ^n.
  Each pair = 1. There are n/2 pairs (even count), so their XOR = 0. Result: n.
- **n % 4 = 1:** f(n) = f(n-1) ^ n = (n-1) ^ n = 1 (consecutive, n-1 even).
- **n % 4 = 2:** f(n) = f(n-2) ^ (n-1) ^ n = (n-2) ^ (n-1) ^ n = (n-2)^1^... 
  Working through: = 1 ^ n = n+1 (n is even).
- **n % 4 = 3:** f(n) = f(n-3) ^ (n-2) ^ (n-1) ^ n. Four consecutive from 
  n-3 (even), so their XOR = 0.

### 7.6 XOR of first n even / odd numbers

**Even numbers:** g(n) = 2 ^ 4 ^ ... ^ 2n = (1^2^...^n) << 1 = f(n) << 1.
(Factor out the left shift.)

**Odd numbers:** h(n) = 1 ^ 3 ^ ... ^ (2n-1).
Since f(2n) = g(n) ^ h(n), we get:

    h(n) = f(2n) ^ (f(n) << 1)

---

## 20. Consecutive Bits from LSB

Define f(n) = number of consecutive 1-bits from the LSB of n.
E.g., f(7) = 3, f(6) = 0, f(5) = 1.

**Formally:** f(n) = largest a >= 0 such that n mod 2^a = 2^a - 1.

### 20.1 Bits differing in n and n+1

**Claim.** The number of bits that differ between n and n+1 is f(n) + 1.

**Why.** Adding 1 to n flips the lowest 0-bit and all trailing 1-bits below it.
There are f(n) trailing ones plus the one flipped zero = f(n) + 1 bits changed.

### 20.2 Counting integers x in [0, n] with f(x) = a

The integers x with x mod 2^a = 2^a - 1 form the AP: 2^a - 1, 2*2^a - 1, ...

Let g1 = floor((n - 2^a + 1) / 2^a) + 1 = count with at least a trailing ones.

The integers with x mod 2^(a+1) = 2^(a+1) - 1 form a sub-AP (at least a+1
trailing ones). By similar counting, the common terms equal floor(g1 / 2).

**Result:** Count of x in [0, n] with f(x) = exactly a is g1 - floor(g1 / 2).
