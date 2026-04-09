# Greedy Algorithms: A Rigorous Treatment

## Section 1: When Does Greedy Work? -- The Exchange Argument

### Definition

A **greedy algorithm** builds a solution incrementally by making, at each step, the
locally optimal choice -- the choice that looks best right now, without considering
future consequences.

The central question: when does local optimality imply global optimality?

### The Two Required Properties

**Theorem (Greedy Correctness Conditions)**: A greedy algorithm produces an optimal
solution if and only if the problem exhibits:

1. **Greedy choice property**: There exists an optimal solution that includes the
   greedy choice. Equivalently: making the locally optimal choice does not eliminate
   all globally optimal solutions from consideration.

2. **Optimal substructure**: After making the greedy choice, the remaining problem
   is a smaller instance of the same problem, and the optimal solution to the
   remaining problem combined with the greedy choice gives an optimal solution to
   the original problem.

### The Exchange Argument (Proof Technique)

The **exchange argument** is the standard technique for proving greedy correctness.

**Structure**:
1. Let G = (g_1, g_2, ..., g_n) be the greedy solution.
2. Let O = (o_1, o_2, ..., o_n) be an arbitrary optimal solution.
3. Find the first position i where G and O differ: g_i != o_i.
4. Show that modifying O by "exchanging" o_i with g_i (or rearranging O to agree
   with G at position i) produces a solution O' that is:
   - Still feasible (satisfies all constraints)
   - No worse than O (objective value is >= that of O, for maximization)
   - Agrees with G on one more position than O does
5. By induction (repeating the exchange), O can be transformed into G without
   worsening the objective. Therefore G is optimal.

**Formal template**:

*Proof*: Let O be an optimal solution. We transform O into G by a sequence of exchanges.

