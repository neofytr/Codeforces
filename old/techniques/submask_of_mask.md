# To iterate through all the submasks of a mask

### **Meaning of a Submask of a Mask**
In bitwise operations, a **submask** of a **mask** is a number that is formed by turning **some subset of the `1` bits** in the mask to `0`, while keeping the rest unchanged. 0 is a submask of all masks.

#### **Definition**
A number `S` is called a **submask** of `M` if:
\[
S \subseteq M
\]
which means that **all bits set in `S` are also set in `M`**.

Mathematically, this is represented as:
\[
(S \& M) = S
\]
which means that applying a bitwise **AND** between `S` and `M` gives back `S`.

```c

// iterating over all submasks (except zero)

size_t mask;
size_t submask = mask;

// generates all submasks of mask, in descending order
while(submask)
{
    // use submask
    submask = (submask - 1) & mask;
}
// submask is now zero
// consider the 0 submask case outside

```

# Proof

We have this algorithm:
```python
submask = mask
while submask:
    # use current submask
    submask = (submask - 1) & mask
```

We need to prove three things:
1. It only generates valid submasks
2. It generates all possible submasks
3. It never generates the same submask twice

Let's start with what makes a submask "valid". A submask is valid if it only has 1s in positions where the original mask has 1s. For example, if our mask is 1101, then 1001 is a valid submask, but 1010 is not (because it has a 1 in a position where the mask has 0).

Now, let's look at each part of the proof:

Part 1: Proving it only generates valid submasks
Think about what happens when we do (submask - 1) & mask:
- The & mask operation acts like a filter. It only keeps 1s that appear in the original mask.
- So if we get any number after this operation, it must be a valid submask.

For example, with mask = 1101:
```
Let's say submask = 1101
submask - 1     = 1100
(1100) & (1101) = 1100  ✓ valid submask
```

Part 2: Proving it generates all possible submasks
This is the trickier part. Let's prove it by contradiction:

Imagine we missed a submask. Let's call it X. There must be a submask Y that our algorithm generated that's just bigger than X. Let's see why this can't happen:

1. When we subtract 1 from Y, we flip bits starting from the rightmost 1:
   ```
   Y       = 1100
   Y - 1   = 1011
   ```

2. When we do & mask, we keep only the bits that mask allows:
   ```
   mask    = 1101
   Y - 1   = 1011
   result  = 1001
   ```

3. This means our algorithm would have generated the number between Y and X.
4. But we said Y was the next bigger number after X!
5. This is a contradiction, so we couldn't have missed any submasks.

Part 3: Proving each submask appears only once
This is the easiest part. Since each operation (submask - 1) & mask gives us a smaller number, and we stop when we reach 0, we can never get the same number twice.

Let's see a complete example with mask = 1101:
```
Start: 1101 (original mask)
Step 1: 1100 (flip rightmost 1 and mask)
Step 2: 1001 (flip two 1s and mask)
Step 3: 1000 (flip rightmost 1 and mask)
Step 4: 0101 (flip three 1s and mask)
Step 5: 0100 (flip rightmost 1 and mask)
Step 6: 0001 (flip two 1s and mask)
Step 7: 0000 (we're done)
```

You can verify that:
1. Each number only has 1s where the mask has 1s
2. We didn't miss any possible combinations
3. We never got the same number twice
4. Each step made the number smaller


See: https://cp-algorithms.com/algebra/all-submasks.html
