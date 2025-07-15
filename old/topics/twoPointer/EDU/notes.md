# Two Pointers Method

The **two pointers technique** is useful for solving problems involving segments or subarrays efficiently. To use this method, two main conditions must be satisfied:

---

## ✅ First Condition (Left Side Condition)

To apply the two pointers technique, we must ensure:

### At least one of the following is true:

1. If $\ell..r$ is "good" (i.e. satisfies the condition), then:
   $\ell'..r \text{ is also good for } \ell' \geq \ell$

   * Example: $\sum a[\ell..r] \leq S$

2. If $\ell..r$ is "good", then:
   $\ell..r' \text{ is also good for } r' \leq r$

   * Example: $\sum a[\ell..r] \geq S$

This ensures we can move one pointer without breaking the property of the segment.

---

## ✅ Second Condition (Right Side Condition)

Once the above holds, we can use the following general **pseudocode pattern**:

```cpp
for (r = 0; r < n; ++r) {
	add(a[r]);
	while (!isGood()) {
		remove(a[l]);
		l++;
	}
	// segment [l, r] is good here
}
```

This efficiently finds all valid segments \[l, r] by extending `r` and shifting `l` only when necessary.

---

## 📌 Patterns for Segment Pseudocode

### 1. Segments Starting from Left

* We extend the segment by increasing `r`.
* Useful when we want to find all right endpoints for each fixed left endpoint.

```cpp
for (l = 0; l < n; ++l) {
	while (r < n && isGood()) {
		add(a[r]);
		r++;
	}
	// segment [l, r-1] is good here
	remove(a[l]);
}
```

### 2. Segments Ending at Right

* We extend the segment by increasing `l`.
* Useful when we want to find all left endpoints for each fixed right endpoint.

```cpp
for (r = 0; r < n; ++r) {
	add(a[r]);
	while (!isGood()) {
		remove(a[l]);
		l++;
	}
	// segment [l, r] is good here
}
```

---

## 💡 Tip

Always define:

* `add(x)`: what happens when we include an element to the segment
* `remove(x)`: what happens when we exclude an element from the segment
* `isGood()`: whether the current segment satisfies the required condition

---

With this structure and these conditions, you'll be able to apply the two pointers method to a wide variety of problems efficiently!
