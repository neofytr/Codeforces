#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<long long> stick(n);
    for (auto &x : stick)
        cin >> x;

    sort(stick.begin(), stick.end());

    // the min can't come before the smallest stick and after the biggest stick
    // the min can't also come between two sticks
    // suppose the minimum min is such that
    // s1 < min < s2 where s1 and s2 are two stick lengths
    // if there are more sticks on the left side of min than on the right side,
    // min will decrease when we move it to the left, which is impossible
    // if there are more sticks on the right side of min than on the left side,
    // min will decrease when we move it to the right, which is impossible
    // if there are equal number of elements on it's either side, then any s1 <= r <= s2
    // can be the minimum, which is impossible
    // this is a contradiction; hence minimum can only be on the sticks and not in between them

    long long init = 0;
    for (long long val : stick)
    {
        init += abs(val - stick[0]);
    }

    long long minimum = init;
    for (int index = 1; index < n; index++)
    {
        // shift common length to stick[index]
        init += index * (stick[index] - stick[index - 1]);
        init -= (n - index) * (stick[index] - stick[index - 1]);

        minimum = min(init, minimum);
    }

    cout << minimum << '\n';
    return 0;
}
