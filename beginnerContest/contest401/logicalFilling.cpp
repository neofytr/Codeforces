#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    string answer(n, '?');

    long long num_o = 0;
    long long definite_qs = 0;

    for (long long i = 0; i < n; ++i)
    {
        if (s[i] == 'o')
            num_o++;
        else if (s[i] == '?')
        {
            bool left_is_o = (i > 0 && s[i - 1] == 'o');
            bool right_is_o = (i < n - 1 && s[i + 1] == 'o');
            if (!left_is_o && !right_is_o)
                definite_qs++;
        }
    }

    for (long long i = 0; i < n; ++i)
    {
        if (s[i] == '.')
            answer[i] = '.';
        else if (s[i] == 'o')
            answer[i] = 'o';
        else
        {
            bool neighbor_is_o = (i > 0 && s[i - 1] == 'o') || (i < n - 1 && s[i + 1] == 'o');
            if (neighbor_is_o)
                answer[i] = '.';
            else if (k - num_o == definite_qs)
                answer[i] = 'o';
            else
                answer[i] = '?'; // could be 'o' or '.'
        }
    }

    cout << answer << '\n';
}
