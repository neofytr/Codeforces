// https://cses.fi/problemset/task/1631

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<long long> arr(n);
    long long maximum = LLONG_MIN;
    for (long long &val : arr)
    {
        cin >> val;
        maximum = max(maximum, val);
    }

    /*

    There are n books, and Kotivalo and Justiina are going to read them all. For each book, you know the time it takes to read it.
    They both read each book from beginning to end, and they cannot read a book at the same time. What is the minimum total time required?

    */

    long long less = accumulate(arr.begin(), arr.end(), 0LL) - maximum;
    if (less <= maximum)
    {
        // if the largest book takes time >= all other books combined
        // the min time possible to read the books is at least 2 * max
        // and this time is achievable
        // give the longest book to person 1
        // until then, person 2 finishes all other books and possibly waits
        // then person 1 finishes the longest book, person 2 takes the longest book
        // and before or in the time person 2 finishes, person 1 finishes all the remaining

        // so min time is 2 * maximum
        cout << 2 * maximum << endl;
    }
    else
    {
        // the minimum time will be atleast less + maximum since a person has to finish all the books
        // we show that this time is achievable
        // sort arr in increasing order
        // person 2 starts with book n - 1
        // person 1 with n - 2

        // they both will continue successively reading books to their left
        // there won't be any clashes since the books are arranged in sorted order

        // person 2 will take a total time of sum
        // person 1 will be the first to reach book 0
        // when he finishes book 0, he wouldve taken time equal to less
        // since less > time for book n - 1 (max time)
        // person 2 won't still be on book n - 1, so person 1 can immediately jump
        // to book n - 1 and finish in time sum
        // both person take time sum with no overlap
        // and it will take at least sum time
        // so ans is just sum

        cout << less + maximum << endl;
    }

    return EXIT_SUCCESS;
}