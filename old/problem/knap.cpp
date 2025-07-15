#include <bits/stdc++.h>
using namespace std;

int max_sum = INT_MIN;

int knapsack(int i, int w, vector<int> &weights, vector<int> &values)
{
    // i is the number of items left to consider
    // w is the remaining weight capacity of the knapsack
    // weights and values store the weight and value of each item

    // base case (if there are no more items (i == 0) or no more capacity (w == 0)), we cannot take
    // anything, so we return 0

    if (!i || !w)
    {
        return 0;
    }

    // if the current item's weight is more than the remaining weight, skip the item and move to the next

    if (weights[i - 1] > w)
    {
        return knapsack(i - 1, w, weights, values);
    }

    // otherwise, we have two choices
    // take the item -> add it's value and reduce weight
    // skip the item -> ignore it and move to the next
    // we return the max of both cases since we want the max value

    return max(knapsack(i - 1, w, weights, values), values[i - 1] + knapsack(i - 1, w - weights[i - 1], weights, values));
}

int main()
{
    int n, w;
    cin >> n >> w;

    vector<int> weights(n);
    vector<int> values(n);

    for (int index = 0; index < n; index++)
    {
        cin >> weights[index] >> values[index];
    }

    vector<int> used_index;

    cout << knapsack(n, w, weights, values) << endl;

    return 0;
}
