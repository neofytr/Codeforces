#include <iostream>
#include <string>
#include <vector>

using namespace std;

string solve(int n)
{
    // If n is too small, we can't form a valid number
    if (n < 2)
        return "-1";

    // The number must be divisible by 66
    // First, let's try to construct the smallest possible number with 3s and 6s
    // Start with all 3s, as 3 is smaller than 6
    string num(n, '3');

    // Check all possibilities systematically
    for (int mask = 0; mask < (1 << n); mask++)
    {
        string current = num;

        // Apply the mask: replace digits with 6 where the bit is set
        for (int i = 0; i < n; i++)
        {
            if ((mask >> i) & 1)
            {
                current[n - 1 - i] = '6';
            }
        }

        // Skip leading zeros (though not possible with 3s and 6s)
        if (current[0] == '0')
            continue;

        // Convert to a number modulo 66 to check divisibility
        long long remainder = 0;
        for (char digit : current)
        {
            remainder = (remainder * 10 + (digit - '0')) % 66;
        }

        if (remainder == 0)
        {
            return current;
        }
    }

    return "-1";
}

// More efficient solution using properties of modular arithmetic
string solveEfficient(int n)
{
    // For large values of n, we need a more efficient approach
    // A number is divisible by 66 if it's divisible by both 2 and 33
    // Since all our digits are odd (3 and 6), the number is divisible by 2
    // only if the last digit is 6

    // First, try with all 3s and ending with 6
    string all3s(n - 1, '3');
    all3s += '6';

    // Check if this is divisible by 33
    long long remainder = 0;
    for (char digit : all3s)
    {
        remainder = (remainder * 10 + (digit - '0')) % 33;
    }

    if (remainder == 0)
    {
        return all3s;
    }

    // If not, we need to find a pattern that works
    // For larger n, we can use the property that repeating digits with period
    // equal to the multiplicative order of 10 modulo 33 will give us a number divisible by 33

    // Let's do a dynamic programming approach for the remainder when divided by 33
    vector<int> minMask(33, -1);
    vector<int> prevState(33, -1);
    vector<char> prevDigit(33, 0);

    minMask[0] = 0;

    for (int pos = 0; pos < n; pos++)
    {
        vector<int> newMinMask(33, -1);
        vector<int> newPrevState(33, -1);
        vector<char> newPrevDigit(33, 0);

        for (int remainder = 0; remainder < 33; remainder++)
        {
            if (minMask[remainder] == -1)
                continue;

            // Try adding '3'
            int newRemainder = (remainder * 10 + 3) % 33;
            if (newMinMask[newRemainder] == -1)
            {
                newMinMask[newRemainder] = minMask[remainder];
                newPrevState[newRemainder] = remainder;
                newPrevDigit[newRemainder] = '3';
            }

            // Try adding '6'
            newRemainder = (remainder * 10 + 6) % 33;
            if (newMinMask[newRemainder] == -1)
            {
                newMinMask[newRemainder] = minMask[remainder];
                newPrevState[newRemainder] = remainder;
                newPrevDigit[newRemainder] = '6';
            }
        }

        minMask = newMinMask;
        prevState = newPrevState;
        prevDigit = newPrevDigit;
    }

    // Check if we have a solution that is divisible by 33
    // Remember that the number must also be divisible by 2, so last digit must be 6
    if (minMask[0] != -1 && prevDigit[0] == '6')
    {
        // Reconstruct the number
        string result;
        int state = 0;

        for (int pos = 0; pos < n; pos++)
        {
            result = prevDigit[state] + result;
            state = prevState[state];
        }

        return result;
    }

    // Handle edge cases - we might need to force the last digit to be 6
    // and find a combination for the rest of the digits

    // Create a number with all 3s except for the last digit which is 6
    string number(n - 1, '3');
    number += '6';

    // Check if it's divisible by 33
    remainder = 0;
    for (char digit : number)
    {
        remainder = (remainder * 10 + (digit - '0')) % 33;
    }

    if (remainder == 0)
    {
        return number;
    }

    // Try setting more digits to 6, starting from right to left
    for (int i = n - 2; i >= 0; i--)
    {
        number[i] = '6';

        // Check if divisible by 33
        remainder = 0;
        for (char digit : number)
        {
            remainder = (remainder * 10 + (digit - '0')) % 33;
        }

        if (remainder == 0)
        {
            return number;
        }
    }

    return "-1";
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        // Use the efficient solution for larger values of n
        if (n <= 20)
        {
            cout << solve(n) << endl;
        }
        else
        {
            cout << solveEfficient(n) << endl;
        }
    }

    return 0;
}