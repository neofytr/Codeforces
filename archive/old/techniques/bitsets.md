## Motivation Behind Bitsets

Consider this problem: There are \(N \leq 5000\) workers. Each worker is available during some days of this month (which has 30 days). For each worker, you are given a set of numbers, each from interval \([1,30]\), representing his/her availability. You need to assign an important project to two workers, but they will be able to work on the project only when they are both available. Find two workers that are best for the job — maximize the number of days when both these workers are available.

You can compute the intersection of two workers (two sets) in \(O(30)\) by using, for example, two pointers for two sorted sequences. Doing that for every pair of workers is \(O(N^2 \cdot 30)\), which is slightly too slow.

We can think about the availability of a worker as a binary string of length 30, which can be stored in a single `int`. With this representation, we can count the intersection size in \(O(1)\) by using `__builtin_popcount(x[i] & x[j])`. The complexity becomes \(O(N^2)\), which is fast enough.

What if we are given the availability for the whole year or, in general, for \(D\) days? We can handle \(D \leq 64\) in a single `unsigned long long`, but what about larger \(D\)?

We can split \(D\) days into convenient parts of size 64 and store the availability of a single worker in an array of \(D/64\) `unsigned long long`s. Then, the intersection can be computed in \(O(D/64)\) and the whole complexity is \(O(N^2 \cdot D/64)\).

### Introduction to Bitsets

A **bitset** is a data structure that efficiently represents a fixed-size sequence of bits. It provides a way to manipulate binary data at the bit level, making operations like AND, OR, and XOR extremely fast.

In C++, we have the `std::bitset` from the standard library, which provides an easy and efficient way to handle binary operations on fixed-size bit sequences.

### How Bitsets Work

A bitset internally stores bits in a compressed form, utilizing machine-level bitwise operations for efficiency. Instead of using a `vector<bool>`, which may have overhead due to per-element storage, `bitset` packs multiple boolean values into a single integer or an array of integers.

For example, a `bitset<30>` can store 30 availability days as a binary string where `1` means available and `0` means unavailable.

### Operations on Bitsets

#### 1. Declaration and Initialization
```cpp
#include <bitset>
#include <iostream>

int main() {
    std::bitset<30> worker1("101010101010101010101010101010");
    std::bitset<30> worker2("110011001100110011001100110011");
    std::cout << worker1 << std::endl;
    std::cout << worker2 << std::endl;
    return 0;
}
```

#### 2. AND, OR, XOR Operations
```cpp
std::bitset<30> intersection = worker1 & worker2; // Common available days
std::bitset<30> union_set = worker1 | worker2;    // Any available day
std::bitset<30> exclusive = worker1 ^ worker2;    // Days only one of them is available
```

#### 3. Counting Set Bits
```cpp
int common_days = (worker1 & worker2).count();
```
This operation is equivalent to `__builtin_popcount` and runs in \(O(1)\).

#### 4. Checking a Specific Bit
```cpp
if (worker1.test(5)) { // Is worker1 available on day 6? (0-based index)
    std::cout << "Worker 1 is available on day 6.";
}
```

#### 5. Setting and Resetting Bits
```cpp
worker1.set(2);   // Set day 3 as available
worker1.reset(4); // Set day 5 as unavailable
worker1.flip();   // Flip all bits
```

#### 6. Bitwise Shifting
```cpp
worker1 <<= 2; // Shift bits left by 2 positions
worker2 >>= 3; // Shift bits right by 3 positions
```

### Complexity of Operations

- **AND, OR, XOR, NOT operations**: \(O(1)\) when `bitset` is stored in a single integer, \(O(D/64)\) for larger bitsets.
- **Count Set Bits (`count()`)**: \(O(1)\) for small bitsets, \(O(D/64)\) otherwise.
- **Bitwise Shifts (`<<, >>`)**: \(O(1)\) for small bitsets, \(O(D/64)\) otherwise.
- **Access (`test(i)`, `set(i)`, `reset(i)`)**: \(O(1)\).
- The complexity of bitwise operations is O(size / 32) or O(size / 64), it depends on the architecture of your computer.

### Summary

Bitsets provide an efficient way to handle binary data and perform bitwise operations in constant time. They are particularly useful in problems involving large boolean arrays, where space and speed are crucial. In our problem of finding the best pair of workers, bitsets allow for quick set intersections, reducing computational complexity significantly compared to naive approaches.

