#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("breedflip.in", "r", stdin);
    freopen("breedflip.out", "w", stdout);

    int n;
    cin >> n;

    string A, B;
    cin >> A >> B;

    int count = 0;
    int left = 0;
    int right = 0;

    while (true)
    {
        while (left < n && A[left] == B[left])
        {
            left++;
        }

        if (left >= n)
        {
            break;
        }

        right = left;
        while (right < n && A[right] != B[right])
        {
            right++;
        }

        count++;
        if (right >= n)
        {
            break;
        }

        left = right;
    }

    cout << count << '\n';
    return 0;
}
