#include <bits/stdc++.h>
using namespace std;

// iterating over all the submasks of a mask
// a submask of a mask is a binary number which can have only those bits ON that are also ON in the mask

int main()
{
    unsigned int mask;
    cin >> mask;

    unsigned int submask = mask;
    while (true)
    {
        // use submask
        submask = (submask - 1) & mask;
        if (!submask)
        {
            // use the submask 0
            break;
        }
    }

    return EXIT_SUCCESS;
}