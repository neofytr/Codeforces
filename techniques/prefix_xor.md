# Prefix XOR: Concept, Uses, and Applications

## 1. What is Prefix XOR?
Prefix XOR is a technique similar to prefix sum, but instead of summing up elements, we compute the XOR (exclusive OR) of elements in a given range. It allows efficient computation of subarray XOR in **constant time O(1)** after an initial **O(n) preprocessing step**.

### Definition
For an array `arr` of size `n`, the **prefix XOR array** `prefix_xor` is defined as:

```
prefix_xor[i] = arr[0] ⊕ arr[1] ⊕ ... ⊕ arr[i]
```
where `⊕` denotes the **bitwise XOR operation**.

It stores the **cumulative XOR** of the array from the beginning up to index `i`.

## 2. Computing Prefix XOR
We can compute the prefix XOR efficiently in a single pass:

```cpp
int prefix_xor[n+1]; // +1 for 1-based indexing
prefix_xor[0] = 0;   // XOR of empty set is 0

for (int i = 1; i <= n; i++) {
    prefix_xor[i] = prefix_xor[i - 1] ^ arr[i - 1];
}
```

The value at `prefix_xor[i]` gives the XOR of all elements from `arr[0]` to `arr[i-1]`.

## 3. Querying XOR of a Subarray `[L, R]`
Once we have the **prefix XOR**, we can efficiently compute the XOR of any subarray `[L, R]` using:

```
XOR(L, R) = prefix_xor[R] ⊕ prefix_xor[L-1]
```

### Why Does This Work?
Using the property that `x ⊕ x = 0`:

```
prefix_xor[R] = arr[0] ⊕ arr[1] ⊕ ... ⊕ arr[R]
prefix_xor[L-1] = arr[0] ⊕ arr[1] ⊕ ... ⊕ arr[L-1]
```

If we XOR these two:

```
(prefix_xor[R]) ⊕ (prefix_xor[L-1])
= (arr[0] ⊕ ... ⊕ arr[R]) ⊕ (arr[0] ⊕ ... ⊕ arr[L-1])
```

Everything cancels out except `arr[L] ⊕ arr[L+1] ⊕ ... ⊕ arr[R]`, which is exactly what we want.

## 4. Example
### **Input**
```
arr = [3, 5, 2, 6, 4]
```
### **Compute Prefix XOR**
| Index | `arr[i]` | `prefix_xor[i]` (cumulative XOR) |
|--------|--------|-------------|
| 0 | - | 0 |
| 1 | 3 | 3 |
| 2 | 5 | 3 ⊕ 5 = 6 |
| 3 | 2 | 6 ⊕ 2 = 4 |
| 4 | 6 | 4 ⊕ 6 = 2 |
| 5 | 4 | 2 ⊕ 4 = 6 |

### **Query XOR(2, 4)**
```
prefix_xor[4] ^ prefix_xor[1] = 2 ^ 3 = 1
```
This means the XOR of `[5, 2, 6]` is `1`.

## 5. Use Cases of Prefix XOR
1. **Efficient Range XOR Queries**  
   - Instead of iterating over the range `[L, R]`, we compute it in `O(1)` time.
2. **Finding Odd Occurrences in a Range**  
   - Numbers that appear an **odd** number of times in a subarray will have a **set bit in the XOR result**.
3. **Checking if a Subarray Has an XOR Sum of Zero**  
   - If `prefix_xor[R] == prefix_xor[L-1]`, then the XOR sum of `[L, R]` is `0`.
4. **Cryptographic Applications**  
   - Used in one-time pad encryption and hashing algorithms.
5. **Finding Unique Elements**  
   - If every number appears twice except one, then XORing all elements gives the unique number.

## 6. Complexity Analysis
| Operation | Complexity |
|-----------|------------|
| **Building prefix_xor** | `O(n)` |
| **Querying XOR(L, R)** | `O(1)` |

This makes it **much faster** than a naive `O(n)` approach of computing XOR directly for each query.

## 7. Summary
- **Prefix XOR** allows fast **range XOR queries** using `O(1)` operations after `O(n)` preprocessing.
- It works using the **property**:  
  ```
  XOR(L, R) = prefix_xor[R] ⊕ prefix_xor[L-1]
  ```
- **Common use cases:** Range queries, finding odd occurrences, cryptography, and number-theoretic problems.

---

