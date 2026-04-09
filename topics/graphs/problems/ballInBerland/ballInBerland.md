# ballInBerland

```markdown
## Competitive Programming Solution Documentation

### 1. Problem Description (Inferred)

The code solves a combinatorial problem involving pairs of boys and girls. Given `a` boys, `b` girls, and `k` pairs of (boy, girl), the task is to find the number of pairs of these `k` pairs where the boys are different and the girls are different.  In other words, we need to count the number of (i, j) such that 0 <= i < j < k, and boy[i] != boy[j] and girl[i] != girl[j].

### 2. Approach Explanation

The solution uses a counting principle combined with inclusion-exclusion.

1.  **Total Possible Pairs:**  First, it calculates the total number of possible pairs of pairs from the given `k` pairs. This is simply `k * (k - 1) / 2`, which represents all possible combinations of choosing 2 pairs from `k`.

2.  **Overcounting Correction (Inclusion-Exclusion):** The initial calculation overcounts the number of valid pairs because it includes pairs of pairs that share the same boy or the same girl.  The code corrects this by subtracting the number of invalid pairs.

    *   **Pairs with the Same Boy:** For each boy, it counts how many pairs that boy is involved in (`boys[i]`).  Then, it calculates the number of ways to choose two pairs that both involve the same boy: `boys[i] * (boys[i] - 1) / 2`.  It sums this value for all boys and subtracts it from the total.

    *   **Pairs with the Same Girl:** Similarly, for each girl, it counts how many pairs that girl is involved in (`girls[i]`).  Then, it calculates the number of ways to choose two pairs that both involve the same girl: `girls[i] * (girls[i] - 1) / 2`.  It sums this value for all girls and subtracts it from the total.

The key insight is that the sets of invalid pairs (same boy) and (same girl) are mutually exclusive.  This is because you can't have two *different* pairs that have *both* the same boy and the same girl. If they did, they'd be the *same* pair. Therefore, we can directly subtract the number of pairs with same boy and number of pairs with same girl, without needing more complex inclusion-exclusion.

### 3. Key Insights and Algorithmic Techniques Used

*   **Combinatorial Counting:** The core idea is to count all possible combinations and then subtract the invalid ones.
*   **Inclusion-Exclusion (Simplified):** While not the full generality of inclusion-exclusion, the problem exploits a special case where sets of invalid pairs are disjoint, making the subtraction simpler.
*   **Frequency Counting:**  The `boys` and `girls` vectors efficiently store the number of times each boy and girl appears in the given pairs. This allows for O(1) access to this information during the correction step.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(t * (a + b + k)), where `t` is the number of test cases, `a` is the number of boys, `b` is the number of girls, and `k` is the number of pairs. This is because the code iterates through the boys, girls, and pairs once. More specifically, the inner loop of the solve function takes O(a+b+k) time. Inputting the vector `p1` and `p2` takes O(k) time. Counting frequency takes O(k) time, and the loops calculating the totals take O(a) and O(b) respectively.
*   **Space Complexity:** O(a + b + k). The code uses vectors `boys` of size `a`, `girls` of size `b`, and `p1` and `p2` of size `k`.

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This redefines the `int` type to `long long`, which is a common practice in competitive programming to avoid integer overflow issues.
*   **`ios_base::sync_with_stdio(false); cin.tie(nullptr);`:** This is a standard optimization in C++ to speed up input/output by disabling synchronization between C and C++ streams.
*   **0-based indexing:** The problem's indices are 1-based but the vectors use 0-based indexing, so the code converts inputs `p1[index]` and `p2[index]` into zero based indexing with `p1[index]--` and `p2[index]--`.
*   **Concise Formula:** The formula `x * (x - 1) / 2` is used to efficiently calculate the number of ways to choose 2 elements from a set of size `x`.

### 6. Any Edge Cases Handled

*   The solution correctly handles the case when `k` is small, as the `k * (k - 1) / 2` calculation will result in 0 when k is 0 or 1, which is the correct behavior when no pairs of pairs can be formed.

```


## Original Code
```cpp
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

void solve() {
    int a, b, k;
    cin >> a >> b >> k;

    // since we have k pairs
    // we select two out of them
    // but in doing so, we have overcounted exactly the following
    // 1. pairs where the boys are the same
    // 2. pairs where the girls are the same
    // these two are mutually exclusive sets since both boys and both girls cannot be the same
    // in two different pairs

    // pairs where the boys are the same
    // for each boy b
    // the number of pairs of pairs formed where both have the boy b is deg(b) * (deg(b) - 1) / 2
    // since all of these are mutually exclusive, we can sum over them

    // pairs where the girls are the same
    // for each girl g
    // the number of pairs of pairs formed where both have the boy b is deg(b) * (deg(b) - 1) / 2
    // since all of these are mutually exclusive, we can sum over them

    vector<int> boys(a);  // boys[r] is the number of pairs boy r is involved in
    vector<int> girls(b); // girls[r] is the number of pairs girl r is involved in

    vector<int> p1(k);
    vector<int> p2(k);
    for (int index = 0; index < k; index++) {
        cin >> p1[index];
        p1[index]--;
    }
    for (int index = 0; index < k; index++) {
        cin >> p2[index];
        p2[index]--;
    }

    for (int index = 0; index < k; index++) {
        boys[p1[index]]++;
        girls[p2[index]]++;
    }

    // total number of possible pairs of the k pairs
    int total = k * (k - 1) / 2;

    // subtract from it the number of pairs where the boys are the same
    for (int by = 0; by < a; by++) {
        total -= (boys[by] * (boys[by] - 1)) / 2;
    }

    // subtract from it the number of pairs where the girls are the same
    for (int g = 0; g < b; g++) {
        total -= (girls[g] * (girls[g] - 1)) / 2;
    }

    cout << total << endl;
    return;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}

```

---
*Documentation generated on 2025-07-28 20:58:14*
