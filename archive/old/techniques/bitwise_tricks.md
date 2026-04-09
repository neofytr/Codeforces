# Bitwise Operations Reference Guide

## Basic Bitwise Operators

| Operator | Name | Description |
|----------|------|-------------|
| `&` | AND | Sets bits to 1 if both operands have 1 in that position |
| `\|` | OR | Sets bits to 1 if either operand has 1 in that position |
| `^` | XOR | Sets bits to 1 if only one operand has 1 in that position |
| `~` | NOT | Inverts all bits (0→1, 1→0) |
| `<<` | Left Shift | Shifts bits left by specified number of positions |
| `>>` | Right Shift | Shifts bits right by specified number of positions |

## Power of Two Checks

```c
// Check if n is a power of 2
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Alternatively, verify n is NOT a power of 2
// (n) && (n & (n - 1)) is 1 iff n is NOT a power of 2
```

# Built-in O(1) functions

__builtin_popcount(x) returns popcount of a number — the number of ones in the binary representation of x. Use __builtin_popcountll(x) for long longs.

There are also __builtin_clz and __builtin_ctz (and their long long versions) for counting the number of leading or trailing zeros in a positive number.

## Extra

Suppose x is an unsigned number
Doing x - 1 sets all the bits to the right of it's leftmost set bit and clears the leftmost set bit
So doing x & (x - 1) clears the leftmost set bit

## Even/Odd Checks

```c
// Check if number is even
bool isEven(int num) {
    return (num & 1) == 0;
}

// Check if number is odd
bool isOdd(int num) {
    return (num & 1) == 1;
}
```

## Bit Manipulation

```c
// Check if kth bit is set
bool isKthBitSet(int n, int k) {
    return (n & (1 << k)) != 0;
}

// Set kth bit
int setKthBit(int n, int k) {
    return n | (1 << k);
}

// Clear kth bit
int clearKthBit(int n, int k) {
    return n & ~(1 << k);
}

// Toggle/invert kth bit
int toggleKthBit(int n, int k) {
    return n ^ (1 << k);
}
```

## Getting Remainder with 2^k

```c

// Get the remainder of a non-negative integer when divided by 2 ^ k
uint32_t getRem(uint32_t x)
{
    return (x & ((1UL << k) - 1));
}

```

## Toggling with XOR

Suppose than x can only be one of 5 or 10
Then, the code,

```c

if (x == 5)
{
    x = 10;
}
else if (x == 10)
{
    x = 5
}

```

is equivalent to

```c

x = x ^ a ^ b

```

## Finding Number of Set Bits

```c

// Brian-Kernighan Algorithm
uint32_t findSetBits(uint32_t x)
{
    uint32_t count = 0;
    while(x)
    {
        count++;
        x &= (x - 1);
    }

    return count;
}

```

## Common Bit Properties

- XOR properties:
  - `x ^ 0 = x` (XOR with 0 returns the original number)
  - `x ^ x = 0` (XOR of a number with itself is 0)
  - `x ^ y ^ x = y` (XOR is commutative and applying twice cancels out)
  - `x ^ a` is `0` iff `a = x`; it's `1` otherwise

- AND properties:
  - `x & 0 = 0` (AND with 0 always returns 0)
  - `x & 1 = x` for single-bit values (AND with 1 preserves the original bit)
  - `x & x = x` (AND of a number with itself is itself)

- OR properties:
  - `x | 0 = x` (OR with 0 returns the original number)
  - `x | 1 = 1` for single-bit values (OR with 1 always returns 1)
  - `x | x = x` (OR of a number with itself is itself)

## Advanced Bitwise Tricks

```c
// Count set bits (Hamming weight/population count)
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // Clears the least significant set bit
        count++;
    }
    return count;
}

// Get the rightmost set bit
int getRightmostSetBit(int n) {
    return n & -n;  // or: n & (~n + 1)
}

// Clear all bits from LSB to position k (inclusive)
int clearBitsFromLSBToK(int n, int k) {
    return n & (~0 << (k + 1));
}

// Clear all bits from position k to MSB (inclusive)
int clearBitsFromKToMSB(int n, int k) {
    return n & ((1 << k) - 1);
}
```

## Bit Twiddling Hacks

```c
// Swap two variables without temporary variable
void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

// Compute absolute value without branching
int abs(int n) {
    int mask = n >> (sizeof(int) * 8 - 1);
    return (n + mask) ^ mask;
}

// Check if two integers have opposite signs
bool oppositeSign(int a, int b) {
    return (a ^ b) < 0;
}

// Round up to the next power of 2
unsigned int nextPowerOf2(unsigned int n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}
```

## Bit Masks and Flags

```c
// Create a bit mask with bits from position i to j set to 1
int createMask(int i, int j) {
    return ((~0) << i) & (~(~0 << (j + 1)));
}

// Extract a range of bits (from position i to j)
int extractBits(int n, int i, int j) {
    int mask = createMask(i, j);
    return (n & mask) >> i;
}

// Update a range of bits from i to j with value v
int updateBits(int n, int i, int j, int v) {
    int mask = createMask(i, j);
    return (n & ~mask) | ((v << i) & mask);
}
```

## Common Bitwise Applications

- Bit-fields and flags for compact data storage
- Efficient math operations
  - Multiply by 2^n: `x << n`
  - Divide by 2^n: `x >> n` (integer division)
  - Modulo 2^n: `x & ((1 << n) - 1)`
- Set operations using bitmasks
- Binary search using bit manipulation
- Memory-efficient data structures

## Common Bit Patterns

```
0xAAAAAAAA = 10101010101010101010101010101010 (alternating 1,0)
0x55555555 = 01010101010101010101010101010101 (alternating 0,1)
0xFFFFFFFF = 11111111111111111111111111111111 (all 1's)
0x00000000 = 00000000000000000000000000000000 (all 0's)
```