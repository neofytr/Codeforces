#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m; // n is the number of rows, m is the number of columns

    vector<vector<int>> matrix(n, vector<int>(m));            // n rows, m columns
    vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0)); // n + 1 rows, m + 1 columns all initialized to 0

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> matrix[i][j]; // ith row, jth column
        }
    }

    // calculate the prefix sum array for the matrix
    // prefix(i, j) is the sum of the elements of the matrix rectangle with diagonal edges (0, 0) and (i - 1, j - 1) for i, j >= 1
    // prefix(0, j) = 0 for 0 <= j < m + 1
    // prefix(i, 0) = 0 for 0 <= i < n + 1
    // i elements from row and j elements from column

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            prefix[i][j] = matrix[i - 1][j - 1] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }
}