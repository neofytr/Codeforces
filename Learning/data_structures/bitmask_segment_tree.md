# Segment Tree with Bitmasks (Small Value Range)

---

## 16. Segment Tree with Bitmasks (Small Value Range)

**Constraint.** All values lie in [0, 63] (or any range fitting in 64 bits).

**Idea.** Each segment tree node stores a 64-bit bitmask. Bit i is set iff
value i appears in that node's segment.

- **Leaf:** mask = (1ULL << a[i]).
- **Combine:** parent mask = left_child | right_child.
- **Query [l, r]:** OR all masks covering the range.
- **Distinct count:** `__builtin_popcountll(combined_mask)`.

**Complexity:** O(log n) per query and update, with tiny constants.
