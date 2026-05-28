# The Prefix Function and KMP — A Complete Guide

A series of twelve self-contained lessons that take you from "what is a border?" to "how do I pattern-match against a string defined by a recursion?". Every claim is proved, every algorithm is implemented in 1-indexed C++, and every lesson builds on the previous one.

**Notation conventions used throughout:**

| Symbol | Meaning |
|--------|---------|
| `s`, `t`, `p` | strings |
| `|s|` or `n` | length of `s` |
| `s[i]` | the `i`-th character of `s` (1-indexed) |
| `s[i..j]` | the contiguous substring from position `i` to `j` (inclusive); empty if `i > j` |
| `ε` | the empty string |
| `π[i]` | the prefix-function value at position `i` |
| `π^k[i]` | applying π to itself k times: π[i], π[π[i]], etc. |
| `Σ`, `σ` | the alphabet and its size (e.g., 26) |
| `rev(s)` | the reverse of `s` |
| `s · t` or `st` | concatenation |
| `s^q` | `s` concatenated with itself `q` times |

**1-Indexed C++ convention.** We treat the input string as having "real" characters at indices 1..n. In C++, this is achieved by prepending a dummy character (typically a space) to the input:

```cpp
string s = " " + raw_input;  // now s[1..n] are the real characters
int n = (int)s.size() - 1;
```

All vectors, including the prefix-function array `pi[1..n]`, are sized `n+1` and use index 0 as a slot we never read.

---

## Table of Contents

