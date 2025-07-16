#include <bits/stdc++.h>
using namespace std;

// prints numbers from 'curr' to 'n' in increasing order
void linearOne(int curr, int n)
{
    if (curr > n)
        return;

    cout << curr << endl;

    // recursive call happens after printing,
    // so the numbers are printed in the order of the calls
    linearOne(curr + 1, n);
}

// prints numbers from 'curr' to 'n' in decreasing order
void linearTwo(int curr, int n)
{
    if (curr > n)
        return;

    // recursive call happens before printing,
    // so the numbers are printed in reverse order of the calls
    linearTwo(curr + 1, n);
    cout << curr << endl;
}

int main()
{
    int n;
    cin >> n;

    // if the input number is less than 1, exit the program with failure
    if (n < 1)
        return EXIT_FAILURE;

    // print numbers from 1 to n using recursion
    linearOne(1, n);

    // print numbers from n to 1 using recursion
    linearTwo(1, n);
}
