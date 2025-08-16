#include <bits/stdc++.h>
#include <vector>
using namespace std;

void subArraySum() {
    int n, x;
    cin >> n >> x;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // all the elements of the array are non-negative
    // we want to find the number of subarrays of arr that have their sum = x
    int cnt = 0;
    int left = 0, right = 0;
    int sum = 0;
    while (left < n) {
        while (right < n && sum < x) {
            sum += arr[right++];
        }

        if (sum == x) {
            // [left, right - 1] is one such subarray
            cnt++;
        }

        sum -= arr[left++];
    }

    cout << cnt << endl;
}

int main() {
    // iterating two monotonic pointers across an array to search for a pair of indices satisfying
    // some condition in linear time

    // In two pointers method, two pointers are used to iterate through the array values
    // Both pointers can move to one direction only, which ensures that the algorithm works efficiently

    // The two pointers method iterates two pointers across the array, to track the start and end of an interval
    // , or two values in a sorted array that we are currently checking
    // Both pointers are monotonic; meaning each pointer starts at one end of the array and only move in one direction

    // Subarray sum
    subArraySum();
}