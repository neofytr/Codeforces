#include <bits/stdc++.h>
using namespace std;

// Function to check if a number is prime
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

    // Try to find a single digit that is not prime
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

    // Try to find a two-digit number that is not prime
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

    // Try three digits if needed
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

    // We're guaranteed to find a solution with less than k digits
    // If we reach here, there might be an issue with our implementation
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