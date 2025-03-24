#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Optimization: Disable synchronization between C and C++ standard streams
    // This speeds up cin/cout operations significantly
    ios::sync_with_stdio(false);
    cin.tie(nullptr);  // Unties cin from cout to prevent flushing
    cout.tie(nullptr); // Unties cout to prevent automatic flushing

    // Read input:
    // n = size of the array
    // x = target sum we want to find
    int n, x;
    cin >> n >> x;

    // Create array of size n+1 (1-indexed for easier reading)
    // We start from index 1 rather than 0
    vector<long long> arr(n + 1, 0);
    for (int index = 1; index <= n; index++)
    {
        cin >> arr[index];
    }

    // Map to store frequency of each prefix sum encountered
    // Key: prefix sum value
    // Value: number of times this prefix sum has occurred
    map<long long, int> prefix;

    // Variables to track:
    // curr_sum = running sum of elements processed so far
    // count = total number of subarrays with sum equal to x
    long long curr_sum = 0;
    long long count = 0;

    // Initialize map with a prefix sum of 0 occurring once
    // This handles the case where the entire subarray from beginning sums to x
    prefix[0] = 1;

    // Iterate through the array
    for (int index = 1; index <= n; index++)
    {
        // Add current element to running sum
        curr_sum += arr[index];

        // For a subarray to have sum x, we need a previous prefix sum of (curr_sum - x)
        // If such a prefix sum exists in our map, add its frequency to our count
        // This counts all subarrays ending at current position with sum x
        count += prefix[curr_sum - x];

        // Increment the frequency of current prefix sum
        prefix[curr_sum]++;
    }

    // Print the result
    cout << count << endl;

    return EXIT_SUCCESS;
}