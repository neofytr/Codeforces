# Nice Article

https://codeforces.com/blog/entry/86420

# Prefix Sum Technique

## Basic Concept

The prefix sum technique creates a new array where each element is the sum of all previous elements in the original array (inclusive). This allows for efficient range sum queries in O(1) time after O(n) preprocessing.

## Core Operations

### Building a Prefix Sum Array

```cpp
// For a 0-indexed array arr of size n
vector<int> prefix(n);
prefix[0] = arr[0];
for(int i = 1; i < n; i++) {
    prefix[i] = prefix[i-1] + arr[i];
}
```

### Querying Range Sum (from index l to r inclusive)

```cpp
// With the prefix array built
int rangeSum(int l, int r) {
    if (l == 0) return prefix[r];
    return prefix[r] - prefix[l-1];
}
```

## Advanced Techniques

### 1. Range Update with Point Query

For operations where you update ranges and then query individual points.

**Problem Pattern**:
- Multiple updates of form: "Add value `val` to all elements in range [l,r]"
- Query the final value at specific positions

**Solution**:
1. Initialize a difference array `diff` of all zeros
2. For each range update [l,r] with value v:
   - Add `v` to `diff[l]`
   - Subtract `v` from `diff[r+1]` (if r+1 is within bounds)
3. The final array is the prefix sum of the difference array

```cpp
// Initialize difference array
vector<int> diff(n, 0);

// Process range updates
for(auto update : updates) {
    int l = update.l;
    int r = update.r;
    int val = update.val;
    
    diff[l] += val;
    if(r + 1 < n) diff[r + 1] -= val;
}

// Build final array using prefix sum
vector<int> result(n);
result[0] = diff[0];
for(int i = 1; i < n; i++) {
    result[i] = result[i-1] + diff[i];
}
```

### 2. Range Update with Range Query

For problems requiring both range updates and range queries.

**Solution**: Use two levels of difference arrays and prefix sums.

### 3. 2D Prefix Sums

For querying sums over rectangular regions in a 2D grid.

```cpp
// Build 2D prefix sum
vector<vector<int>> prefix2D(n+1, vector<int>(m+1, 0));
for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
        prefix2D[i][j] = grid[i-1][j-1] + prefix2D[i-1][j] + prefix2D[i][j-1] - prefix2D[i-1][j-1];
    }
}

// Query sum in rectangle (r1,c1) to (r2,c2)
int getSum(int r1, int c1, int r2, int c2) {
    // Convert to 1-indexed for prefix array
    r1++; c1++; r2++; c2++;
    return prefix2D[r2][c2] - prefix2D[r1-1][c2] - prefix2D[r2][c1-1] + prefix2D[r1-1][c1-1];
}
```

## Application: Operation Counting

A powerful application of prefix sums is efficiently tracking the frequency of operations:

1. For each operation range [l,r]:
   - Increment a counter at position l
   - Decrement the counter at position r+1
2. Build a prefix sum of these counters to get the number of operations affecting each position
3. Apply the operations weighted by their frequency

### Example Code

```cpp
// Count operations using prefix technique
vector<long long> op_counts(m+1, 0);

for (size_t query = 0; query < k; query++) {
    size_t x, y;
    cin >> x >> y;
    x--, y--;
    
    // Mark the range [x,y]
    op_counts[x]++;
    op_counts[y+1]--; 
}

// Get actual count of each operation
for (size_t i = 1; i < m; i++) {
    op_counts[i] += op_counts[i-1];
}

// Apply operations using another prefix array
vector<long long> prefix(n, 0);

for (size_t i = 0; i < m; i++) {
    if (op_counts[i] == 0) continue;
    
    auto [l, r, d] = operations[i];
    prefix[l] += d * op_counts[i];
    if (r + 1 < n) {
        prefix[r + 1] -= d * op_counts[i];
    }
}

// Propagate final prefix sum
for (size_t i = 1; i < n; i++) {
    prefix[i] += prefix[i - 1];
}
```

## Time Complexity

- Building a prefix sum array: O(n)
- Range sum queries: O(1) per query
- Range updates with point queries: O(n + u) where u is the number of updates
- Range updates with range queries: O(n + u + q) where q is the number of queries

## Common Problems

1. Range sum queries
2. Range update operations
3. Finding subarrays with a given sum
4. Computing running statistics (min, max, average)
5. Counting operations across ranges

## Tips

- Always check for off-by-one errors when working with ranges
- Be careful with 0-indexed vs 1-indexed arrays
- Consider using `long long` for prefix sums to avoid overflow
- In competitive programming, use prefix sums whenever you see range queries or updates