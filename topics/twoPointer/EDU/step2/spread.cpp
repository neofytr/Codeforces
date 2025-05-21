#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    stack<long long> left_stack, left_min, left_max;
    stack<long long> right_stack, right_min, right_max;

    int left = 0, right = 0;
    long long count = 0;

    while (left < n)
    {
        while (right < n)
        {
            long long elt = arr[right];
            right_stack.push(elt);

            if (!right_max.empty())
                right_max.push(max(elt, right_max.top()));
            else
                right_max.push(elt);

            if (!right_min.empty())
                right_min.push(min(elt, right_min.top()));
            else
                right_min.push(elt);

            long long totmax;
            long long totmin;

            if (!left_min.empty())
                totmin = min(left_min.top(), right_min.top());
            else
                totmin = right_min.top();

            if (!left_max.empty())
                totmax = max(left_max.top(), right_max.top());
            else
                totmax = right_max.top();

            if (totmax - totmin > k)
            {
                right_stack.pop();
                right_min.pop();
                right_max.pop();
                break;
            }

            right++;
        }

        count += (right - left);

        if (left_stack.empty())
        {
            while (!right_stack.empty())
            {
                long long val = right_stack.top();
                right_stack.pop();
                right_min.pop();
                right_max.pop();

                left_stack.push(val);

                if (!left_max.empty())
                    left_max.push(max(val, left_max.top()));
                else
                    left_max.push(val);

                if (!left_min.empty())
                    left_min.push(min(val, left_min.top()));
                else
                    left_min.push(val);
            }
        }

        if (!left_stack.empty())
        {
            left_stack.pop();
            left_min.pop();
            left_max.pop();
        }

        left++;
    }

    cout << count << endl;
    return 0;
}
