# Number Theory Observations

---

## 2. Number Theory Observations

### 2.1 Power of 2 via `__builtin_ctzll`

For any integer `x > 1`:

```
__builtin_ctzll(x) == v2(x)
```

where `v2(x)` is the 2-adic valuation (the exponent of 2 in the prime
factorization of x). This counts trailing zeros in binary, which is exactly the
number of times 2 divides x.

### 2.2 LCM of three consecutive integers (odd case)

**Claim.** If n is odd and n >= 3, then

    LCM(n, n-1, n-2) = n * (n-1) * (n-2).

**Proof sketch.** We need gcd of every pair to be 1.
- gcd(n, n-1) = 1 (consecutive).
- gcd(n-1, n-2) = 1 (consecutive).
- gcd(n, n-2) = gcd(n, n-2). Since n is odd and n-2 is also odd, and
  n - (n-2) = 2, we get gcd(n, n-2) | 2. But both are odd, so gcd = 1.

When all pairwise gcds are 1, LCM = product.

### 2.3 Consecutive integers are coprime

For n >= 2: **gcd(n, n-1) = 1.**

Proof: any common divisor d divides n - (n-1) = 1.

### 2.4 At most one multiple of r in r consecutive integers

**Claim.** In the sequence x, x+1, ..., x+(r-1) (r terms), at most one number
is divisible by any integer m >= r.

**Proof.** If two distinct elements a, b in the sequence are divisible by m,
then |a - b| >= m >= r. But the entire range has width r-1, contradiction.

**Use case.** When you need to argue that large prime factors are "rare" in a
short window.

### 2.5 Chicken McNugget Theorem

For coprime positive integers a, b:

    The largest integer NOT representable as ax + by (x, y >= 0) is ab - a - b.

Every integer > ab - a - b IS representable.

**Quick proof idea.** Consider residues mod a. For each residue class r, the
smallest representable number in that class is r*b (take x=0, y=r). The
largest gap occurs at the boundary.

### 2.6 Repunit decomposition (f(x) = 111...1, x ones)

**Claim.** For any x >= 2, f(x) = 11*a + 111*b for some non-negative integers
a, b.

**Proof by cases mod 3:**

- **x = 3r** (r >= 1): f(x) is a sum of r copies of 111 at appropriate
  positions. So a = 0, b = sum of powers of 10.

- **x = 3r+1** (r >= 1, so x >= 4): Split as (x-4) threes + one group of 4.
  f(4) = 1111 = 11*100 + 11*1 = 11*101. The remaining 3-groups use 111.

- **x = 3r+2** (r >= 0, so x >= 2): f(2) = 11. The remaining (x-2) digits
  form groups of 3 using 111.

In every case, we decompose into multiples of 11 and 111.
