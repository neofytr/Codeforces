#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    cin >> str;

    stack<int> st;
    st.push(-1);
    int maxLen = 0;
    int count = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
        {
            st.push(i);
        }
        else
        {
            st.pop();

            if (!st.empty())
            {
                int len = i - st.top();
                if (len > maxLen)
                {
                    maxLen = len;
                    count = 1;
                }
                else if (len == maxLen)
                {
                    count++;
                }
            }
            else
            {
                st.push(i);
            }
        }
    }

    if (!count)
    {
        cout << "0 1\n";
        return 0;
    }

    cout << maxLen << " " << count << endl;
    return 0;
}
