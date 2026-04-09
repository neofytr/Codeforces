#include <bits/stdc++.h>
using namespace std;

int main()
{
    // input n (the target number for the equation x^3 - y^3 = n)
    uint64_t n;
    cin >> n;

    // if n is 0, we know x = 1 and y = 1 is a solution (1^3 - 1^3 = 0)
    if (n == 0)
    {
        cout << "1 1" << endl;
        return EXIT_SUCCESS;
    }

    // if n is 1, there is no solution (x^3 - y^3 = 1 has no integral solutions for x and y)
    if (n == 1)
    {
        cout << -1 << endl;
        return EXIT_SUCCESS;
    }

    // iterate over possible values for delta (small value that helps in constructing the solution)
    for (uint64_t delta = 1; delta * delta * delta <= n; delta++)
    {
        // skip delta if it doesn't divide n evenly
        if (n % delta != 0)
            continue;

        // m is the quotient of n and delta, used for discriminant computation
        uint64_t m = n / delta;

        // calculate the discriminant (12 * m - 3 * delta^2)
        uint64_t discriminant = 12 * m - 3 * delta * delta;

        // compute the square root of the discriminant
        uint64_t sqrt_discriminant = sqrt(discriminant);

        // if the discriminant is not a perfect square, skip this delta
        if (sqrt_discriminant * sqrt_discriminant != discriminant)
            continue;

        // compute the numerator part for the solution calculation
        int64_t numerator = -3LL * delta + sqrt_discriminant;

        // skip if numerator is negative or cannot be divided by 6 evenly
        if (numerator < 0 || numerator % 6 != 0)
            continue;

        // calculate y (the second part of the solution) using the formula
        uint64_t y = numerator / 6;

        // calculate x (the first part of the solution)
        uint64_t x = y + delta;

        // check if the solution satisfies the equation x^3 - y^3 = n
        if (x > 0 && y >= 0 && x * x * x - y * y * y == n)
        {
            // if valid solution, output it and exit
            cout << x << " " << y << endl;
            return EXIT_SUCCESS;
        }
    }

    // if no solution is found, output -1
    cout << -1 << endl;
    return EXIT_SUCCESS;
}
