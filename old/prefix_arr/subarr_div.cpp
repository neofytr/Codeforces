#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n; // Input the array size

    vector<long long> arr(n + 1, 0); // Create array of size n+1 (1-indexed for convenience)

    // Read the array elements
    for (int index = 1; index <= n; index++)
    {
        cin >> arr[index];
    }

    long long curr_sum = 0; // Running sum of array elements
    long long count = 0;    // Counter for subarrays with sum divisible by n

    // Map to store frequency of prefix sum remainders
    // key: remainder when prefix sum is divided by n
    // value: count of how many times this remainder has been seen
    map<long long, int> prefix;
    prefix[0] = 1; // Initialize target 0 with 1 since any target 0 has one subarray (from start till that index) by default which doesn't need any other index to form a valid subarray

    for (int index = 1; index <= n; index++)
    {
        // Update running sum with current element
        curr_sum += arr[index];

        // Calculate the remainder when current prefix sum is divided by n
        // The formula (x % n + n) % n handles negative numbers correctly
        long long target = (curr_sum % n + n) % n;

        // If we've seen this remainder before, it means there exist earlier
        // prefix sums that, when subtracted from current sum, give a result divisible by n
        // For any prefix sums P1 and P2 where P1 % n = P2 % n:
        // (P2 - P1) % n = 0, meaning (P2 - P1) is divisible by n
        if (prefix.count(target))
        {
            // Add the frequency of this remainder to our count
            // Each previous occurrence can form a valid subarray with the current position
            count += prefix[target];
            prefix[target]++; // Increment the frequency of this remainder
        }
        else
        {
            // First time seeing this remainder
            prefix[target] = 1;
        }
    }

    // Output the total count of subarrays with sum divisible by n
    cout << count << endl;
}