# Greedy Observations and Proof Techniques

---

## 9. Greedy Insights

### 9.1 Pairwise comparator sorting

**Observation.** Even when all items must be taken but order matters, you can
derive the optimal order by pairwise comparison.

**Method:**
1. Compare two items A, B: which order (A then B) vs (B then A) gives a better
   result?
2. Express this as a comparator: A < B iff "A before B" is at least as good.
3. Sort all items by this comparator.

**Why globally optimal.** If the pairwise comparator is transitive, any
out-of-order adjacent pair can be swapped to improve (or maintain) the result.
Bubble sort argument: the sorted order has no improvable adjacent pair, so it is
optimal.

### 9.2 Greedy proof technique for feasibility

For YES/NO problems with repeated operations:

1. **Reinterpret** operations as resource transfers (units, tokens, supply/demand).
2. **Identify invariants** (parity, sum mod k, monotonic quantities).
3. **Derive necessary conditions** from invariants and extreme cases (e.g.,
   largest element vs rest).
4. **Define a greedy move** that is always legal when conditions hold and
   simplifies the state.
5. **Prove invariant preservation:** conditions hold before move implies they
   hold after.
6. **Eliminate dead-ends:** any dead-end would violate a necessary condition,
   so dead-ends are unreachable.
7. **Conclude:** valid move always exists + progress is made + process terminates
   implies target is reachable.
