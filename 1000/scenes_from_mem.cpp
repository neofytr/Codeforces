#include <bits/stdc++.h>
using namespace std;

/*

Let's show that if a number has three digits, you can always remove at least one from it to get a number that is not prime. This can be proved by a simple brute-force search of all numbers with three digits, but we'll try to do it without a brute-force search.

In fact, if a number contains the digits '1', '4', '6', '8' or '9', then that one digit is the answer, because 1
, 4
, 6
, 8
 and 9
 are not prime numbers.

Now let's see what happens if the number doesn't have those digits. Then, if the number has two identical digits, we have found an answer of size two — the number of two identical digits (22
, 33
, 55
, or 77
) is divisible by 11
. Also, if the digits 2
 or 5
 are not at the beginning of the number, we again have found an answer of size two — the number of two digits ending in 2
 or 5
 is not prime.

If none of the above cases worked, then we find that a three-digit number has one of the following values: 237
, 273
, 537
, 573
. It is not difficult to see that these numbers have two digits, which form a number, that is divisible by three.

Thus, the maximum answer is two, that is, you can leave no more than two digits in the number. You can find these digits by considering the above cases, or you can just try.

It can be shown that such a brute-force solution will work for O(k)
.

Asymptotics: O(k)
 per test case.

*/

bool isPrime(long long n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (long long i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

void solve()
{
    int k;
    string num;
    cin >> k >> num;

    for (int i = 0; i < k; i++)
    {
        int digit = num[i] - '0';
        if (digit == 1 || digit == 4 || digit == 6 || digit == 8 || digit == 9)
        {
            cout << 1 << endl;
            cout << digit << endl;
            return;
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            int first = num[i] - '0';
            int second = num[j] - '0';
            int twoDigit = first * 10 + second;

            if (!isPrime(twoDigit))
            {
                cout << 2 << endl;
                cout << twoDigit << endl;
                return;
            }
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            for (int l = j + 1; l < k; l++)
            {
                int first = num[i] - '0';
                int second = num[j] - '0';
                int third = num[l] - '0';
                int threeDigit = first * 100 + second * 10 + third;

                if (!isPrime(threeDigit))
                {
                    cout << 3 << endl;
                    cout << threeDigit << endl;
                    return;
                }
            }
        }
    }

    cout << "No solution found!" << endl;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}