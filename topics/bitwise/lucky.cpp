#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

// Function to generate a super lucky number from a bitset
// If bit is 1, we place 7, otherwise we place 4
long long generateNumber(long long bitset, int totalDigits)
{
    long long result = 0;
    for (int i = 0; i < totalDigits; i++)
    {
        // Start from most significant digit
        int position = totalDigits - i - 1;

        // Check if this position should be 7 or 4
        int digit = ((bitset >> position) & 1) ? 7 : 4;

        // Add to result
        result = result * 10 + digit;
    }
    return result;
}

// Function to count number of bits set to 1
int countSetBits(long long n)
{
    int count = 0;
    while (n)
    {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// Main function to solve the problem
long long findNextSuperLucky(long long n)
{
    // Start with the smallest possible super lucky number: 47
    if (n <= 47)
        return 47;

    // Find the number of digits in n
    int digits = 0;
    long long temp = n;
    while (temp > 0)
    {
        digits++;
        temp /= 10;
    }

    // Check super lucky numbers with the same number of digits as n
    // And if needed, with 2 more digits (if we can't find one with the same length)
    for (int length = digits; length <= digits + 2; length += 2)
    { // Must be even for equal 4s and 7s
        // Number of 4's and 7's should be equal
        int halfLength = length / 2;

        // We need to generate all bitsets with exactly halfLength bits set to 1
        // We'll iterate through possible bitsets and check which ones have exactly halfLength bits

        // Start with the smallest bitset that has exactly halfLength bits set
        // This is a number where the rightmost halfLength bits are set to 1
        long long bitset = (1LL << halfLength) - 1;

        std::vector<long long> candidates;

        // Generate all possible combinations
        while (bitset < (1LL << length))
        {
            long long superLuckyNumber = generateNumber(bitset, length);
            if (superLuckyNumber >= n)
            {
                candidates.push_back(superLuckyNumber);
            }

            // Generate the next bitset with exactly halfLength bits set
            // This is a complex bit manipulation algorithm (Gosper's hack)
            long long c = bitset & -bitset;
            long long r = bitset + c;
            bitset = (((r ^ bitset) >> 2) / c) | r;

            // If we've exceeded the length, break
            if (bitset >= (1LL << length))
                break;
        }

        // If we found candidates, return the smallest one
        if (!candidates.empty())
        {
            return *std::min_element(candidates.begin(), candidates.end());
        }
    }

    return -1; // Should never reach here
}

int main()
{
    long long n;
    std::cin >> n;

    long long result = findNextSuperLucky(n);
    std::cout << result << std::endl;

    return 0;
}