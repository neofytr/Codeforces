# Bitmask Techniques: Iterating Over All Possibilities

## Introduction to Bitmasks

Bitmasks are a powerful technique in competitive programming that use binary representation to efficiently iterate through all possible subsets or combinations of elements. This approach leverages the natural mapping between binary digits and yes/no decisions.

## The Core Technique: Iterating All Possibilities

### Basic Pattern
```c
for (int mask = 0; mask < (1 << n); mask++) {
    // Process this specific combination
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            // The i-th element is included
        } else {
            // The i-th element is excluded
        }
    }
}
```

### How It Works
- A number with `n` bits can represent 2^n different states
- Each bit position corresponds to one element/decision
- For each element, we can make a binary choice (yes/no, include/exclude, etc.)

## When to Use Bitmasks

### Perfect For:
1. **Subset Generation**: Generate all possible subsets of an array/set
2. **State Representation**: When you need to track which elements are "on" or "off"
3. **Binary Decision Problems**: Any problem where each element has exactly two possible states
4. **Small Input Sizes**: When n ≤ 20-25 (since 2^n quickly becomes too large)

### Common Problem Types:
1. **Subset Sum Problems**: Finding subsets that sum to a target value
2. **Traveling Salesman Problem**: Dynamic programming with bitmasks
3. **Assignment Problems**: Assigning n tasks to n workers
4. **Permutation Generation**: Generating all possible arrangements
5. **Combinatorial Problems**: Counting/enumerating combinations with constraints

## The Combination Lock Example

Your solution to the combination lock problem is a perfect example:

```c
for (int set = 0; set < (1 << n); set++) {
    int sum = 0;
    for (int test = 0; test < n; test++) {
        sum += ((1 << test) & set) ? -rotations[test] : rotations[test];
    }
    if (!(sum % 360)) {
        return true; // Found a valid combination
    }
}
```

Here, you use bitmasks to try all 2^n possible ways to rotate the lock (clockwise or counterclockwise for each instruction).

## Advanced Bitmask Techniques

### 1. Set Operations
- Union: `A | B`
- Intersection: `A & B`
- Complement: `~A`
- Difference: `A & (~B)`

### 2. Bit Manipulation
- Check if bit is set: `(mask & (1 << i)) != 0`
- Set a bit: `mask |= (1 << i)`
- Clear a bit: `mask &= ~(1 << i)`
- Toggle a bit: `mask ^= (1 << i)`
- Get lowest set bit: `mask & (-mask)`

### 3. Counting Set Bits
- Built-in: `__builtin_popcount(mask)` (GCC)
- Kernighan's Algorithm: `count += mask &= (mask-1)`

## Time and Space Complexity

- Time Complexity: O(2^n) for full enumeration
- Space Complexity: O(1) for the mask itself, potentially O(2^n) if storing results

## Limitations
- Grows exponentially - generally practical only up to n ≈ 20-25
- Not suitable for large input sizes
- Can be harder to debug due to binary representation

## Practice Problems

To master this technique, try these types of problems:
1. Subset sum problems
2. Traveling Salesman Problem variants
3. DP with bitmasks
4. Set covering problems
5. Graph coloring with few colors

## Conclusion

Bitmask enumeration is a powerful technique when you need to consider all possible combinations of a relatively small set of elements. It's elegant, memory-efficient, and often leads to cleaner code than recursive approaches for the same tasks.