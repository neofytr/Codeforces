#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

using ll = long long;
using vi = vector<int>;

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;

    int t1, t2, d;
    cin >> t1 >> t2 >> d;

    int a = max(t1, t2); // rightmost teacher
    int b = min(t1, t2); // leftmost teacher

    if (d < b)
    {
        // David is before the leftmost teacher
        // David will eventually be stuck at position 1
        // The teacher will reach him in (b - 1) moves
        cout << b - 1 << endl;
    }
    else if (d > a)
    {
        // David is after the rightmost teacher
        // David will eventually be stuck at position n
        // The teacher will reach him in (n - a) moves
        cout << n - a << endl;
    }
    else if (d >= b && d <= a)
    {
        // David is somewhere between the two teachers (or at one of their positions)

        // Proof by contradiction that David will be caught at the middle point (a+b)/2:
        // Let's define the middle point k = (a+b)/2
        int k = (a + b) / 2;

        // Assumption: David is not caught at point k
        // If this is true, then David must be caught either to the left or to the right of k

        // Case 1: Suppose David is caught to the left of k (at some position p where b ≤ p < k)
        // This would mean teacher b caught David at position p
        // For this to happen, David must have been at position p while teacher b was at position p+1
        // But if David plays optimally, he would have moved right in this situation
        // Since the rightmost teacher a is still far enough away (as a > k > p)
        // This contradicts our assumption that David was caught at position p < k

        // Case 2: Suppose David is caught to the right of k (at some position p where k < p ≤ a)
        // This would mean teacher a caught David at position p
        // For this to happen, David must have been at position p while teacher a was at position p-1
        // But if David plays optimally, he would have moved left in this situation
        // Since the leftmost teacher b is still far enough away (as b < k < p)
        // This contradicts our assumption that David was caught at position p > k

        // Since both cases lead to contradiction, our original assumption must be false
        // Therefore, David will be caught at the middle point k = (a+b)/2

        // The number of moves needed is the minimum of:
        // 1. How long it takes for teacher a to reach k: (a - k) moves
        // 2. How long it takes for teacher b to reach k: (k - b) moves
        int movesToCapture;

        // Special case: if David is already at the same position as one of the teachers
        if (d == a || d == b)
        {
            movesToCapture = 0;
        }
        else
        {
            movesToCapture = min(a - k, k - b);
        }

        cout << movesToCapture << endl;
    }
}

int main()
{
    FAST_IO;
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}