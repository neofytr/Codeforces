---
# Subsequence Coverage Method

This document explains an efficient method to determine whether **all possible sequences** (up to a given length) that can be formed from a subset of symbols occur as **subsequences** in a given sequence.

## 📌 Problem Statement

Given:

* A sequence `x` composed of symbols from a universe `S`
* A subset `s ⊆ S`
* An integer `k`

We want to check:

> Do **all possible sequences of length `≤ k`** that can be formed using only symbols from `s` appear as subsequences of `x`?

## ✅ Key Insight

All such sequences **are subsequences of `x`** **if and only if** the following condition holds:

> There exist **at least `k` full "sets"** of `s` in `x`, **in order**, each containing **at least one occurrence of every symbol in `s`**.

This ensures that we can **greedily construct** any sequence of length up to `k` by selecting one symbol from each set, preserving relative order (as required by subsequences).

## 📘 Terminology

* A **subsequence** of a sequence is obtained by deleting some (possibly zero) elements **without changing the order** of the remaining elements.
* A **full set** of `s` in `x` is a contiguous run (not necessarily continuous) that contains at least one occurrence of **every** symbol in `s`.

## 🧠 Example

Let `x = abacbabc`, `s = {a, b, c}`, and `k = 2`.

We scan `x` left to right and collect full sets of `s`:

1. First set: `a, b, c` → formed from `a (0), b (1), c (4)`
2. Second set: `a, b, c` → from `a (5), b (6), c (7)`

We have 2 full sets ⇒ **All sequences of length ≤ 2** over `{a, b, c}` can be constructed as subsequences of `x`.

## ⚠️ Why It Works

If we have `k` such full sets:

* Pick one symbol from each set → gives any sequence of length `k`
* Picking fewer sets gives sequences of length < `k`
* Since each set contains all symbols from `s`, **any combination** is possible.

## 💡 When to Use This

* You need to check subsequence coverage without brute-forcing all combinations (which is exponential).
* Your alphabet size (`|s|`) and target length (`k`) are reasonably small (e.g., ≤ 26).
* Efficient solution is needed, especially under time/space constraints.

---