*Exchange step*: Let i be the first index where O and G differ. [Argue that swapping
o_i for g_i in O produces a feasible solution with objective >= O's objective.]

*Induction*: After at most n exchanges, O has been transformed into G. Since each
exchange preserved optimality, G is optimal. QED.

### Why the Exchange Argument Works

The exchange argument exploits a key insight: if the greedy choice is at least as good
as any other choice in the context of an optimal solution, then there must exist an
optimal solution containing the greedy choice. This is precisely the greedy choice property.

The art lies in defining the right "exchange" and proving it preserves feasibility
and optimality.

---

## Section 2: Greedy Paradigms

### Paradigm 1: Sorting + Greedy

**Pattern**: Sort the input by some criterion, then process elements in sorted order,
making greedy decisions.

**Why sorting works**: Sorting imposes a total order on the elements. If the exchange
argument shows that any inversion (pair processed in the wrong order) can be corrected
without worsening the objective, then the sorted order is optimal.

**General inversion argument**: Given a processing order, if swapping any adjacent
out-of-order pair (a, b) where a should come before b (by the sorting criterion)
improves or preserves the objective, then the sorted order is optimal. This is because
any permutation can be transformed into the sorted order by a sequence of adjacent
transpositions (bubble sort), each of which preserves or improves optimality.

### Example 1: Interval Scheduling (Maximum Non-overlapping Intervals)

**Problem**: Given n intervals [s_i, e_i], select the maximum number of non-overlapping
intervals.

**Greedy**: Sort by end time. Greedily select the interval with the earliest end time
that doesn't overlap with the last selected interval.

```cpp
sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
    return a.end < b.end;
});
int count = 0, last_end = -INF;
for (auto& [s, e] : intervals) {
    if (s >= last_end) {
        count++;
        last_end = e;
    }
}
```

**Theorem**: This greedy algorithm produces a maximum-size set of non-overlapping intervals.

**Proof by exchange argument**:

Let G = (g_1, g_2, ..., g_k) be the greedy solution (in order of selection).
Let O = (o_1, o_2, ..., o_m) be an optimal solution with m >= k (sorted by end time).

*Claim*: g_i.end <= o_i.end for all i = 1, ..., k.

*Proof of claim by induction on i*:

Base (i=1): g_1 has the earliest end time among all intervals, so g_1.end <= o_1.end.

Inductive step: Assume g_{i-1}.end <= o_{i-1}.end. The greedy algorithm selects g_i
as the interval with the earliest end time that starts at or after g_{i-1}.end.
Since o_i starts at or after o_{i-1}.end >= g_{i-1}.end (by IH and the fact that
O is non-overlapping), o_i is a candidate for greedy selection. Therefore
g_i.end <= o_i.end (greedy picks the earliest-ending valid option).

*Claim*: k >= m.

*Proof*: Suppose k < m. Then o_{k+1} exists. By the claim, g_k.end <= o_k.end.
Since o_{k+1}.start >= o_k.end >= g_k.end... wait, we need o_{k+1}.start >= o_k.end,
which holds because O is non-overlapping. So o_{k+1} starts at or after g_k.end,
meaning o_{k+1} is a valid candidate for the greedy algorithm after selecting g_k.
But the greedy algorithm would have selected some interval (it only stops when no
valid interval remains), contradicting k being the greedy count. Therefore k >= m.

Since m >= k (O is optimal) and k >= m, we have k = m. G is optimal. QED.

### Example 2: Job Scheduling with Deadlines

**Problem**: n jobs, each with deadline d_i and processing time 1. Minimize the number
of late jobs (jobs completed after their deadline).

**Greedy**: Sort by deadline. Process in deadline order.

**Exchange argument**: If an optimal solution processes job b (later deadline) before
job a (earlier deadline), swapping them cannot make a late (a now finishes earlier)
and can only help b (if b was already late, it stays late; if not, it still finishes
by its later deadline since a's processing time equals b's).

### Example 3: Fractional Knapsack

**Problem**: n items with weights w_i and values v_i. Knapsack capacity W. Items can be
taken fractionally. Maximize total value.

**Greedy**: Sort by value-to-weight ratio v_i/w_i in decreasing order. Take as much
of each item as possible.

**Proof by exchange argument**: Consider an optimal solution O that differs from greedy
solution G. There must exist items a, b where a has higher ratio, G takes more of a
than O, and O takes more of b than G. Replace a small amount of b in O with the same
weight of a. Since a has higher value/weight, the total value increases or stays the
same. Repeat until O matches G.

**Note**: This argument fails for 0/1 knapsack (items cannot be split), which is why
0/1 knapsack requires DP.

---

## Section 3: More Greedy Paradigms

### Paradigm 2: Priority Queue Greedy

Some greedy algorithms maintain a priority queue (heap) to efficiently access the
current best choice.

**Huffman Coding**:

**Problem**: Given characters with frequencies f_1, ..., f_n, build a binary prefix code
minimizing the expected code length: sum f_i * l_i, where l_i is the code length of
character i.

**Algorithm**: Repeatedly extract the two nodes with smallest frequency, merge them into
a new node with frequency = sum of children. Repeat until one node remains.

```
while (pq.size() > 1):
    a = pq.extract_min()
    b = pq.extract_min()
    new_node = Node(freq = a.freq + b.freq, left = a, right = b)
    pq.insert(new_node)
```

**Theorem**: Huffman's algorithm produces an optimal prefix code.

**Proof sketch via exchange argument**:

*Lemma 1*: An optimal tree is full (every internal node has two children).
Proof: A node with one child can be eliminated by promoting its child, shortening all
codes in that subtree. This improves or preserves the objective.

*Lemma 2*: The two lowest-frequency characters can be siblings at maximum depth.
Proof: Let x, y be the two lowest-frequency characters. In any optimal full tree, let
a, b be siblings at maximum depth. If {a,b} != {x,y}, swap x with a (if x != a):
the cost change is (f_x - f_a)(depth_a - depth_x). Since f_x <= f_a and depth_a is
maximum, depth_a >= depth_x, so the cost change is <= 0 (cost doesn't increase).
Similarly swap y with b. So there exists an optimal tree with x, y as siblings.

*Main argument*: After merging x and y into a node z with frequency f_x + f_y, the
problem reduces to building an optimal tree for the remaining characters plus z. By
optimal substructure (the cost of the merged subtree contributes f_x + f_y to z's
parent's frequency, which correctly accounts for the extra depth), the reduced problem
has the same structure. By induction, Huffman's algorithm is optimal. QED.

### Paradigm 3: Greedy Stays Ahead

Instead of exchanging, show that at every step, the greedy solution is at least as good
as any other solution.

**Structure**:
1. Define a measure of "progress" at each step.
2. Show by induction that greedy's progress >= any other solution's progress at every step.
3. Conclude that greedy's final solution is at least as good.

This is exactly what we did for interval scheduling: we showed g_i.end <= o_i.end
at every step (greedy "stays ahead" by always finishing no later).

---

## Section 4: Greedy vs DP -- The Boundary

### Decision Framework

Given an optimization problem, ask:

1. **Can I prove the exchange argument?** If yes, greedy works.
2. **Is there a clear locally optimal choice?** If yes and the exchange argument holds,
   greedy works.
3. **Do different locally optimal choices lead to different global outcomes?** If yes,
   greedy fails; use DP.

### Concrete Examples at the Boundary

**Activity selection with weights**: Each interval has a weight. Maximize total weight.
- Greedy (by end time) fails: a long, heavy interval might be skipped in favor of
  many short, light intervals.
- **DP is required**: sort by end time, dp[i] = max(dp[i-1], w_i + dp[j]) where j is
  the latest non-overlapping interval before i.

**Coin change (canonical systems)**: Given denominations {1, 5, 10, 25}, make change
for amount N using fewest coins.
- Greedy (largest denomination first) works for US coin denominations.
- But for {1, 3, 4}, making change for 6: greedy gives 4+1+1 (3 coins), optimal is
  3+3 (2 coins). Greedy fails.
- **The difference**: US denominations satisfy a particular divisibility structure;
  arbitrary denominations do not.

**Shortest paths**: Dijkstra's algorithm is greedy (always relax the nearest unvisited
node). It works because edge weights are non-negative, ensuring the greedy choice property:
the nearest unvisited node's shortest-path distance is final.
With negative weights, Dijkstra fails; use Bellman-Ford (which is DP).

### Summary Table

| Problem                          | Greedy? | Why / Why Not                              |
|----------------------------------|---------|--------------------------------------------|
| Interval scheduling (unweighted) | Yes     | Earliest end time; exchange argument works |
| Interval scheduling (weighted)   | No      | Weight makes local choice suboptimal       |
| Fractional knapsack              | Yes     | Best ratio first; exchange on fractions    |
| 0/1 knapsack                     | No      | Cannot split items; greedy ratio fails     |
| Huffman coding                   | Yes     | Merge smallest; exchange on tree structure |
| Coin change (US denominations)   | Yes     | Divisibility structure of denominations    |
| Coin change (arbitrary)          | No      | Greedy denomination may block better combo |
| Dijkstra (non-negative weights)  | Yes     | Nearest node is final; no negative cycles  |
| Shortest path (negative weights) | No      | Nearest node may not be final              |

---

## Section 5: Common Greedy Proof Patterns

### Pattern 1: Ratio Ordering

When items have two attributes (cost and benefit), sort by benefit/cost ratio.

**Exchange**: If optimal has items (a, b) in wrong ratio order, swapping improves
or preserves the objective because the item with better ratio contributes more per unit.

**Examples**: Fractional knapsack, weighted job scheduling on a single machine
(Smith's rule: sort by processing time / weight).

### Pattern 2: Deadline/Time Ordering

When items have deadlines or time constraints, sort by deadline.

**Exchange**: Processing earlier-deadline items first cannot worsen the schedule
because they have tighter constraints. Delaying them risks missing their deadlines.

### Pattern 3: Matroid Theory (Advanced)

A **matroid** M = (E, I) consists of a ground set E and a family I of "independent sets"
satisfying:
1. The empty set is in I.
2. If A is in I and B is a subset of A, then B is in I (hereditary property).
3. If A, B are in I and |A| < |B|, then there exists x in B \ A such that A + x is in I
   (exchange property -- not to be confused with the exchange argument!).

**Theorem (Rado-Edmonds)**: The greedy algorithm (repeatedly add the maximum-weight
element that maintains independence) finds a maximum-weight independent set on any
weighted matroid.

**Why this matters**: Many greedy problems are secretly matroid problems. Recognizing
the matroid structure gives an instant proof of greedy correctness.

**Examples of matroids**:
- **Uniform matroid**: I = {S subset of E : |S| <= k}. Greedy = take k heaviest elements.
- **Graphic matroid**: E = edges of a graph, I = forests. Greedy = Kruskal's MST algorithm.
- **Partition matroid**: E is partitioned into groups, I = sets taking at most k_i from group i.

### Pattern 4: Cut Property for MST

**Theorem (Cut Property)**: For any cut of the graph, the minimum-weight edge crossing
the cut is in some MST.

**Proof**: Let e be the min-weight crossing edge, and T be an MST not containing e.
Adding e to T creates a cycle that must cross the cut (since e does). Let e' be another
edge in this cycle crossing the cut. Since w(e) <= w(e'), replacing e' with e gives
a spanning tree of weight <= w(T). So this new tree is also an MST containing e. QED.

Both Kruskal's and Prim's algorithms are applications of the cut property:
- **Kruskal**: Process edges in weight order; add if it doesn't form a cycle. The edge
  connects two components, and it's the lightest edge crossing that cut.
- **Prim**: Grow a tree from a source; always add the lightest edge leaving the current tree.
  This edge crosses the cut (tree, non-tree) and is minimum, so the cut property applies.
