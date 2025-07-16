#include <bits/stdc++.h>
using namespace std;

// this function prints numbers from 1 to n using recursion and backtracking
void linearOneBacktrack(int curr, int n)
{
    // base case: stop when curr < 1
    // in any recursive function, a base case is essential to prevent infinite recursion
    if (curr < 1)
        return;

    // recursive case: call function on a smaller input
    // here we go deeper into recursion first (stack builds up)
    linearOneBacktrack(curr - 1, n);

    // work is done after the recursive call → this is called post-order recursion
    // such style is useful when you want to process results *after* all deeper calls are done
    cout << curr << endl;

    // general concept:
    // - recursive calls go deeper and are stored on call stack
    // - on returning (unwinding), we perform operations in reverse order
}

// prints numbers from curr to n in increasing order using recursion
void linearOne(int curr, int n)
{
    // base case: stop when curr > n
    if (curr > n)
        return;

    // work is done before the recursive call → this is pre-order recursion
    // useful when you want to process values in the original order
    cout << curr << endl;

    // recursive case: progress toward base case
    linearOne(curr + 1, n);

    // general concept:
    // - work is done during the forward phase (going deeper)
    // - nothing happens during return (stack unwinds quietly)
}

// prints numbers from curr to n in decreasing order using recursion
void linearTwo(int curr, int n)
{
    // base case: stop when curr > n
    if (curr > n)
        return;

    // recursive case happens first
    linearTwo(curr + 1, n);

    // work is done after recursion → post-order/backtracking style
    cout << curr << endl;

    // this prints in reverse because all deeper calls are made first,
    // and only then we start printing while returning
}

int recursionSum(int curr, int n)
{
    if (curr > n)
        return 0;

    return curr + recursionSum(curr + 1, n);
}

int main()
{
    int n;
    cin >> n;

    // guard clause: ensure valid input
    if (n < 1)
        return EXIT_FAILURE;

    // recursion to print numbers from 1 to n (in increasing order)
    linearOne(1, n); // forward recursion → work before recursive call
    cout << endl;

    // recursion to print numbers from n to 1 (in decreasing order)
    linearTwo(1, n); // backtracking → work after recursive call

    cout << endl;
    // another function showing backtracking from n to 1
    linearOneBacktrack(n, n);

    cout << endl;
    cout << recursionSum(1, n) << endl;
    return EXIT_SUCCESS;
}
