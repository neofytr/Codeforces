# Efficient Subset Sum Checking Using Bitsets

## Overview
The subset sum problem asks whether a subset of given weights `{w1, w2, ..., wN}` exists such that the total sum is exactly `W`. Given constraints where `N ≤ 1000` and `W ≤ 10^6`, a brute-force approach is computationally infeasible. Instead, we use **bitset shifting** to efficiently track reachable sums.

## Key Idea: Using Bitsets for Fast DP
Instead of explicitly tracking subsets, we maintain a **bitset** where each bit at position `i` represents whether the sum `i` can be achieved using some subset of weights.

### **Initialization**
We start with:
- `reachable_sums[0] = 1` because an empty subset always sums to `0`.
- `reachable_sums[i] = 0` for all other `i` initially.

### **Dynamic Update Using Bitwise Shifting**
For each weight `w`, we update the bitset as follows:
```cpp
reachable_sums |= reachable_sums << w;
```
This operation works as follows:
1. **Shifting left by `w`** moves all bits `reachable_sums[i]` to `reachable_sums[i + w]`, meaning all sums `i + w` that could be formed previously are now reachable.
2. **Bitwise OR (`|=`) ensures previously reachable sums are retained**.

## Example Execution
### **Input:**
```cpp
N = 3, W = 7
weights = {3, 5, 2}
```

### **Bitset Evolution:**
#### **Step 1: Start**
```
reachable_sums = {1, 0, 0, 0, 0, 0, 0, 0, 0}
```
#### **Step 2: Add weight `3` (shift left by `3`)**
```
reachable_sums = {1, 0, 0, 1, 0, 0, 0, 0, 0}
```
#### **Step 3: Add weight `5` (shift left by `5`)**
```
reachable_sums = {1, 0, 0, 1, 0, 0, 1, 0, 1}
```
#### **Step 4: Add weight `2` (shift left by `2`)**
```
reachable_sums = {1, 0, 1, 1, 1, 0, 1, 1, 1}
```
Since `reachable_sums[7] = 1`, we conclude that **a subset exists with sum `7`**.

## **Time Complexity**
- **Bitwise shifting and OR operations take `O(1)` per bit**.
- **Overall complexity:** `O(NW / 64)`, significantly faster than `O(2^N)` brute force.

## **When to Use This Technique?**
Use this approach when:
- `N` is large (up to `1000`), making `O(2^N)` infeasible.
- `W` is moderate (`≤ 10^6`), so a `bitset<W>` fits in memory.
- **Exact subset sum checking** is needed rather than approximate solutions.

This method provides a highly efficient way to solve subset sum problems using bit manipulation and shifting, making it ideal for competitive programming and constrained environments.

