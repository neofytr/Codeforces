#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    stack<int> st; // stores the base of the current substring
    st.push(-1);

    cin >> str;
    int count = 0;
    int maxLen = -1;
    for (int index = 0; index < str.length(); ++index)
    {
        if (str[index] == '(')
        {
            st.push(index);
        }
        else
        {
            if (!st.empty())
            {
                st.pop();
                if (!st.empty())
                {
                    int length = index - st.top();
                    if (length > maxLen)
                    {
                        count = 1;
                        maxLen = length;
                    }
                    else if (length == maxLen)
                    {
                        count++;
                    }
                }
                else
                {
                    st.push(index); // change the current base if the stack is empty
                }
            }
        }
    }

    if (count == 0)
    {
        cout << "0 1\n";
        return 0;
    }

    cout << maxLen << " " << count << endl;
    return 0;
}
