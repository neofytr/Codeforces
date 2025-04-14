#include <bits/stdc++.h>
using namespace std;

void printBinary(uint32_t number)
{
    for (int index = 31; index >= 0; index--)
    {
        if (number & (1 << index))
        {
            cout << 1;
        }
        else
        {
            cout << 0;
        }
    }

    cout << endl;
}

int main()
{
    // enumerating all submasks of a given mask

    // given a bitmask m, we want to efficiently iterate through all of it's submasks, that is,
    // masks s in which only bits that were included in mask m are set

    uint32_t m = 0b010101;
    uint32_t s = m;

    while (s > 0)
    {
        printBinary(s);
        s = (s - 1) & m;
    }

    // the above code visits all submasks of m, without repetition, and in descending order
    // proof:

    // at the start of nth iteration of the while loop, s is the nth largest submask of m
    // this is our induction hypothesis

    // base case
    // in the first iteration, we assume s > 0, so the loop occurs
    // since s = m at the loop start, its the largest submask of m
    // so the induction hypothesis is true for n = 1

    // induction step
    // assume that induction hypothesis is true for some k
    // we show that its also true for k + 1

    // at the start of kth iteration, s is the kth largest submask of m
    // we do (s - 1) & m, which creates a submask of m immediately less than s
    // thus induction hypothesis is true for k + 1
}