1. [Strings, Prefixes, Suffixes, Borders](#lesson-1-strings-prefixes-suffixes-and-borders)
2. [The Prefix Function π — Definition, Examples, Naïve Algorithm](#lesson-2-the-prefix-function-π--definition-examples-naïve-algorithm)
3. [The Border-Structure Theorem (the π-chain)](#lesson-3-the-border-structure-theorem-the-π-chain)
4. [The Monotonicity Lemma](#lesson-4-the-monotonicity-lemma-πi1--πi--1)
5. [The Linear-Time Algorithm + Amortized Analysis](#lesson-5-the-linear-time-algorithm)
6. [Application — KMP Pattern Matching](#lesson-6-application-1--kmp-pattern-matching)
7. [Application — Counting Prefix Occurrences](#lesson-7-application-2--counting-occurrences-of-each-prefix)
8. [Application — Distinct Substrings (Online)](#lesson-8-application-3--number-of-distinct-substrings-online)
9. [Application — Periods, Borders, String Compression](#lesson-9-application-4--periods-borders-and-string-compression)
10. [Application — The KMP Automaton](#lesson-10-application-5--the-kmp-automaton)
11. [Advanced — Border Tree, Fine-Wilf, Z-Function, Connections](#lesson-11-advanced--border-tree-fine-wilf-z-function-connections)
12. [Pitfalls, Common Bugs, Practice Problems](#lesson-12-pitfalls-common-bugs-and-practice-problems)

---

# Lesson 1: Strings, Prefixes, Suffixes, and Borders

## 1.1 Goals
- Establish vocabulary and notation (1-indexed).
- Define prefix, suffix, **border**.
- Prove the crucial *nested-borders* lemma — the seed of the π-chain theorem in Lesson 3.

## 1.2 Strings, Prefixes, Suffixes

A string `s` of length `n` is the sequence `s[1], s[2], ..., s[n]`. Substrings are `s[i..j]`; we set `s[i..j] = ε` (empty string) if `i > j`.

A **prefix** of `s` of length `k` (0 ≤ k ≤ n) is `s[1..k]`. It is **proper** if `k < n`.

A **suffix** of `s` of length `k` is `s[n-k+1..n]`. It is proper if `k < n`.

So `s` has exactly `n+1` prefixes (including ε and `s` itself), of which `n` are proper, of which `n-1` are non-empty and proper.

## 1.3 Borders

A **border** of `s` is a string α that is both a proper prefix and a proper suffix of `s`. Equivalently, α has some length `k` with 0 ≤ k < n such that `s[1..k] = s[n-k+1..n]`. We let

> `B(s) = { k : 0 ≤ k < n, s[1..k] = s[n-k+1..n] }`

the set of border *lengths* of `s`. The empty string (length 0) is in `B(s)` for every non-empty `s` — a useful "anchor" for the chain we will build in Lesson 3.

Borders are sometimes called *failure values* (the failure-function notation in textbooks) or *bifixes* (older literature).

## 1.4 Examples — compute by hand

### s = "abacaba" (n = 7)

| k | s[1..k] | s[n-k+1..n] | border? |
|---|---------|-------------|---------|
| 0 | ε | ε | yes |
| 1 | "a" | "a" | yes |
| 2 | "ab" | "ba" | no |
| 3 | "aba" | "aba" | yes |
| 4 | "abac" | "caba" | no |
| 5 | "abaca" | "acaba" | no |
| 6 | "abacab" | "bacaba" | no |

So `B("abacaba") = {0, 1, 3}`. Longest proper border has length 3.

### s = "aabaaab" (n = 7)

`B("aabaaab") = {0, 3}`. (Try it.)

### s = "ababab" (n = 6)

`B("ababab") = {0, 2, 4}`.

### s = "aaaa" (n = 4)

`B("aaaa") = {0, 1, 2, 3}`. Notice the borders form a complete chain.

## 1.5 Why Borders Matter — A Preview

Imagine you are scanning a text `t` looking for occurrences of a pattern `p`. You have matched `p[1..k]` against `t[i-k+1..i]`, and the next character mismatches: `p[k+1] ≠ t[i+1]`.

You do **not** have to restart from `i+1`. Instead, you should ask: what is the longest prefix of `p` that is a suffix of `t[1..i]`? Since the last `k` characters of `t[1..i]` equal `p[1..k]`, the answer is the longest border of `p[1..k]`. That tells you the right "shift" — and the right starting state — for continuing the search.

This is the heart of KMP. Borders encode "how much of my progress can I keep on a mismatch?".

## 1.6 The Nested-Borders Lemma

This is small but absolutely crucial. We will lean on it in Lesson 3.

> **Lemma 1.1 (Nested Borders).** If β is a border of `s` and α is a border of β, then α is a border of `s`.

**Proof.** Let `|s| = n`, `|β| = k`, `|α| = j`, with j < k < n.
- α is a prefix of β, and β is a prefix of `s`. So α is a prefix of `s`. Concretely α = `β[1..j] = s[1..j]`.
- α is a suffix of β: α = `β[k-j+1..k]`. And β is a suffix of `s`: β = `s[n-k+1..n]`. Translating: `β[k-j+1..k] = s[(n-k+1)+(k-j+1)-1 .. (n-k+1)+k-1] = s[n-j+1..n]`. So α = `s[n-j+1..n]`, a suffix of `s`.

So α is both a prefix and a suffix of `s`, and `j < n` (since j < k < n), so α is a proper border of `s`. ∎

**Converse (also true; try to prove).** If α and β are both borders of `s` with |α| < |β|, then α is a border of β.

So borders chain: from any border, smaller borders are *exactly* the borders of that border. This nesting structure is what the π-chain theorem will turn into an algorithm.

## 1.7 Exercises

1. Compute `B(s)` for: `"aaa"`, `"aabaab"`, `"abcabc"`, `"abcabcabc"`, `"xyzxyzxyz"`, `"aabaaaba"`.
2. Show that `|B(s)|` can be as large as `n` (consider `s = "aaaa...a"`).
3. Prove the converse: if α, β ∈ borders of `s` with |α| < |β|, then α ∈ borders of β.
4. Show that the longest proper border of `"aaaa...a"` (length n) is `"aaaa...a"` (length n-1).

---

# Lesson 2: The Prefix Function π — Definition, Examples, Naïve Algorithm

## 2.1 Goals
- State the formal definition.
- Compute π by hand on three examples.
- Implement the O(n³) brute force so you feel why it must be improved.

## 2.2 Formal Definition

For a string `s` of length `n`, the **prefix function** is the array `π[1..n]` defined by

> `π[i] = max { k : 0 ≤ k < i, s[1..k] = s[i-k+1..i] }`

That is, `π[i]` is the length of the longest proper border of the prefix `s[1..i]`. The empty string always works (k=0), so the max always exists.

Equivalently: **`π[i] = the largest element of B(s[1..i])`**.

By convention, `π[1] = 0`: the only prefix of a single character is the empty string.

## 2.3 Three Worked Examples

### Example 1: s = "abcabcd" (n=7)

| i | s[1..i] | longest proper border | π[i] |
|---|---------|----------------------|------|
| 1 | "a" | ε | 0 |
| 2 | "ab" | ε | 0 |
| 3 | "abc" | ε | 0 |
| 4 | "abca" | "a" | 1 |
| 5 | "abcab" | "ab" | 2 |
| 6 | "abcabc" | "abc" | 3 |
| 7 | "abcabcd" | ε | 0 |

So `π = [_, 0, 0, 0, 1, 2, 3, 0]`. (The leading `_` marks the unused index 0 in the 1-indexed convention.)

### Example 2: s = "aabaaab" (n=7)

| i | s[1..i] | longest proper border | π[i] |
|---|---------|----------------------|------|
| 1 | "a" | ε | 0 |
| 2 | "aa" | "a" | 1 |
| 3 | "aab" | ε | 0 |
| 4 | "aaba" | "a" | 1 |
| 5 | "aabaa" | "aa" | 2 |
| 6 | "aabaaa" | "aa" | 2 |
| 7 | "aabaaab" | "aab" | 3 |

So `π = [_, 0, 1, 0, 1, 2, 2, 3]`.

### Example 3: s = "aaaa" (n=4)

`π = [_, 0, 1, 2, 3]`. Each prefix of length ≥ 2 has its previous prefix as a border.

## 2.4 Three Properties to Remember

1. **Range.** 0 ≤ π[i] < i for all `i`.
2. **Anchor.** π[1] = 0.
3. **Semantic.** If π[i] = k > 0, then s[1..k] = s[i-k+1..i].

We will add a fourth crucial property in Lesson 4.

## 2.5 The Naïve O(n³) Algorithm

The definition itself is an algorithm: for each `i`, try every `k` from `i-1` downwards until you find a match.

```cpp
vector<int> prefix_function_naive(const string& s) {
    // 1-indexed: s[1..n] hold actual chars; s[0] is a dummy
    int n = (int)s.size() - 1;
    vector<int> pi(n + 1, 0);
    pi[1] = 0;
    for (int i = 2; i <= n; ++i) {
        for (int k = i - 1; k >= 0; --k) {
            bool ok = true;
            for (int j = 1; j <= k; ++j) {
                if (s[j] != s[i - k + j]) { ok = false; break; }
            }
            if (ok) { pi[i] = k; break; }
        }
    }
    return pi;
}
```

**Complexity.** Outer loop: n iterations. Middle loop: up to i iterations. Inner string-comparison: up to k ≤ i characters. Worst case: O(n³).

For `n = 10⁴` this is already 10¹² operations — far too slow. We need ideas. The next two lessons supply them.

## 2.6 Exercises

1. Implement the naïve algorithm and compute π for the three examples above. Verify they match.
2. Construct a string where the inner loop runs many times. (Hint: `"aaaa...ab"`.)
3. What is π for `"abcabcabcabc"`?

---

# Lesson 3: The Border-Structure Theorem (the π-chain)

## 3.1 Goal
Prove that the chain `π[i], π²[i], π³[i], ..., 0` enumerates **every** border length of `s[1..i]`. This single theorem is what makes both the linear algorithm and most applications possible.

## 3.2 Statement

> **Theorem 3.1 (π-Chain).** For every string `s` and every `1 ≤ i ≤ n`, the set of proper border lengths of `s[1..i]` is exactly
>
> > { π[i], π²[i], π³[i], ..., 0 }
>
> where `π^k[i]` means applying π to itself k times: `π¹[i] = π[i]`, `π²[i] = π[π[i]]`, etc., and the chain terminates at 0.
>
> In particular, the proper border lengths of `s[1..i]` in **strictly decreasing order** are `π[i] > π²[i] > π³[i] > ... > 0`.

## 3.3 Why This is Powerful

If you know π[i], you know the longest border. If you know π[π[i]], you know the second-longest. And so on. Walking the chain enumerates all borders in time proportional to the number of borders. No nested loops, no scanning.

## 3.4 Proof of Theorem 3.1

The key step is:

> **Lemma 3.2 (Border Restriction).** Let `b = π[i]`. If `0 < k < b` and `k` is a border length of `s[1..i]`, then `k` is a border length of `s[1..b]`.

**Proof of the Lemma.**
- Since `b = π[i]` is a border of `s[1..i]`: `s[1..b] = s[i-b+1..i]`. *(†)*
- Since `k` is a border of `s[1..i]`: `s[1..k] = s[i-k+1..i]`. *(‡)*
- The right side of *(‡)* is the last `k` characters of `s[1..i]`. Because `k < b`, these are also the last `k` characters of the rightmost window `s[i-b+1..i]`. Specifically: `s[i-k+1..i] = (s[i-b+1..i])[b-k+1..b]`.
- By *(†)*, `s[i-b+1..i] = s[1..b]`. Applying the same windowing: `(s[i-b+1..i])[b-k+1..b] = (s[1..b])[b-k+1..b] = s[b-k+1..b]`.
- Therefore `s[i-k+1..i] = s[b-k+1..b]`, i.e., `s[1..k] = s[b-k+1..b]` by *(‡)*.
- That last equality says: `k` is a border length of `s[1..b]`. ∎

(The reverse direction — borders of `s[1..b]` are borders of `s[1..i]` — is the converse of Lemma 1.1 / Nested Borders, and is true because if `k ≤ b ≤ i` and `s[1..k]` is both a prefix and a suffix of `s[1..b]`, then it is a prefix of `s[1..i]` automatically, and a suffix of `s[1..i]` because `s[1..b]` itself is a suffix of `s[1..i]`.)

**Proof of Theorem 3.1.** By strong induction on `i`.

- **Base** `i = 1`: The only proper border of `s[1..1]` is ε (length 0). The chain is `π[1] = 0`, so the set is `{0}`. ✓

- **Inductive step**: Assume the theorem holds for every `i' < i`. Let `b = π[i]`.
  - By definition, `b` is a border length of `s[1..i]`. It is the *largest* such proper border length.
  - Every other border length `k` of `s[1..i]` satisfies `k < b`. By Lemma 3.2, every such `k` is a border length of `s[1..b]`.
  - Conversely, every border length of `s[1..b]` is a border length of `s[1..i]` (Lemma 1.1 applied to "α is a border of β where β = `s[1..b]` is a border of `s[1..i]`").
  - So: border lengths of `s[1..i]` less than `b` = border lengths of `s[1..b]`.
  - By inductive hypothesis applied to `i' = b < i`: border lengths of `s[1..b]` = `{ π[b], π²[b], ..., 0 }` = `{ π²[i], π³[i], ..., 0 }`.
  - Including `b = π[i]`, all border lengths of `s[1..i]` = `{ π[i], π²[i], π³[i], ..., 0 }`. ∎

## 3.5 Application: Enumerate All Borders of a Given Prefix

```cpp
void list_border_lengths(int i, const vector<int>& pi) {
    int k = pi[i];
    while (k > 0) {
        cout << k << " ";
        k = pi[k];
    }
    cout << 0 << '\n';
}
```

Time: O(number of borders), which is at most i but in practice often O(log i).

## 3.6 Application: The "Failure Tree" (preview)

Define a tree where each node `k ∈ {0, 1, ..., n}` has parent `π[k]` (and node 0 is the root). This is the **failure tree** (a.k.a. border tree). The path from node `i` up to root spells out all border lengths of `s[1..i]`. We will revisit this in Lesson 7 (counting) and Lesson 11 (advanced).

## 3.7 Exercises

1. For `s = "aabaaab"`, list all borders of `s[1..7]` using the chain.
2. Show that for `s = "aaaaa"` the chain at position 5 is `4, 3, 2, 1, 0`.
3. (Subtle.) Show that the converse to Lemma 3.2 is also true: if `k` is a border of `s[1..b]` then `k` is a border of `s[1..i]` (given `b` is a border of `s[1..i]`). Hint: nested-borders lemma from Lesson 1.

---

# Lesson 4: The Monotonicity Lemma: π[i+1] ≤ π[i] + 1

## 4.1 Goal

Prove a simple but powerful upper bound on how fast π can grow. This is the second ingredient for the linear algorithm.

## 4.2 Statement

> **Lemma 4.1 (Monotonicity / Slow-Growth).** For every `i` with `1 ≤ i < n`,
>
> > π[i+1] ≤ π[i] + 1.

In words: π can jump up by at most 1 per step. It can drop by any amount, but it can grow only one notch at a time.

## 4.3 Proof

Suppose for contradiction `π[i+1] = c > π[i] + 1`.

By definition, `s[1..c] = s[(i+1)-c+1..i+1] = s[i-c+2..i+1]`.

Strip off the last character on both sides: `s[1..c-1] = s[i-c+2..i]`.

The right side has length `c - 1` and ends at position `i`. The left side has length `c - 1`. So `s[1..c-1]` is a proper border of `s[1..i]` of length `c - 1`.

But `π[i]` is the **maximum** border length of `s[1..i]`, so `c - 1 ≤ π[i]`, i.e., `c ≤ π[i] + 1`. This contradicts `c > π[i] + 1`. ∎

## 4.4 Consequence: Total Growth is at Most n

Summing telescopically (using `π[0] = 0` by convention):

> Σᵢ₌₁ⁿ (π[i] − π[i−1]) = π[n] − π[0] ≤ n.

The "increase" part of this sum is at most n − π[0] + (total decrease amount). Since the total change is bounded, the total *positive* movement (matches) plus the total *negative* movement (fall-backs through the chain) are tightly linked. This is the basis of the amortized analysis in Lesson 5.

## 4.5 Tight Example

For `s = "aaaa...a"` of length n, π[i] = i − 1 for all i ≥ 1. So π grows by exactly 1 at every step. The bound is tight.

## 4.6 Exercises

1. Verify the bound on π[i] for `s = "aabaaab"`.
2. Construct a string where π[i] drops from a large value to 0 in one step.
3. Argue: if `π[i+1] = π[i] + 1`, then `s[π[i]+1] = s[i+1]`. (Use the proof above in reverse.)

---

# Lesson 5: The Linear-Time Algorithm

## 5.1 Goal
- Derive the linear-time recurrence using Lessons 3 and 4.
- Implement it in 1-indexed C++.
- Trace it on an example.
- Prove the amortized O(n) bound using a potential function.

## 5.2 Deriving the Recurrence

We compute π[i] assuming π[1..i-1] is known. Let `j = π[i-1]`. By definition,

> `s[1..j] = s[i-j..i-1]`. *(★)*

We want the longest border of `s[1..i]`. By the monotonicity lemma, it has length at most `j + 1`.

**Case 1**: `s[j+1] = s[i]`. Then *(★)* extends one position to the right:

> `s[1..j+1] = s[i-j..i]`,

which says `s[1..j+1]` is a proper border of `s[1..i]`. By monotonicity, no border of length > `j + 1` exists. So `π[i] = j + 1`.

**Case 2**: `s[j+1] ≠ s[i]`. Then `j + 1` is *not* a valid border length. We need the next-longest border length of `s[1..i]` of the form "border of `s[1..i-1]`, then check if the next character matches `s[i]`".

The next-largest border of `s[1..i-1]` (after `j = π[i-1]`) is — by the π-chain theorem (Lesson 3) — `π[j]`.

So we set `j ← π[j]` and try again: is `s[j+1] = s[i]`? If yes, `π[i] = j + 1`. If no, fall back again to `π[j]`. Continue until either we find a match or `j` reaches 0.

If `j = 0` and `s[1] ≠ s[i]`, then `π[i] = 0`.
If `j = 0` and `s[1] = s[i]`, then `π[i] = 1`.

## 5.3 The 1-Indexed C++ Implementation

```cpp
vector<int> prefix_function(const string& s) {
    // Convention: s[0] is a dummy character; s[1..n] are the real chars.
    int n = (int)s.size() - 1;
    vector<int> pi(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j + 1])
            j = pi[j];
        if (s[i] == s[j + 1])
            ++j;
        pi[i] = j;
    }
    return pi;
}
```

**Why `s[j + 1]`?** Because `j` is the length already matched, so the next pattern character to test is at position `j + 1` (1-indexed). In the 0-indexed cp-algorithms version this appears as `s[j]`.

## 5.4 Hand Trace: s = " aabaaabaaa" (1-indexed, n = 10)

Characters: `s[1]=a, s[2]=a, s[3]=b, s[4]=a, s[5]=a, s[6]=a, s[7]=b, s[8]=a, s[9]=a, s[10]=a`.

| i | j_start (= π[i-1]) | iter(s) of while loop | post-while j | match? | π[i] |
|---|--------------------|------------------------|--------------|--------|------|
| 2 | 0 | none | 0 | s[2]='a' = s[1]='a' ✓ | 1 |
| 3 | 1 | s[3]='b' vs s[2]='a' ✗ ⇒ j ← π[1] = 0 | 0 | s[3]='b' vs s[1]='a' ✗ | 0 |
| 4 | 0 | none | 0 | s[4]='a' vs s[1]='a' ✓ | 1 |
| 5 | 1 | none | 1 | s[5]='a' vs s[2]='a' ✓ | 2 |
| 6 | 2 | s[6]='a' vs s[3]='b' ✗ ⇒ j ← π[2] = 1 | 1 | s[6]='a' vs s[2]='a' ✓ | 2 |
| 7 | 2 | none | 2 | s[7]='b' vs s[3]='b' ✓ | 3 |
| 8 | 3 | none | 3 | s[8]='a' vs s[4]='a' ✓ | 4 |
| 9 | 4 | none | 4 | s[9]='a' vs s[5]='a' ✓ | 5 |
| 10 | 5 | none | 5 | s[10]='a' vs s[6]='a' ✓ | 6 |

So `π = [_, 0, 1, 0, 1, 2, 2, 3, 4, 5, 6]`.

Sanity check: `π[10] = 6` means the longest proper border of "aabaaabaaa" has length 6 = "aabaaa". Take last 6 chars: `s[5..10] = "aabaaa"`. ✓

## 5.5 Why This Runs in O(n) — The Amortized Argument

> **Theorem 5.1.** The above algorithm runs in O(n) total time.

**Proof using a potential function.** Define the potential Φ to be the current value of `j` between iterations. Specifically, right after iteration `i` of the outer loop, `Φ = π[i]`. Initially (before iteration 2) `Φ = π[1] = 0`. Always `Φ ≥ 0`.

Consider iteration `i`:
1. The while-loop executes some number `w_i ≥ 0` of iterations. Each iteration strictly decreases `j` (since `π[j] < j` for `j > 0`). So `j` decreases by at least `w_i`. Cost: w_i.
2. The post-while match check executes once. It either increments `j` by 1 (if matched) or leaves it unchanged. Cost: O(1). `j` increases by at most 1.

Combining, the *net* change in `j` over iteration `i` is at most `+1 − w_i` (could be less if no match). Equivalently, the increase in Φ is `Φ_after − Φ_before ≤ 1 − w_i`.

Define amortized cost = actual cost + change in Φ. For iteration `i`, actual cost ≤ `w_i + O(1)`, change in Φ ≤ `1 − w_i`. So amortized cost ≤ `O(1) + 1 = O(1)`.

Sum over `i` from 2 to n: total amortized cost ≤ O(n).

Total actual cost = total amortized cost − (Φ_final − Φ_initial) = total amortized cost − π[n] + 0 ≤ O(n) (since π[n] ≥ 0).

Hence total actual cost = O(n). ∎

The intuitive picture: every while-iteration *destroys* one unit of "matched length" that was built up over a prior match. Since matched length never exceeds n, the total destruction over the whole run is at most n.

## 5.6 Common Bugs

| Bug | Symptom | Fix |
|-----|---------|-----|
| Using 0-indexed `s[j]` in a 1-indexed algorithm | Wrong values, possibly array out-of-bounds | Use `s[j + 1]` in 1-indexed |
| Forgetting `if (s[i] == s[j + 1]) ++j;` | π[i] always 0 except for trivial matches | Add the match check |
| Not initializing pi to zero | Garbage values | `vector<int>(n+1, 0)` |
| Reading raw input directly without dummy | Off-by-one over the whole code | Prepend `" "` |
| Using `pi[i-1]` instead of `pi[j]` in the while loop | Infinite loop or wrong result | The while loop falls back via `pi[j]`, not `pi[i-1]` |

## 5.7 Exercises

1. Hand-trace π for `" ababab"`, `" abcabcd"`, `" abacaba"`.
2. Implement and verify the algorithm. Compare against the naïve from Lesson 2.
3. Modify the algorithm to also output, for each i, the **second-longest** proper border of s[1..i].
4. Prove: if `s = "aaaa...a"` of length `n`, the while-loop body executes 0 times in total across the run. (The "best case".)
5. Construct a string where the while-loop body executes Θ(n) times in total. (The "worst case".)

---

# Lesson 6: Application 1 — KMP Pattern Matching

## 6.1 Goal
Find all occurrences of a pattern `p` of length `m` in a text `t` of length `n`, in O(n + m) time and O(m) extra space.

## 6.2 Method 1 — Concatenation s = p + '#' + t

Let `#` be a fresh character that appears in neither `p` nor `t`. Form

> `s = p · '#' · t`, where `|s| = m + 1 + n`.

Indices: `s[1..m] = p`, `s[m+1] = '#'`, `s[m+2..m+1+n] = t`.

Compute `π` for `s`.

> **Claim 6.1.** For each `i` in the range `[m+2, m+1+n]` (i.e., for each position of `s` that lies inside the t-section), if `π[i] = m`, then **`p` occurs in `t` starting at position `i − 2m`** (1-indexed in `t`).

**Why `π[i] ≤ m` always:** Suppose `π[i] = k ≥ m + 1`. Then `s[1..k] = s[i-k+1..i]`. In particular, `s[m+1] = '#' = s[(i-k+1) + m]`. But `(i-k+1) + m ≤ i` is a position in the t-section (i ≥ m+2, k ≥ m+1, so (i-k+1)+m ≥ m+2 only when... let's just observe directly: any character in the t-section is from t's alphabet, while `#` is not. So `s[(i-k+1)+m] ≠ '#'`. Contradiction. Hence `π[i] ≤ m`.

**Why `π[i] = m` implies a match at `i − 2m` in t:** Take `π[i] = m`. Then `s[1..m] = s[i-m+1..i]`, i.e., `p = s[i-m+1..i]`. The substring `s[i-m+1..i]` lies entirely in the t-section iff `i-m+1 ≥ m+2`, i.e., `i ≥ 2m+1`. For `i ≥ 2m+1`, the position of this match in `t` (1-indexed) is `(i-m+1) - (m+1) = i - 2m`.

What if `m+2 ≤ i < 2m+1`? Then the apparent "match" would straddle the `#`, which is impossible since `π[i] ≤ m` and the `#` blocks longer matches. Concretely, for `i < 2m+1`, `π[i] < m` always.

### Code (1-indexed)

```cpp
vector<int> kmp_match_concat(const string& pattern, const string& text) {
    int m = (int)pattern.size() - 1;  // 1-indexed lengths
    int n = (int)text.size() - 1;
    
    string s = " ";
    for (int i = 1; i <= m; ++i) s += pattern[i];
    s += '#';
    for (int i = 1; i <= n; ++i) s += text[i];
    // s[1..m+1+n] = p#t
    
    vector<int> pi = prefix_function(s);
    
    vector<int> matches;
    for (int i = m + 2; i <= m + 1 + n; ++i) {
        if (pi[i] == m)
            matches.push_back(i - 2 * m);
    }
    return matches;
}
```

Complexity: O(n + m) time and O(n + m) space.

## 6.3 Method 2 — On-the-Fly (the "classic" KMP)

We don't need to materialize the concatenation. Compute π just for the pattern, then run the same recurrence on the text:

```cpp
vector<int> kmp_match_online(const string& pattern, const string& text) {
    int m = (int)pattern.size() - 1;
    int n = (int)text.size() - 1;
    vector<int> pi_p = prefix_function(pattern);
    
    vector<int> matches;
    int j = 0;  // current matched length
    for (int i = 1; i <= n; ++i) {
        while (j > 0 && text[i] != pattern[j + 1])
            j = pi_p[j];
        if (text[i] == pattern[j + 1])
            ++j;
        if (j == m) {
            matches.push_back(i - m + 1);  // 1-indexed start in t
            j = pi_p[j];                   // shift to look for next match
        }
    }
    return matches;
}
```

Complexity: O(n + m) time and O(m) space. Same amortized analysis as Lesson 5 (Φ = j is bounded by m, total destruction ≤ n + m).

## 6.4 Worked Example

`p = "aba"` (m=3), `t = "abaababa"` (n=8).

**Method 2 trace** (using `pi_p` of `" aba"` which is `[_, 0, 0, 1]`):

| i | t[i] | j_start | while | post-while j | match step | j_after | output |
|---|------|---------|-------|--------------|------------|---------|--------|
| 1 | 'a' | 0 | — | 0 | s[1]='a' ✓ | 1 | — |
| 2 | 'b' | 1 | — | 1 | s[2]='b' ✓ | 2 | — |
| 3 | 'a' | 2 | — | 2 | s[3]='a' ✓ | 3 | match at 1; j ← π[3] = 1 |
| 4 | 'a' | 1 | s[2]='b' ≠ 'a', j ← π[1] = 0 | 0 | s[1]='a' ✓ | 1 | — |
| 5 | 'b' | 1 | — | 1 | s[2]='b' ✓ | 2 | — |
| 6 | 'a' | 2 | — | 2 | s[3]='a' ✓ | 3 | match at 4; j ← π[3] = 1 |
| 7 | 'b' | 1 | — | 1 | s[2]='b' ✓ | 2 | — |
| 8 | 'a' | 2 | — | 2 | s[3]='a' ✓ | 3 | match at 6; j ← π[3] = 1 |

Matches in `t`: positions 1, 4, 6. Verify by eye: `t[1..3]="aba"`, `t[4..6]="aba"`, `t[6..8]="aba"`. ✓

## 6.5 Trade-offs

| | Method 1 (s = p#t) | Method 2 (on-the-fly) |
|---|---------------------|------------------------|
| Space | O(n + m) | O(m) |
| Need a fresh character `#` | Yes | No |
| Conceptual simplicity | Single tool (π) | Two intertwined sequences |
| Useful when… | π values for the whole concatenation are needed for other reasons (e.g., counting prefix-of-p occurrences in t, Lesson 7) | Pure pattern matching with streaming text |

In CP, Method 2 is preferred for memory and conceptual reasons. Method 1 is useful when you also want extra information about the relationship between `p` and `t`.

## 6.6 Counting Occurrences Only

```cpp
long long count_kmp(const string& pattern, const string& text) {
    int m = (int)pattern.size() - 1, n = (int)text.size() - 1;
    vector<int> pi_p = prefix_function(pattern);
    long long cnt = 0;
    int j = 0;
    for (int i = 1; i <= n; ++i) {
        while (j > 0 && text[i] != pattern[j + 1]) j = pi_p[j];
        if (text[i] == pattern[j + 1]) ++j;
        if (j == m) { ++cnt; j = pi_p[j]; }
    }
    return cnt;
}
```

## 6.7 Exercises

1. Implement both methods. Test them on random patterns/texts of length 10⁵.
2. Find all occurrences of `"aab"` in `"aabaabaab"`.
3. Modify Method 2 to support a *streaming* text: it should be processable character by character without lookahead. (Hint: it already is — that's the point.)
4. What if `p` and `t` together use the entire ASCII range? Choose a sentinel character; or use Method 2 which doesn't need one.

---

# Lesson 7: Application 2 — Counting Occurrences of Each Prefix

## 7.1 Goal

Given a string `s` of length `n`, compute `cnt[k]` for each `k ∈ {1, ..., n}` where

> `cnt[k] = number of substrings of s equal to s[1..k]`.

And the related: given a pattern `p` and a text `t`, compute the number of times each prefix of `p` appears in `t`.

The trick uses the failure-tree structure (Lesson 3) cleverly.

## 7.2 Subproblem A — Prefixes in s

### Observation

At every position `i`, the prefixes of `s` that occur ending at `i` are exactly those of lengths in the π-chain of `i`, plus the trivial length `i` itself (which "occurs at position i" because s[1..i] = s[1..i]).

Specifically: `s[1..k] = s[i-k+1..i]` iff `k = i` (the trivial whole-prefix case) or `k ∈ {π[i], π²[i], π³[i], ...} \ {0}` (a proper border).

So `cnt[k] = 1 + #{i : i > k and k is in the π-chain of i}`.

### Algorithm

1. For each `i`, increment `cnt[π[i]]` by 1. After this, `cnt[k]` counts positions where the **longest** border has length `k`.
2. Propagate counts up the failure tree: for `k = n, n-1, ..., 1`, do `cnt[π[k]] += cnt[k]`. After this, `cnt[k]` counts positions where `k` is **somewhere in the chain** (including being the longest border at some other position).
3. Add 1 to each `cnt[k]` for the trivial "prefix occurs as itself" contribution.

The key insight for step 2 is the failure-tree perspective. Each node `k` has parent `π[k]` (a strictly smaller index). Processing nodes in decreasing order of `k` ensures children are processed before parents — so when we add `cnt[k]` to `cnt[π[k]]`, all of `k`'s subtree has already been folded in.

### Code (1-indexed)

```cpp
vector<int> count_prefix_occurrences(const string& s) {
    int n = (int)s.size() - 1;
    vector<int> pi = prefix_function(s);
    vector<int> cnt(n + 1, 0);
    
    // Step 1: count direct π-hits
    for (int i = 1; i <= n; ++i) ++cnt[pi[i]];
    
    // Step 2: propagate up the failure tree
    for (int k = n; k >= 1; --k) cnt[pi[k]] += cnt[k];
    
    // Step 3: trivial whole-prefix contribution
    for (int k = 1; k <= n; ++k) ++cnt[k];
    
    return cnt;  // cnt[k] = # occurrences of s[1..k] in s, for k in 1..n
}
```

Complexity: O(n).

### Worked Example: s = " ababab" (n=6)

We computed in Lesson 5 (Exercise) or can verify: `π = [_, 0, 0, 1, 2, 3, 4]`.

Step 1: `cnt[π[i]]++`:
- i=1: cnt[0]=1
- i=2: cnt[0]=2
- i=3: cnt[1]=1
- i=4: cnt[2]=1
- i=5: cnt[3]=1
- i=6: cnt[4]=1

`cnt = [2, 1, 1, 1, 1, 0, 0]`.

Step 2: propagate from k=6 down to 1:
- k=6: cnt[π[6]=4] += cnt[6]=0. No change.
- k=5: cnt[π[5]=3] += cnt[5]=0. No change.
- k=4: cnt[π[4]=2] += cnt[4]=1. cnt[2]=2.
- k=3: cnt[π[3]=1] += cnt[3]=1. cnt[1]=2.
- k=2: cnt[π[2]=0] += cnt[2]=2. cnt[0]=4.
- k=1: cnt[π[1]=0] += cnt[1]=2. cnt[0]=6.

`cnt = [6, 2, 2, 1, 1, 0, 0]`.

Step 3: add 1 to cnt[1..6]:
`cnt = [6, 3, 3, 2, 2, 1, 1]`.

Verify by inspection:
- `"a"` occurs 3 times in `"ababab"` (positions 1, 3, 5). ✓
- `"ab"` occurs 3 times (1-2, 3-4, 5-6). ✓
- `"aba"` occurs 2 times (1-3, 3-5). ✓
- `"abab"` occurs 2 times (1-4, 3-6). ✓
- `"ababa"` occurs 1 time. ✓
- `"ababab"` occurs 1 time. ✓

## 7.3 Subproblem B — Prefixes of p Inside t

Form `s = p · '#' · t` and compute its `π`. For each position `i` in the t-section (i ≥ m+2), the values in the π-chain `π[i], π²[i], ...` are all ≤ m (as proven in Lesson 6), and they enumerate prefixes of `p` ending at position `i`.

So the algorithm is the same as Subproblem A, but:
- In step 1, only count `cnt[π[i]]` for `i` in the t-section.
- In step 2, propagate only over the pattern-length range (k = m down to 1). The pi-values for `k ∈ [1, m]` are the prefix function of `p` itself.
- Do **not** add 1 in step 3 — we are counting occurrences of `p`'s prefixes in `t`, not occurrences of `p`'s prefixes in `p`.

### Code

```cpp
vector<int> count_prefix_of_p_in_t(const string& pattern, const string& text) {
    int m = (int)pattern.size() - 1;
    int n = (int)text.size() - 1;
    
    string s = " ";
    for (int i = 1; i <= m; ++i) s += pattern[i];
    s += '#';
    for (int i = 1; i <= n; ++i) s += text[i];
    
    int N = m + 1 + n;
    vector<int> pi = prefix_function(s);
    vector<int> cnt(m + 1, 0);
    
    for (int i = m + 2; i <= N; ++i) ++cnt[pi[i]];
    for (int k = m; k >= 1; --k) cnt[pi[k]] += cnt[k];
    
    return cnt;  // cnt[k] = # occurrences of pattern[1..k] in text, for k in 1..m
}
```

### Worked Example

`p = "aba"`, `t = "abaababa"`. From Lesson 6 we know the full pattern `"aba"` occurs at positions 1, 4, 6 in `t` (3 times). So `cnt[3] = 3`.

Direct enumeration:
- `"a"` in `t`: positions 1, 3, 4, 6, 8. cnt[1] = 5.
- `"ab"` in `t`: 1, 4, 6. cnt[2] = 3.
- `"aba"` in `t`: 1, 4, 6. cnt[3] = 3.

You can verify the algorithm produces these.

## 7.4 Exercises

1. Verify Subproblem A on `s = "aabaaab"`.
2. Verify Subproblem B on `p = "aba"`, `t = "abaababa"` step by step.
3. **Hard.** Given `s` of length `n`, for each position `i` output the *number* of prefixes of `s` ending at `i` (i.e., size of π-chain at `i` plus 1 for the trivial whole-prefix). Compute in O(n) using one pass through the failure tree.

---

# Lesson 8: Application 3 — Number of Distinct Substrings (Online)

## 8.1 Goal

Maintain `D(s) = # distinct substrings of s`, supporting the operation "append character `c` to s". Each append updates `D` in O(|s|) time.

## 8.2 The Key Lemma

> **Lemma 8.1.** Let `s' = s · c` for a single character `c`. Let `π_max` be the maximum value of the prefix function of `rev(s')`. Then
>
> > `# new distinct substrings introduced by the append = |s'| − π_max`.

So we maintain a running `D` initialized to 0, and at each append we increment `D` by `|s'| − π_max`.

## 8.3 Proof of Lemma 8.1

Every distinct substring of `s'` is either entirely a substring of `s` (in which case it's not "new") or it ends at position `|s'|` (the newly appended character). So:

> "new substrings" = "non-empty suffixes of s' that are not substrings of s".

There are `|s'|` non-empty suffixes of `s'` (one for each starting position).

**Downward closure.** If the suffix of length `L` of `s'` is a substring of `s`, then for every `0 < L' < L`, the suffix of length `L'` is also a substring of `s`. (Because it's a substring of the L-suffix.)

So there is a maximum `L_max` such that the suffix of length `L_max` of `s'` is a substring of `s`, and suffixes of length > `L_max` are not. Then

> "# new distinct substrings" = `|s'| − L_max`.

**Computing L_max via reversal.** Let `t = rev(s')`. Then:
- suffixes of `s'` ↔ prefixes of `t`.
- substrings of `s = s'[1..|s'|-1]` ↔ substrings of `rev(s) = t[2..|t|]`.

So `L_max = ` length of the longest prefix of `t` that occurs as a substring of `t[2..|t|]`.

For each position `j ≥ 2` in `t`, `π[j]` is the length of the longest prefix of `t` that is a suffix of `t[1..j]`. Such a "prefix-as-suffix" is an occurrence of that prefix starting at position `j - π[j] + 1 ≥ 2`. So `max_j π[j]` is exactly the longest prefix of `t` that occurs in `t[2..|t|]`.

Therefore `L_max = π_max(t)`. Combined with the previous formula: `# new = |s'| − π_max`. ∎

## 8.4 Code (1-indexed)

```cpp
long long distinct_substrings_online(const string& input_raw) {
    // input_raw is a normal 0-indexed C++ string
    string s = " ";  // 1-indexed; s[1..len] = current string
    long long D = 0;
    
    for (char c : input_raw) {
        s += c;
        int len = (int)s.size() - 1;
        
        // build t = reverse of s[1..len], also 1-indexed
        string t = " ";
        for (int j = len; j >= 1; --j) t += s[j];
        
        vector<int> pi = prefix_function(t);
        int pi_max = 0;
        for (int j = 1; j <= len; ++j) pi_max = max(pi_max, pi[j]);
        
        D += (long long)len - pi_max;
    }
    return D;
}
```

Complexity: O(n²) total, O(n) per append.

## 8.5 Example

Append `'a', 'b', 'a'` to an initially empty `s`.

| step | s after append | t = rev(s) | π of t | π_max | len − π_max | D |
|------|----------------|------------|---------|-------|-------------|---|
| 1 | "a" | "a" | [_,0] | 0 | 1 | 1 |
| 2 | "ab" | "ba" | [_,0,0] | 0 | 2 | 3 |
| 3 | "aba" | "aba" | [_,0,0,1] | 1 | 2 | 5 |

Distinct non-empty substrings of "aba": {a, b, ab, ba, aba}. That's 5. ✓

## 8.6 Variants and Extensions

- **Prepending.** Symmetric: append to `rev(s)` instead.
- **Deleting from the end.** Maintain a different structure (e.g., suffix automaton) — harder.
- **O(n) total.** Achievable with a suffix automaton or a suffix tree; the prefix function approach is O(n²) but simpler.

For `n ≤ 5000`, this O(n²) approach is the right tool. For larger `n`, learn the suffix automaton.

## 8.7 Exercises

1. Run the algorithm on `"banana"`. The answer should be the count of distinct substrings (15: b, a, n, ba, an, na, ban, ana, nan, bana, anan, nana, banan, anana, banana).
2. Prove that `L_max` (in the proof above) is monotone: as we append more characters, can `L_max` jump down or up? By how much?
3. Sketch how to handle the "delete from front" operation. (Hard; you may need additional data structures.)

---

# Lesson 9: Application 4 — Periods, Borders, and String Compression

## 9.1 Goal
- Define periods. Prove the **border–period duality**.
- Prove: the smallest period of s is `n − π[n]`.
- Characterize compressibility: when does `s = t^q`?
- State and use the **Fine and Wilf theorem**.

## 9.2 Periods

A positive integer `p ≤ n` is a **period** of `s` if

> `s[i] = s[i + p]` for all valid `i`, i.e., for `1 ≤ i ≤ n − p`.

Equivalently: `s[1..n-p] = s[p+1..n]` (shift by p preserves overlap).

`n` itself is always a (trivial) period.

The **smallest period** of `s` is the minimum such `p`.

## 9.3 Border–Period Duality

> **Theorem 9.1.** `p` is a period of `s` iff `n − p` is a border length of `s`.

**Proof.** `p` is a period ⟺ `s[1..n-p] = s[p+1..n]`. Let `k = n − p`. The right side is the last `k` characters of `s`: `s[n-k+1..n] = s[p+1..n]`. So the condition becomes `s[1..k] = s[n-k+1..n]`, which is "k is a border length of s". ∎

This is a perfect bijection: periods 1, 2, ..., n correspond to border lengths n−1, n−2, ..., 0. Smaller period ↔ larger border.

## 9.4 The Smallest Period Formula

> **Theorem 9.2.** The smallest period of `s[1..n]` is `n − π[n]`.

**Proof.** `π[n]` is the **largest** proper border length. By duality, the largest border corresponds to the smallest period: `p_min = n − π[n]`. ∎

(Edge case: if `π[n] = 0`, the only border is empty, and the only period is `p = n` itself.)

### Code

```cpp
int smallest_period(const string& s) {
    int n = (int)s.size() - 1;
    vector<int> pi = prefix_function(s);
    return n - pi[n];
}
```

## 9.5 Compression: When is s = t^q?

We say `s` is "compressible to t" if `s = t · t · ... · t` (q copies, q ≥ 2). Such `t` must have `|t| < n` and `|t|` divides `n`.

> **Theorem 9.3.** `s = t^q` for some q ≥ 2 and `|t| < n` iff `p := n − π[n]` divides `n`. In that case, the shortest such `t` is `s[1..p]` and `q = n/p`.

**Proof of "if".** Let `p = n − π[n]`. Then `p` is a period of `s` (Theorem 9.1, 9.2). Suppose `p | n`. Let `t = s[1..p]`, `q = n/p`. We need `s = t^q`, i.e., `s[i] = t[((i-1) mod p) + 1]` for all `i ∈ [1, n]`.

By the period: `s[i] = s[i+p]` for `1 ≤ i ≤ n-p`. Iterating: `s[i] = s[i + kp]` for any `k` with `1 ≤ i + kp ≤ n`. So all positions in `s` congruent mod `p` have the same character. The first `p` characters thus determine `s`. ✓

**Proof of "only if".** Suppose `s = t^q` with `q ≥ 2`, `|t| < n`. Then `|t|` is a period of `s`. Let `p = n - π[n]` be the smallest period (Theorem 9.2). Then `p ≤ |t|`.

If `p < |t|`, we have two periods `p` and `|t|` with `p + |t| ≤ |t| + |t| = 2|t| ≤ n` (since `q ≥ 2`, `|t| ≤ n/2`). By Fine and Wilf (Theorem 9.4 below), `gcd(p, |t|)` is also a period. Since `p` is the smallest period, `gcd(p, |t|) ≥ p`, so `p | |t|`. Combined with `|t| | n`, we get `p | n`. ✓

If `p = |t|`, then `p | n` directly. ✓

Either way, `p | n`. ∎

### Code

```cpp
// Returns {compressible?, k}.
// If compressible, s = (s[1..k]) repeated n/k times.
// If not, k = n and s is "incompressible" by this method.
pair<bool, int> compress(const string& s) {
    int n = (int)s.size() - 1;
    vector<int> pi = prefix_function(s);
    int p = n - pi[n];
    if (p < n && n % p == 0) return {true, p};
    return {false, n};
}
```

## 9.6 The Fine and Wilf Theorem

> **Theorem 9.4 (Fine and Wilf).** If `s` has periods `p` and `q` with `p + q − gcd(p, q) ≤ |s|`, then `gcd(p, q)` is also a period of `s`.

**Sketch of proof.** Let `g = gcd(p, q)`. We want to show `s[i] = s[i + g]` for all `1 ≤ i ≤ n − g`.

Fix `i`. Since `g = gcd(p, q)`, by Bezout there exist integers `a, b` (not both zero) with `ap + bq = g`. We can choose `a > 0, b < 0` or vice versa (WLOG `a > 0, b < 0`).

Consider the sequence of positions: starting from `i`, repeatedly add `p` or subtract `q` while staying in `[1, n]`. The Fine-Wilf bound `p + q − g ≤ n` is exactly what's needed to ensure such a walk reaches `i + g` without leaving `[1, n]`. Each step preserves the character (by the periods). So `s[i] = s[i + g]`. ∎

(A clean rigorous proof uses induction on `g` or on a coloring argument — see Lothaire's "Combinatorics on Words".)

**Tightness.** The bound `p + q − gcd ≤ n` is sharp. Example: `s = "aabaa"` (n=5) has periods 3 and 4: 
- p=3: s[1]=a, s[4]=a; s[2]=a, s[5]=a; ✓.
- p=4: s[1]=a, s[5]=a; ✓.
Both work. gcd = 1. The Fine-Wilf bound: `3 + 4 − 1 = 6 > 5 = n`. So FW doesn't apply, and indeed gcd = 1 is NOT a period (since `s[1] = 'a' ≠ s[2] = 'a'` is fine but `s[2] = 'a' ≠ s[3] = 'b'`). The bound just barely fails to apply, and just barely the gcd isn't a period.

## 9.7 Examples

| s | π[n] | p = n − π[n] | divides n? | Compressed form |
|---|------|--------------|------------|-----------------|
| "abcabcabc" (n=9) | 6 | 3 | ✓ | "abc" × 3 |
| "abcab" (n=5) | 2 | 3 | ✗ | (no compression) |
| "aaaa" (n=4) | 3 | 1 | ✓ | "a" × 4 |
| "ababab" (n=6) | 4 | 2 | ✓ | "ab" × 3 |
| "abcabcd" (n=7) | 0 | 7 | trivially | (no compression) |
| "aabaa" (n=5) | 2 | 3 | ✗ | (no compression — and it has 2 periods 3,4 which Fine-Wilf can't combine) |

## 9.8 Exercises

1. Compute the smallest period of `"abcabcabcab"`. Is it compressible?
2. Prove: the smallest period `p` of `s` divides every period `q` of `s` satisfying `p + q ≤ n`. (Direct application of Fine-Wilf.)
3. Given an array of n integers (not characters), use the prefix function over the integer array to find the smallest period.
4. Codeforces 1326D2: minimum string operations relating to palindrome / period structure.

---

# Lesson 10: Application 5 — The KMP Automaton

## 10.1 Goal
Build a deterministic finite automaton (DFA) from the pattern that processes each text character in **O(1)** time (no while-loop fall-back), enabling pattern matching even when the text is given implicitly (e.g., by a recursion).

## 10.2 The Automaton

Define the DFA `M(p)`:
- **States**: 0, 1, ..., m (where m = |p|).
- **Initial state**: 0.
- **Accepting state**: m (signifies "we have just seen p as a substring").
- **Transition**: δ(j, c) = "the new state after reading character c while currently in state j".

**Interpretation**: state `j` means "the last j characters read form `p[1..j]`; we have matched a prefix of length j as a suffix of the text so far".

## 10.3 The Recurrence for δ

> **Recurrence.** For j ∈ {0, ..., m} and c ∈ Σ:
>
> - If `j < m` and `c = p[j + 1]`: δ(j, c) = j + 1.
> - Else if `j = 0`: δ(0, c) = 0.
> - Else (j > 0 and c ≠ p[j+1]): δ(j, c) = δ(π[j], c).

The recursion terminates because π[j] < j.

**Why?** We have just received character `c` while in state `j`. The new state is the largest `j'` such that `p[1..j']` is a suffix of `p[1..j] · c`.
- If `p[j + 1] = c`, then `p[1..j + 1]` itself is such a prefix, giving `j' = j + 1`.
- Otherwise, the next-largest prefix of `p` that is a suffix of `p[1..j]` has length `π[j]`. So we replay the "current state" as `π[j]` and process the same character `c`, giving δ(π[j], c).
- If `j = 0` and `c ≠ p[1]`, no progress: stay at 0.

## 10.4 Computing the Automaton in O(σ · m)

Iterate `j` from 0 upward. For each `j`, the recurrence uses δ(π[j], c) where π[j] < j, so it's already computed.

```cpp
// Assumes SIGMA is the alphabet size (e.g., 26 for lowercase letters)
// and characters are encoded as 0..SIGMA-1.
// Pattern is 1-indexed: pattern[1..m].
vector<array<int, SIGMA>> build_kmp_automaton(const string& pattern) {
    int m = (int)pattern.size() - 1;
    vector<int> pi = prefix_function(pattern);
    vector<array<int, SIGMA>> aut(m + 1);
    
    for (int j = 0; j <= m; ++j) {
        for (int c = 0; c < SIGMA; ++c) {
            if (j < m && c == pattern[j + 1] - 'a') {
                aut[j][c] = j + 1;
            } else if (j == 0) {
                aut[j][c] = 0;
            } else {
                aut[j][c] = aut[pi[j]][c];
            }
        }
    }
    return aut;
}
```

**Note on state m.** At state m we have just seen a full match. The automaton continues processing: aut[m][c] uses the recurrence with `j = m`. We can never have `m < m`, so we always fall back via `aut[pi[m]][c]`. This is what enables overlapping matches.

## 10.5 Using the Automaton

```cpp
long long count_with_automaton(const string& text,
                                const vector<array<int, SIGMA>>& aut,
                                int m) {
    int n = (int)text.size() - 1;
    int j = 0;
    long long cnt = 0;
    for (int i = 1; i <= n; ++i) {
        j = aut[j][text[i] - 'a'];
        if (j == m) ++cnt;
    }
    return cnt;
}
```

Per-character work: O(1). Total: O(n) for the matching phase, plus O(σ · m) preprocessing.

## 10.6 Comparison: Plain KMP vs Automaton

| | Plain KMP | Automaton |
|---|-----------|-----------|
| Preprocessing | O(m) | O(σ · m) |
| Per character | Amortized O(1) (with while-loop) | True O(1) (table lookup) |
| Space | O(m) | O(σ · m) |
| Best when | One text, normal use | Implicit text; multiple texts; need worst-case guarantees |

## 10.7 Use Case: Pattern Matching on Implicit Strings

Define a sequence of strings:
- `T_0 = "a"`,
- `T_k = T_{k-1} · 'b' · T_{k-1}` for `k ≥ 1`.

Then `|T_k| = 2^(k+1) − 1`. For `k = 30`, `|T_k| ≈ 2 · 10^9`. Materializing `T_30` is impossible.

But we can compute the number of occurrences of a pattern `p` in `T_k` using the automaton recursively.

Define `f(k, j) = (count_matches_during_T_k, final_state)` where we start processing `T_k` from state `j`. The recursion:

- **Base** `k = 0`: process the single character `'a'`. `f(0, j) = (1_{aut[j]['a'-'a'] == m}, aut[j]['a'-'a'])`.

- **Inductive** `k ≥ 1`: `T_k = T_{k-1} · 'b' · T_{k-1}`. Compose three actions:
  1. Process `T_{k-1}` from state `j`. Get count `c_1` and end state `j_1 = f_{state}(k-1, j)`.
  2. Process the single character `'b'` from `j_1`. Get count `c_2 = [aut[j_1]['b'-'a'] == m]`, end state `j_2 = aut[j_1]['b'-'a']`.
  3. Process `T_{k-1}` from state `j_2`. Get count `c_3` and end state `j_3 = f_{state}(k-1, j_2)`.
  
  Then `f(k, j) = (c_1 + c_2 + c_3, j_3)`.

Cache `f` for all (k, j) pairs. Total entries: O(k · m). Each computation: O(1). Total time: O(k · m).

```cpp
// Pseudocode; SIGMA, aut, pi must be set up beforehand.
unordered_map<long long, pair<long long, int>> memo;  // key = encode(k, j)

pair<long long, int> solve(int k, int j, int m, const vector<array<int, SIGMA>>& aut) {
    long long key = (long long)k * (m + 1) + j;
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    
    pair<long long, int> result;
    if (k == 0) {
        int j_new = aut[j]['a' - 'a'];
        result = { (j_new == m ? 1 : 0), j_new };
    } else {
        auto [c1, j1] = solve(k - 1, j, m, aut);
        int j2 = aut[j1]['b' - 'a'];
        long long c2 = (j2 == m) ? 1 : 0;
        auto [c3, j3] = solve(k - 1, j2, m, aut);
        result = { c1 + c2 + c3, j3 };
    }
    
    memo[key] = result;
    return result;
}
```

This is exactly the structure for problems like "count occurrences of pattern P in the k-th Thue-Morse string" or "in the k-th Fibonacci word".

## 10.8 Exercises

1. Build the automaton for `p = "aba"` (σ = 2 say). Print the transition table.
2. Verify: aut[0]['a'] = 1, aut[1]['b'] = 2, aut[2]['a'] = 3, aut[3]['a'] = 1 (the chain at full match).
3. Implement the recursive matcher for `T_k` defined above with `p = "aba"`. Compute the count for k = 5, k = 10.
4. Explain why the automaton's preprocessing depends on σ but the matching does not.

---

# Lesson 11: Advanced — Border Tree, Fine-Wilf, Z-Function, Connections

## 11.1 Goal
Bring out the underlying mathematical structure. Connect the prefix function to its siblings (Z-function, Aho-Corasick, suffix automaton) for context.

## 11.2 The Failure Tree (Border Tree)

Define the tree `T_π` on vertices `{0, 1, ..., n}` with edges `k → π[k]` for `k = 1, ..., n` (root is 0).

**Properties.**
1. The path from `i` to 0 spells out all border lengths of `s[1..i]` (Lesson 3).
2. Depth of `i` in `T_π` = number of (proper) borders of `s[1..i]` (including ε at the leaf-side).
3. Subtree rooted at `k` = `{i : k ∈ chain of i}` = positions where the prefix of length `k` "lives" in some border position.

**Applications.**
- Counting prefix occurrences (Lesson 7) is a subtree sum.
- DFS / parent-pointer structures answer "is `k` a border of `s[1..i]`?" queries efficiently with Euler tour.

**Picture for s = "abacaba" (π = [_, 0, 0, 1, 0, 1, 2, 3]):**

```
            0
           /|\
          / | \
         1  2  4
         |  
         3  
         |  
         5  (s[1..5] has border "aba" of length 3, but wait — π[5]=1; so 5's parent is 1)
```

Hmm let me redo this carefully. π[1] = 0, π[2] = 0, π[3] = 1, π[4] = 0, π[5] = 1, π[6] = 2, π[7] = 3.

Parents:
- 1 → 0
- 2 → 0
- 3 → 1
- 4 → 0
- 5 → 1
- 6 → 2
- 7 → 3

Tree:
```
                  0
                / | \
               1  2  4
              / \  \
             3   5  6
             |
             7
```

(Position 7 has π[7] = 3, so 7 → 3. Position 5 has π[5] = 1. Position 6 has π[6] = 2.)

The path from 7 to root is 7 → 3 → 1 → 0, giving border lengths 3, 1, 0 — exactly the borders of `s[1..7]` = "abacaba".

## 11.3 Aho-Corasick (Multi-Pattern Matching)

KMP handles one pattern. For matching several patterns simultaneously:

1. Build a **trie** of patterns.
2. For each trie node `u`, define its **failure link** `f(u) = ` deepest proper-suffix-of-the-string-spelled-by-u that is also a prefix of some pattern (i.e., a trie node).
3. Failure links form a tree (the **failure tree**), generalizing the π-tree of KMP.
4. Process the text by walking the trie, jumping along failure links on mismatches (just like KMP).

Complexity: O(total pattern length + |text| + output size).

This is the standard tool for "given many patterns, find all their occurrences in a text".

## 11.4 The Z-Function (Sibling Concept)

> `z[i] = ` length of the longest substring starting at position `i` that is also a prefix of `s`.

By convention `z[1] = n` (or sometimes 0; conventions vary).

Like π, `z` can be computed in O(n). It encodes related but distinct information:

| | π | Z |
|---|---|---|
| What it asks | "Longest prefix that equals a suffix here" | "Longest prefix that occurs starting here" |
| Local meaning | At position `i`, look backward | At position `i`, look forward |
| Typical use | KMP search | "Does the prefix appear starting at i?" |

You can convert one to the other in O(n), but they have different cleanliness for different problems.

## 11.5 Fine and Wilf — In Depth

> **Theorem (Fine and Wilf, 1965).** If `s` has periods `p` and `q` with `p + q − gcd(p, q) ≤ |s|`, then `gcd(p, q)` is also a period of `s`.

### Corollary (Structure of Periods)

The smallest period `p_min` of `s` divides every "small" period `q` (i.e., `q ≤ n − p_min + gcd(p_min, q)`).

### Corollary (Number of Small Periods is O(log n))

The number of distinct periods of `s` that are ≤ `n/2` is O(log n). This is because Fine-Wilf forces small periods to be multiples of `p_min`, and the chain of distinct periods that are not multiples of any smaller period is short.

### Tightness

For each pair (p, q), the Fine and Wilf bound is tight: there are strings of length `p + q − gcd(p, q) − 1` with both periods `p` and `q` but with no period `gcd(p, q)`. The classic examples come from **Sturmian words** and **Fibonacci words**.

## 11.6 Borders Are Almost Arithmetic Progressions

> **Theorem (Knuth-Morris-Pratt, classical).** The set of border lengths of any string can be partitioned into at most `⌈log₂(n+1)⌉` arithmetic progressions.

**Sketch.** A long border (length > n/2) of `s` forces a small period `p = n − |border|`. By Fine-Wilf, all such long borders share a common arithmetic structure. The long borders give one AP; the next "tier" (length ≤ n/2, > n/4) gives another; and so on. This is used in advanced periodicity algorithms (Main-Lorentz, Apostolico-Crochemore, ...).

## 11.7 Suffix Automaton (for Distinct Substrings)

For Lesson 8 (distinct substrings), the suffix automaton gives:
- O(n) construction.
- The number of distinct substrings is the sum of `len(u) − len(link(u))` over all states `u`, computable in O(n).

The KMP-based approach is O(n²). For `n ≤ 5000`, KMP is fine; for larger `n`, suffix automaton wins. But suffix automaton is harder to learn and implement correctly.

## 11.8 Suffix Array + LCP (Another Cornerstone)

Many string problems are most naturally attacked via the suffix array + LCP array. The suffix array sorts all `n` suffixes; the LCP array gives longest common prefixes between consecutive sorted suffixes.

Many distinct-substring, longest-common-substring, and pattern-matching variants are most cleanly solved by SA + LCP, with O(n) or O(n log n) construction.

The prefix function and suffix array are different tools for related problems. Master both.

## 11.9 The Berry-Ravindran Theorem (for the curious)

A deeper result about the period structure: there's a finite-state automaton of size O(n) that recognizes all powers of `s`. This is beyond CP but elegant.

## 11.10 Connections Summary

| Tool | Strength | Typical Problem |
|------|----------|-----------------|
| Prefix function (KMP) | Pattern matching, periods, prefixes-in-text | "Find all occurrences", "smallest period" |
| Z-function | "Does prefix occur starting at i?" | "Compute matching prefix at each position" |
| Aho-Corasick | Multi-pattern matching | "Find all dictionary words in text" |
| Suffix array + LCP | Sorted suffixes, LCP queries | "Longest repeated substring", "kth distinct substring" |
| Suffix automaton | Distinct substrings, substring queries | "Number of distinct substrings", "is X a substring of Y" |
| Suffix tree | Universal but heavy | Everything (but rare in CP) |
| Hashing | Probabilistic substring equality | "Compare arbitrary substrings", quick prototyping |

Each builds on or relates to ideas in the prefix function. KMP is the "Hello, world" of advanced string algorithms.

---

# Lesson 12: Pitfalls, Common Bugs, and Practice Problems

## 12.1 Common Bugs

### B1. Off-by-one between 0-indexed and 1-indexed

The most common bug. Pick one convention and stick to it. The 1-indexed prefix-function loop is:

```cpp
while (j > 0 && s[i] != s[j + 1]) j = pi[j];
```

The 0-indexed version is:

```cpp
while (j > 0 && s[i] != s[j]) j = pi[j - 1];
```

Mixing them produces silent bugs. If you started 1-indexed, don't sneak in a `s[j]` or `pi[j-1]`.

### B2. Forgetting `if (s[i] == s[j+1]) ++j;`

The while loop exits either when `j = 0` or when there's a match. If it exits on a match (the second condition), you must still increment `j`. Missing this check makes π underreport.

### B3. Wrong dummy character

For 1-indexed C++ via `string s = " " + raw_input`, the space character `' '` is the dummy. But if your input might contain spaces (very rare in CP), use `'\0'` or some other safe character. For pattern matching with concatenation `p + '#' + t`, the `#` must not appear in `p` or `t`.

### B4. π[1] not initialized to 0

`vector<int>(n+1, 0)` handles this. Don't manually set `pi[0]` to something weird.

### B5. Reading the wrong length

`s.size()` gives the full size including the dummy. If you wrote `s = " " + raw`, then `(int)s.size() - 1` is the "real" length n. Mistakes here cascade.

### B6. Failed sentinel check in pattern matching

In Method 1 (s = p#t), checking `pi[i] == m` for `i` in the t-section requires correct index arithmetic. The match position is `i − 2m` in `t` (1-indexed). Off-by-one here is common.

### B7. Counting matches with overlap

In Method 2, after `j == m`, we set `j ← pi_p[m]` to allow the next match to overlap. If you set `j ← 0`, you only find non-overlapping matches. Whether overlap is desired depends on the problem.

### B8. Reading the chain as positions, not lengths

`pi[i]` is the length of the longest proper border, not a position. Don't access `s[pi[i]]` thinking "that's the matched position".

### B9. Stack overflow in deep recursions

The automaton construction (Lesson 10) and some applications are iterative — be careful about deeply recursive solutions on large inputs.

### B10. Quadratic string concatenation in C++

`s = s + c` builds a new string each time. Prefer `s += c` (amortized linear) or `s.reserve(N)` upfront.

## 12.2 Performance Tips

- **Pre-allocate** vectors: `vector<int> pi(n + 1, 0);` not push_back.
- **Use `std::string += char`** in append-loops, not `+`.
- **Avoid recursion in hot loops** (recursion overhead is real).
- **For huge alphabets** (Unicode, integers), use `unordered_map<int, int>` for the automaton, or stick with KMP (which doesn't need the σ factor).
- **Cache locality**: π-chain accesses jump around. For massive inputs, the automaton is friendlier.

## 12.3 Mental Model Checks

Before writing code, ask yourself:
1. What is π[i] *semantically*? "Length of the longest proper border of `s[1..i]`."
2. Why is `s[j+1]` the right comparison? "Because `j` is the current matched length, and `j+1` is the next pattern character."
3. Why is `pi[j]` the right fall-back? "Because the next-longest border of `s[1..j]` is `π[j]` (π-chain theorem)."
4. Why does the algorithm terminate? "Because `pi[j] < j` for `j > 0`, so the while loop strictly decreases `j`."
5. Why is it O(n) total? "Because the potential `Φ = j` increases by at most 1 per outer iteration and decreases by the number of while iterations; total decrease ≤ total increase + initial − final ≤ n."

If you can answer these without thinking, the implementation flows naturally.

## 12.4 Curated Practice Problems

### Tier 1 — Warmup (do these first)

1. **Implement and test prefix_function.** Verify against the examples in Lesson 2.
2. **Codeforces 1326D2** — "Prefix-Suffix Palindrome (Hard version)".
3. **SPOJ NHAY** — "A Needle in the Haystack". Pure KMP.
4. **Implement smallest period** for an input string.

### Tier 2 — Standard

5. **Codeforces 432D** — "Prefixes and Suffixes". For each prefix that is also a suffix, count occurrences. Uses the failure tree.
6. **Codeforces 471D** — "MUH and Cube Walls". KMP on a difference array.
7. **Codeforces 25E** — "Test". Find the shortest superstring of three strings using prefix function overlaps.
8. **Codeforces 126B** — "Password". Find the longest border of `s` that also occurs in the middle.
9. **Codeforces 808G** — "Anthem of Berland". DP over KMP states with a pattern that has wildcards.

### Tier 3 — Harder

10. **Codeforces 526D** — "Om Nom and Necklace". Borders and periods on a more complex structure.
11. **Codeforces 30E** — "Tricky and Clever Password". Palindromes + KMP.
12. **Codeforces 825F** — "String Compression". Uses periods and DP.
13. **Codeforces 346B** — Variant on KMP transition DP.
14. **AtCoder ABC 285 Ex** — String period-related problem.

### Tier 4 — Advanced

15. **Aho-Corasick problems** (e.g., Codeforces 163E "e-Government").
16. **Distinct substring count for large n** — switch to suffix automaton.
17. **Codeforces Round on "fibonacci string" or "Thue-Morse"** — uses Lesson 10's recursive matching.

## 12.5 Roadmap After This Guide

Once you've internalized the prefix function and KMP:

1. **Z-function** (close relative; many problems are cleaner with Z).
2. **Aho-Corasick** (multi-pattern matching).
3. **Suffix array + LCP** (different paradigm, opens many more problems).
4. **Suffix automaton** (the workhorse for substring problems).
5. **Hashing** (probabilistic; useful prototyping tool).
6. **Manacher's algorithm** (palindromic substrings).
7. **Eertree / palindromic tree** (advanced palindrome work).
8. **Lyndon decomposition + Duval** (for ordering / rotation problems).

The mental discipline you built here — careful definitions, proved theorems, amortized analyses, 1-indexed precision — will carry over to every one of these.

## 12.6 Final Words

The prefix function is small but mighty. The recurrence is only six lines of code, but it encodes a deep theorem (π-chain) and supports half a dozen substantial applications. Master it by:

1. **Hand-tracing** at least three examples.
2. **Implementing** it without looking.
3. **Solving** at least 10 problems from the lists above.
4. **Explaining** to yourself why each line of the algorithm is correct.

Welcome to the world of advanced string algorithms.

---

*End of guide.*
