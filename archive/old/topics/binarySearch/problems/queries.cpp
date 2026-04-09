// https://codeforces.com/contest/600/problem/B
#include <bits/stdc++.h>
using namespace std;

inline int find(long long target, vector<long long> &A)
{
    // find the max index x in A such that A[x] <= target
    // return x + 1

    int left = -1;
    int right = A.size();

    while (right != left + 1)
    {
        int mid = left + (right - left) / 2;
        if (A[mid] <= target)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }

    return left + 1;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<long long> A(n);
    vector<long long> B(m);

    for (long long &val : A)
    {
        cin >> val;
    }

    sort(A.begin(), A.end());

    for (long long &val : B)
    {
        cin >> val;
    }

    for (int index = 0; index < m; index++)
    {
        cout << find(B[index], A) << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}