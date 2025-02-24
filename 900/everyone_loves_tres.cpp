#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Check if a number represented as a string is divisible by both 33 and 66
bool isDivisibleBy33And66(const string &num)
{
    // For divisibility by 33:
    // A number is divisible by 33 if it's divisible by both 3 and 11

    // Check divisibility by 3: sum of digits is divisible by 3
    int digitSum = 0;
    for (char digit : num)
    {
        digitSum += (digit - '0');
    }

    // Check divisibility by 11: alternating sum is divisible by 11
    int alternatingSum = 0;
    for (int i = 0; i < num.length(); i++)
    {
        if (i % 2 == 0)
        {
            alternatingSum += (num[i] - '0');
        }
        else
        {
            alternatingSum -= (num[i] - '0');
        }
    }

    // For divisibility by 66:
    // A number is divisible by 66 if it's divisible by both 6 and 11
    // For divisibility by 6: number must be divisible by both 2 and 3
    // Number is divisible by 2 if last digit is even
    bool isDivisibleBy2 = (num.back() == '6'); // Only 6 is even among 3 and 6

    // Number is divisible by 33 if it's divisible by both 3 and 11
    // Number is divisible by 66 if it's divisible by both 6 and 11
    // Thus, we need divisibility by 3, 11, and 2
    return (digitSum % 3 == 0) && (alternatingSum % 11 == 0) && isDivisibleBy2;
}

// Generate the smallest number of length n with only 3s and 6s
// that is divisible by both 33 and 66
string findSmallestValidNumber(int n)
{
    // For n = 1, only single digit is possible
    if (n == 1)
    {
        // 6 is divisible by 6, but not by 33
        return "-1";
    }

    // For n = 2, check "33", "36", "63", "66"
    if (n == 2)
    {
        string candidates[] = {"33", "36", "63", "66"};
        for (const string &num : candidates)
        {
            if (isDivisibleBy33And66(num))
            {
                return num;
            }
        }
        return "-1";
    }

    // For n >= 3, we need to systematically check
    // Start with smallest possible: all 3s except the last digit (which is 6 to ensure divisibility by 2)
    string smallestNum(n, '3');
    smallestNum[n - 1] = '6'; // Last digit must be 6 for divisibility by 2

    // If this number is already divisible by 33 and 66, return it
    if (isDivisibleBy33And66(smallestNum))
    {
        return smallestNum;
    }

    // Otherwise, we need to systematically modify digits from right to left
    // to make it divisible by 33 and 66
    vector<string> candidates;

    // Try replacing digits with 6 (except the last one which is already 6)
    for (int i = 0; i < n - 1; i++)
    {
        string candidate = smallestNum;
        candidate[i] = '6';
        if (isDivisibleBy33And66(candidate))
        {
            candidates.push_back(candidate);
        }
    }

    // Try replacing more digits if needed
    int numDigitsToChange = 2;
    while (candidates.empty() && numDigitsToChange < n)
    {
        // Generate all combinations with numDigitsToChange digits changed to 6
        vector<int> positions(n - 1, 0);
        for (int i = 0; i < numDigitsToChange; i++)
        {
            positions[i] = 1; // Mark positions to change
        }

        // Sort to get canonical order
        sort(positions.begin(), positions.end());

        do
        {
            string candidate = smallestNum;
            for (int i = 0; i < n - 1; i++)
            {
                if (positions[i] == 1)
                {
                    candidate[i] = '6';
                }
            }

            if (isDivisibleBy33And66(candidate))
            {
                candidates.push_back(candidate);
            }
        } while (next_permutation(positions.begin(), positions.end()));

        numDigitsToChange++;
    }

    // If no candidates found
    if (candidates.empty())
    {
        return "-1";
    }

    // Return the smallest valid number
    sort(candidates.begin(), candidates.end());
    return candidates[0];
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        cout << findSmallestValidNumber(n) << endl;
    }

    return 0;
}