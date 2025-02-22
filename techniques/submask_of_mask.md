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
    submask &= (mask - 1);
}

// submask is now zero
// consider the 0 submask case outside

```

See: https://cp-algorithms.com/algebra/all-submasks.html
